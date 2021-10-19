
/*
* Functions for seconday or auxiliary utilities
- Reading IMU, calculating values for electronic bubble level
- Starting and reading eeprom, temp sensor, ecc
*/

// * IMU functions

int16_t SensorEncoder::roundFunction(int16_t d)
{
    /*
     Round input number
     Parameter description:
     - d: number to be rounded
    */
    return floor(d + 0.5);
}

void SensorEncoder::slopeCalc(void)
{
    /*
    slope calculation to transform values from the imu into values shown on the digital level
    */

    iP->slopeX = 1.0 * (outputEndX - outputStartX) / (inputEndX - inputStartX);
    iP->slopeY = 1.0 * (outputEndY - outputStartY) / (inputEndY - inputStartY);
}

bool SensorEncoder::startIMU(void)
{
    /*
    Function to start the imu, if initialization is ok returns true, otherwise false
    */
    bool isIMUok = false;
    uint8_t i = 0;
    do
    {
        if (IMU.begin() == false)
        {
            DEBUG_IMULN(F("Failed to initialize IMU"));
            i++;
            isIMUok = false;
            delayMicroseconds(10);
        }
        else
        {
            DEBUG_IMULN(F("IMU started"));
            isIMUok = true;
            Accelerometer.begin();
            SensorEncoder::slopeCalc();
            break;
        }
    } while (i < 10);
    delay(5);
    return isIMUok;
}

void SensorEncoder::imuRead(void)
{
    /*
     Read values from IMU and calculate inclination angles to be shown on the screen/webServer
    */

    for (uint8_t i = 0; i < meanSampleNumber; i++)
    {
        // store reading from accelerometer on a buffer to calculate mean value
        DEBUG_IMU("i is: ");
        DEBUG_IMULN(i);
        Accelerometer.pop(accelerometerData); // get values from accelerometer
        mediaAccX.push(accelerometerData.x);  // save actual value on a buffer inside mean calculation library
        DEBUG_IMU(F("accX[i] is: "));
        DEBUG_IMULNFLO(mediaAccX.get(i), 2);
        mediaAccY.push(accelerometerData.y); // save actual value on a buffer inside mean calculation library
        DEBUG_IMU(F("accY[i] is: "));
        DEBUG_IMULNFLO(mediaAccY.get(i), 2);
        mediaAccZ.push(accelerometerData.z); // save actual value on a buffer inside mean calculation library
        DEBUG_IMU(F("accZ[i] is: "));
        DEBUG_IMULNFLO(mediaAccZ.get(i), 2);
    }

    // mean accelerometers values
    DEBUG_IMU(F("Mean values are: "));
    float avgX = mediaAccX.mean();
    float avgY = mediaAccY.mean();
    float avgZ = mediaAccZ.mean();
    DEBUG_IMUFLO(avgX, 2);
    DEBUG_IMU(" ");
    DEBUG_IMUFLO(avgY, 2);
    DEBUG_IMU(" ");
    DEBUG_IMULNFLO(avgZ, 2);

    // calculate (x,y) coordinates of the digital level dot shown on the screen/webServer
    iP->outputX = outputStartX + SensorEncoder::roundFunction(iP->slopeX * (avgX - inputStartX));
    iP->outputY = outputStartY + SensorEncoder::roundFunction(iP->slopeY * (avgZ - inputStartY));

    //  calculate inclination angle on x and y axis using trigonometry
    iP->angX = atan(avgX / sqrt(pow(avgY, 2) + pow(avgZ, 2))) * (RAD_TO_DEG);
    iP->angZ = atan(avgZ / sqrt(pow(avgX, 2) + pow(avgY, 2))) * (RAD_TO_DEG);

    DEBUG_IMU(F("xAngle: "));
    DEBUG_IMULNFLO(iP->angX, 1);
    DEBUG_IMU(F("yAngle: "));
    DEBUG_IMULNFLO(iP->angY, 1);
}

// * Encoder frequency calculation functions

void SystemEncoder::readEncoder(void)
{
    /*
     Read signals A and B coming from ST board using interrupts, then use the QEI library 
     to calculate actual encoder frequency: distance (in Hz) between pulse A and pulse B
     - How QEI library works? In globVar is created an object of that library called myPulse
     and pins where encoder signal arrives are given to it. The library automatically uses
     interrupts to read arriving pulses, each time there is a rising edge on each og the pins
     the pulses counter get increased.

     - Then, readEncoder signal is called every 50 ms, within screen functions. only when
     user goes to Encoder frequency page

     - readEncoder get the mean value of pulses using meanPulsamples as number of samples,
     when inside the function, the cycle is repeated each 20 ms, so a new pulses values is
     read every 20ms

    */

    const uint8_t readInterval = 20; // in ms, reading interval, each 20 ms take 20 samples for freq calc
    uint8_t i = 0;
    static uint32_t lastPulses, justBefore, rightNow, actualPulses;
    static uint32_t deltaPulses[meanPulSamples];

    do
    {
        // Check if 20ms have passed before start new reading of pulses
        rightNow = millis();
        if (rightNow - justBefore >= readInterval)
        {
            justBefore = millis();
            actualPulses = myPulse.getPulses();
            deltaPulses[i] = actualPulses - lastPulses; // get current pulses
            mediaPuls.push(deltaPulses[i]);             // save current pulses on buffer for mean calculation
            lastPulses = actualPulses;
            DEBUG_FREQ(F("deltaPuls["));
            DEBUG_FREQ(i);
            DEBUG_FREQ(F("] are: "));
            DEBUG_FREQLN(deltaPulses[i]);
            i++;
        }
    } while (i < meanPulSamples);
    DEBUG_FREQ(F("Exit the loop, now mean calculation"));
    sP->mPul = mediaPuls.mean(); // get pulses mean value
    DEBUG_FREQ(F("Mean pulse is: "));
    DEBUG_FREQLN(sP->mPul);
    sP->encFreq = sP->mPul / readInterval / encodingType; // get frequency value
    DEBUG_FREQ(F("Frequency is: "));
    DEBUG_FREQLN(sP->encFreq);
}

// * Functions to handle button pressing and also reset encoder

void ScreenEncoder::buttonSetup(void)
{
    /*
     Set button using easyButton library, this allow to have two different behaviour with a single button:
     when single-pressed screen page is changed, when long-pressed for 5 seconds, the encoder is reset.
    */

    DEBUG_BOOTLN(F("Setting button functions"));
    button.begin();
    button.onPressed(btnToggleScreen);            // single pressed, call btnToggleScreen function
    button.onPressedFor(encResetTime, resetFunc); // long pressed for 5 seconds, call reset function
    DEBUG_BOOTLN("Button function set");
}

void resetFunc(void)
{
    /*
    Function for software reset using nano_33_BLE, first reset ST and ethernet shield for 500 us,
    then call nordic semiconductors hal function NVIC reset.
    */
    DEBUG_BOOTLN("I'm reseting");
    ST_RESET_LO;
    delayMicroseconds(500);
    ST_RESET_HI;
    delay(1);
    NVIC_SystemReset();
}

void btnToggleScreen(void)
{
    /*
        Function used to change the different screens on the oled display
    */

    sP->mTimerCounter = millis();
    fP->toggleScreen = !fP->toggleScreen;
}

// * Functions used during boot time

#ifdef EXTMEMORY_ON
int16_t SystemEncoder::readParam(void)
{
    /*
    All the parameters that can be configured in the web server are stored in the extEEPROM
    We need to fetch and save them to our global variables during the setup, to maintain 
    previously saved values
    */

    DEBUG_BOOTLN(F("Reading parameters from memory"));
    int16_t errCount = 0;

#ifdef EXTMEMORY_ON
    // start EEPROm
    SystemEncoder::startEEPROM();
    if (fP->extMemFlag)
    {
        // if EEPROM started, read stored values and save them on globVar
        SystemEncoder::loadEncSettings();
        eP->remotePort = eP->localPort + eP->deviceIndex;
#ifdef WEBSERVER_ON
        ip = IPAddress(192, 168, 0, 20 + eP->deviceIndex);
#endif
        errCount = 0;
#ifdef DEBUG_BOOT
        DEBUG_BOOTLN(F("Read param done"));
        DEBUG_BOOTLN(F("Parameters are:"));
        DEBUG_BOOT("devIndex: ");
        DEBUG_BOOTLN(eP->deviceIndex);
        DEBUG_BOOT(F("Local IP: "));
        for (uint8_t i = 0; i < 4; i++)
        {
            DEBUG_BOOT(ip[i]);
            if (i < 3)
                DEBUG_BOOT(F(":"));
        }
        DEBUG_BOOTLN("");
        DEBUG_BOOT("MAC address: ");
        for (uint8_t i = 0; i < 6; i++)
        {
            DEBUG_BOOTFLO(eP->mac[i], HEX);
            if (i < 5)
                DEBUG_BOOT(":");
        }
        DEBUG_BOOTLN("");

        DEBUG_BOOT("localPort: ");
        DEBUG_BOOTLN(eP->localPort);

        DEBUG_BOOT("remotePort: ");
        DEBUG_BOOTLN(eP->remotePort);

        for (uint8_t i = 0; i < numberParameters; i++)
        {
            DEBUG_BOOT(deviceParamNames[i]);
            DEBUG_BOOT(" is: ");
            DEBUG_BOOTLN(eP->deviceParameters[i]);
        }
#endif
        return errCount;
    }
    else
    {
        errCount = -1;
        DEBUG_BOOTLN(F("Failed to read parameters. Check EEPROM"));
        return errCount;
    }
#else
    eP->deviceIndex = 5;
    eP->mac[0] = 0xDE;
    eP->mac[1] = 0xAD;
    eP->mac[2] = 0xBE;
    eP->mac[3] = 0xEF;
    eP->mac[4] = 0xFE;
    eP->mac[5] = 0xED;
    eP->localPort = 3000;
    eP->deviceParameters[0] = 25;
    eP->deviceParameters[1] = 42;
    eP->deviceParameters[2] = 2006;
    eP->deviceParameters[3] = 10;
    eP->deviceParameters[4] = 10;
    eP->deviceParameters[5] = 400;
    eP->deviceParameters[6] = 6;
    eP->remotePort = eP->localPort + eP->deviceIndex;
#ifdef WEBSERVER_ON
    ip = IPAddress(192, 168, 0, 20 + eP->deviceIndex);
#else
    ip[3] = 20 + eP->deviceIndex;
#endif
    errCount = 0;
    return errCount;
#endif
}

void SystemEncoder::startEEPROM(void)
{
    /*
    Try 10 times to start the eeprom, if succeed flag is true, else flag is false and
    the user will see it on the screen
    */
    Wire.begin();
    Wire.setClock(i2cAftClk);

    uint8_t i = 0;
    while (i < i2cErrorLimit)
    {
        if (myEEPROM.begin(eepromAddress) == false)
        {
            DEBUG_BOOTLN(F("EEPROM Error. No memory detected"));
            fP->extMemFlag = false;
            i++;
            delay(delayI2C);
        }
        else
        {
            DEBUG_BOOTLN(F("EEPROM present"));
            fP->extMemFlag = true;
            myEEPROM.setMemorySize(eepromMemSize);
            myEEPROM.setPageSize(eepromPageSize);
            myEEPROM.setPageWriteTime(eepromPageWriteTime);
            DEBUG_BOOT(F("Mem size in bytes: "));
            DEBUG_BOOTLN(myEEPROM.length());
            break;
        }
    }
}

void SystemEncoder::loadEncSettings(void)
{
    /*
    Function that load the previously saved parameters on EEPROM, Check if eeprom is blank by reading
    the first four places, if those are zeroes it can be assumed that memory is empty, if so, then save
    the default parameters. If memory is not empty, read the saved values and save them on encSettings structure
    to be used during runtime
    */

#ifdef ERASE_EEPROM
    DEBUG_BOOTLN(F("Erasing EEPROM"));
    myEEPROM.erase();
#endif

    uint32_t testRead = 0;

    // if the first four bytes are zeroes means that memory is empty
    if (myEEPROM.get(eepromStartAddress, testRead) == 0)
    {
        mySystem.putEncParameters(eepromStartAddress); // if memory is empty save on EEPROM the default parameters
        delayMicroseconds(delayI2C);
        DEBUG_BOOTLN(F("Default settings applied"));
    }
    else
    {
        //if memory is not empty then read the actual paramters stored on EEPROM
        DEBUG_TASKSLN("Now i read from memory and save it to globVar");
        DEBUG_DELAY(1000);
        DEBUG_TASKS("Starting EEPROM position: ");
        DEBUG_TASKSLN(eepromStartAddress);
        myEEPROM.get(eepromStartAddress, encSettings);
        delayMicroseconds(delayI2C);
        DEBUG_BOOTLN(F("Loaded saved encoder settings"));
    }
}
#endif

#ifdef SENSOR_BME280
void SensorEncoder::bmeStart(void)
{
    /*
    start temperature sensor, returns true is started properly, otherwise false
    */
    uint8_t i = 0;
    while (i < 10)
    {
        if (!bme.begin(bmeAddress))
        {
            i++;
            DEBUG_BOOTLN(F("BME not started. Check wiring."));
            fP->tFlag = false;
            delay(100);
        }
        else
        {
            DEBUG_BOOTLN(F("BME started"));
            fP->tFlag = true;
            sP->tC = READ_TEMPERATURE;
            sP->hP = READ_HUMIDITY;
            sP->bPre = READ_PRESSURE;
            break;
        }
    }
}
#endif

#ifdef SHIELD_ON
bool SystemEncoder::bootShield(void)
{
    /*
     Function that starts the ethernet shield used for webServer and udp communication with plc
    */
    DEBUG_BOOTLN(F("Starting boot shield function"));
    bool isShieldOK, isHardOK, isLinkOK, isUdpOK, isServerOK;

    // disable all SPI peripherals by keeping high ther SS pins
    DEBUG_BOOTLN(F("Setting all slave select high"));
    ST_NSS_HI;
    SD_NSS_HI;
    ET_NSS_HI;
    delay(200);

    // ETHERNET COMMUNICATION
    DEBUG_BOOTLN(F("Starting ethernet init"));
    Ethernet.init(ET_PIN_NSS);
    Ethernet.begin(eP->mac, ip);
    ET_NSS_HI; // Bring the SS pin high again (bug of Ethernet library causes it to turn Low after Ethernet.begin())
    DEBUG_BOOTLN(F("Ethernet activated."));

    // Check for Ethernet hardware present
    uint8_t i = 0;
    while (i < 10)
    {
        if (Ethernet.hardwareStatus() == EthernetNoHardware)
        {
            i++;
            DEBUG_BOOTLN(F("Ethernet shield was not found"));
            isHardOK = false;
            delay(10);
        }
        else if (Ethernet.hardwareStatus() == EthernetW5500)
        {
            DEBUG_BOOTLN(F("W5500 Ethernet controller detected"));
            isHardOK = true;
            break;
        }
    }

    // Check for ethernet cable connected
    i = 0;
    while (i < 10)
    {
        if (Ethernet.linkStatus() == LinkOFF)
        {
            i++;
            DEBUG_BOOTLN(F("Ethernet cable is not connected"));
            isLinkOK = false;
            delay(10);
        }
        else
        {
            DEBUG_BOOTLN(F("Ethernet cable connected"));
            isLinkOK = true;
            break;
        }
    }

    // Start Udp server
#ifdef UPD_ON
    i = 0;
    while (i < 10)
    {
        if (!Udp.begin(eP->localPort))
        {
            i++;
            DEBUG_BOOTLN(F("Error connecting device. UDP socket not available"));
            isUdpOK = false;
            delay(10);
        }
        else
        {
#ifdef DEBUG_BOOT
            DEBUG_BOOTLN(F("Connection Udp OK"));
            DEBUG_BOOT(F("Local IP address: "));
            for (uint8_t w = 0; w < 4; w++)
            {
                DEBUG_BOOT(ip[w]);
                if (w < 3)
                    DEBUG_BOOT(".");
            }
            DEBUG_BOOT(F(", port: "));
            DEBUG_BOOT(eP->localPort);
            DEBUG_BOOTLN(".");
#endif
            isUdpOK = true;
            break;
        }
    }
#else
    isUdpOK = true;
#endif

    // Start webServer
    i = 0;
    while (i < 10)
    {
        server.begin();
        if (!server)
        {
            i++;
            DEBUG_BOOTLN(F("Server not started"));
            isServerOK = false;
            delay(10);
        }
        else
        {
            DEBUG_BOOT(F("Server is at: "));
            DEBUG_BOOTLN(Ethernet.localIP());
            isServerOK = true;
            break;
        }
    }

    isShieldOK = isLinkOK && isHardOK && isUdpOK && isServerOK; // to check if all systems started properly

    if (isShieldOK)
    {
        DEBUG_BOOTLN(F("WebServer ready to go!"));
        fP->eFlag = true;
    }
    else
    {
        DEBUG_BOOTLN(F("Check wiring to ethernet shield"));
        fP->eFlag = false;
    }
    return isShieldOK;
}
#endif

// * Function that handles PLC enable
void SystemEncoder::enableFlagEncoder(void)
{
    if (PLC_STATUS)
        fP->enablePLC = true;
    else
        fP->enablePLC = false;
}

// * For debug functions execution time
#ifdef DEBUG_FCN_TIME
void pinConfig(int pin)
{
    NRF_GPIO->PIN_CNF[pin] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
                             (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
                             (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) |
                             (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
                             (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
}
#endif
