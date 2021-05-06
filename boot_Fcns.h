

int16_t readParam(void)
{
    /*
    All the parameters that can be configured in the web server are stored in the extEEPROM
    We need to fetch and save them to our global variables during the setup, to maintain 
    previously saved values
    */

    DEBUG_BOOTLN(F("Reading parameters from memory"));
    int16_t errCount = 0;

#ifdef EXTMEMORY_ON
    startEEPROM();
    if (flagPoint->extMemFlag)
    {
        loadEncSettings();
        encPoint->remotePort = encPoint->localPort + encPoint->deviceIndex;
#ifdef WEBSERVER_ON
        ip = IPAddress(192, 168, 1, 20 + encPoint->deviceIndex);
#endif
        errCount = 0;
#ifdef DEBUG_BOOT
        DEBUG_BOOTLN(F("Read param done"));
        DEBUG_BOOTLN(F("Parameters are:"));
        DEBUG_BOOT("devIndex: ");
        DEBUG_BOOTLN(encPoint->deviceIndex);
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
            DEBUG_BOOTFLO(encPoint->mac[i], HEX);
            if (i < 5)
                DEBUG_BOOT(":");
        }
        DEBUG_BOOTLN("");

        DEBUG_BOOT("localPort: ");
        DEBUG_BOOTLN(encPoint->localPort);

        DEBUG_BOOT("remotePort: ");
        DEBUG_BOOTLN(encPoint->remotePort);

        for (uint8_t i = 0; i < NUMBER_OF_PARAMETERS; i++)
        {
            DEBUG_BOOT(deviceParamNames[i]);
            DEBUG_BOOT(" is: ");
            DEBUG_BOOTLN(encPoint->deviceParameters[i]);
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
    encPoint->deviceIndex = 5;
    encPoint->mac[0] = 0xDE;
    encPoint->mac[1] = 0xAD;
    encPoint->mac[2] = 0xBE;
    encPoint->mac[3] = 0xEF;
    encPoint->mac[4] = 0xFE;
    encPoint->mac[5] = 0xED;
    encPoint->localPort = 3000;
    encPoint->deviceParameters[0] = 25;
    encPoint->deviceParameters[1] = 42;
    encPoint->deviceParameters[2] = 2006;
    encPoint->deviceParameters[3] = 10;
    encPoint->deviceParameters[4] = 10;
    encPoint->deviceParameters[5] = 400;
    encPoint->deviceParameters[6] = 6;
    encPoint->remotePort = encPoint->localPort + encPoint->deviceIndex;
#ifdef WEBSERVER_ON
    ip = IPAddress(192, 168, 1, 20 + encPoint->deviceIndex);
#else
    ip[3] = 20 + encPoint->deviceIndex;
#endif
    errCount = 0;
    return errCount;
#endif
}

#ifdef EXTMEMORY_ON
void startEEPROM(void)
{
    /*
    Try 10 times to start the eeprom, if succeed flag is true, else flag is false and
    the user will see it on the screen
    */
    Wire.begin();
    Wire.setClock(I2C_CLKFQY_AFTER);

    uint8_t i = 0;
    while (i < ERROR_I2C_LIMIT)
    {
        if (myEEPROM.begin(EEPROM_ADDRESS) == false)
        {
            DEBUG_BOOTLN(F("EEPROM Error. No memory detected"));
            flagPoint->extMemFlag = false;
            i++;
            delay(SHORTDELAY_I2C);
        }
        else
        {
            DEBUG_BOOTLN(F("EEPROM present"));
            flagPoint->extMemFlag = true;
            myEEPROM.setMemorySize(EEPROM_MEM_SIZE);
            myEEPROM.setPageSize(EEPROM_PAGE_SIZE);
            myEEPROM.setPageWriteTime(EEPROM_PAG_WRITETIME);
            DEBUG_BOOT(F("Mem size in bytes: "));
            DEBUG_BOOTLN(myEEPROM.length());
            break;
        }
    }
}

void loadEncSettings(void)
{
    /*
    Function that load the previously saved parameters on EEPROM, Check if eeprom is blank by reading
    the first four places, if those are zeroes it can be assumed that memory is empty
    */
#ifdef ERASE_EEPROM
    DEBUG_BOOTLN(F("Erasing EEPROM"));
    myEEPROM.erase();
#endif

    uint32_t testRead = 0;

    // if the first four bytes are zeroes means that memory is empty
    if (myEEPROM.get(LOCATION_SETTINGS, testRead) == 0)
    {
        myEncoder.putEncParameters(LOCATION_SETTINGS); // if memory is empty save on EEPROM the default parameters
        delayMicroseconds(SHORTDELAY_I2C);
        DEBUG_BOOTLN(F("Default settings applied"));
    }
    else
    {
        //if memory is not empty then read the actual paramters stored on EEPROM
        myEEPROM.get(LOCATION_SETTINGS, encSettings);
        delayMicroseconds(SHORTDELAY_I2C);
        DEBUG_BOOTLN(F("Loaded saved encoder settings"));
    }
}
#endif

#ifdef SHIELD_ON
bool bootShield(void)
{
    /*
    TODO: write description
    */
    bool isShieldOK, isHardOK, isLinkOK, isUdpOK, isServerOK;

    // disable all SPI peripherals by keeping high ther SS pins
    pinMode(ST_PIN_NSS, OUTPUT);
    ST_NSS_HI;
    pinMode(SD_PIN_NSS, OUTPUT);
    SD_NSS_HI;
    pinMode(ET_PIN_NSS, OUTPUT);
    ET_NSS_HI;
    delay(200);

    // ETHERNET COMMUNICATION
    Ethernet.init(ET_PIN_NSS);
    Ethernet.begin(encPoint->mac, ip);
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

#ifdef UPD_ON
    // Start Udp server
    i = 0;
    while (i < 10)
    {
        if (!Udp.begin(encPoint->localPort))
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
            DEBUG_BOOT(encPoint->localPort);
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
        flagPoint->eFlag = true;
    }
    else
    {
        DEBUG_BOOTLN(F("Check wiring to ethernet shield"));
        flagPoint->eFlag = false;
    }
    return isShieldOK;
}
#endif

#ifdef SENSOR_BME280
void BestEncoder::bmeStart(void)
{
    /*
    start temperature sensor, returns true is started properly, otherwise false
    */
    uint8_t i = 0;
    while (i < 10)
    {
        if (!bme.begin(BME280_ADDRESS))
        {
            i++;
            DEBUG_BOOTLN(F("BME not started. Check wiring."));
            flagPoint->tFlag = false;
            delay(100);
        }
        else
        {
            DEBUG_BOOTLN(F("BME started"));
            flagPoint->tFlag = true;
            secPoint->tC = READ_TEMPERATURE;
            secPoint->hP = READ_HUMIDITY;
            secPoint->bPre = READ_PRESSURE;
            break;
        }
    }
}
#endif