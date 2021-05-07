
// * IMU functions

int16_t BestEncoder::roundFunction(int16_t d)
{
    /*
        Function to round values
    */
    return floor(d + 0.5);
}

void BestEncoder::slopeCalc(void)
{
    /*
    slope calculation to transform values from the imu into values shown on the digital level
    */
    imuPoint->slopeX = 1.0 * (OUTPUT_END_X - OUTPUT_START_X) / (INPUT_END_X - INPUT_START_X);
    imuPoint->slopeY = 1.0 * (OUTPUT_END_Y - OUTPUT_START_Y) / (INPUT_END_Y - INPUT_START_Y);
}

bool BestEncoder::startIMU(void)
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
            BestEncoder::slopeCalc();
            break;
        }
    } while (i < 10);
    delay(5);
    return isIMUok;
}

void BestEncoder::imuRead(void)
{
    /*
     Read values from IMU and calculate inclination angles to show on the screen/webServer
    */

    for (uint8_t i = 0; i < MEAN_SAMPLE_NUMBER; i++)
    {
        // store reading from accelerometer on a buffer to calculate mean value
        DEBUG_IMU("i is: ");
        DEBUG_IMULN(i);
        Accelerometer.pop(accelerometerData);
        mediaAccX.push(accelerometerData.x);
        DEBUG_IMU(F("accX[i] is: "));
        DEBUG_IMULNFLO(mediaAccX.get(i), 2);
        mediaAccY.push(accelerometerData.y);
        DEBUG_IMU(F("accY[i] is: "));
        DEBUG_IMULNFLO(mediaAccY.get(i), 2);
        mediaAccZ.push(accelerometerData.z);
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
    imuPoint->outputX = OUTPUT_START_X + BestEncoder::roundFunction(imuPoint->slopeX * (avgX - INPUT_START_X));
    imuPoint->outputY = OUTPUT_START_Y + BestEncoder::roundFunction(imuPoint->slopeY * (avgZ - INPUT_START_Y));

    //  calculate inclination angle on x and y axis using trigonometry
    imuPoint->angX = atan(avgX / sqrt(pow(avgY, 2) + pow(avgZ, 2))) * (RAD_TO_DEG);
    imuPoint->angZ = atan(avgZ / sqrt(pow(avgX, 2) + pow(avgY, 2))) * (RAD_TO_DEG);

    DEBUG_IMU(F("xAngle: "));
    DEBUG_IMULNFLO(imuPoint->angX, 1);
    DEBUG_IMU(F("yAngle: "));
    DEBUG_IMULNFLO(imuPoint->angY, 1);
}

// * Encoder read functions

void BestEncoder::readEncoder(void)
{
    const uint8_t readInterval = 20;
    uint8_t i = 0;
    static uint32_t lastPulses, justBefore, rightNow, actualPulses;
    static uint32_t deltaPulses[MEAN_PUL_SAMPLES];

    do
    {
        rightNow = millis();
        if (rightNow - justBefore >= readInterval)
        {
            justBefore = millis();
            actualPulses = myPulse.getPulses();
            deltaPulses[i] = actualPulses - lastPulses;
            mediaPuls.push(deltaPulses[i]);
            lastPulses = actualPulses;
            DEBUG_FREQ(F("deltaPuls["));
            DEBUG_FREQ(i);
            DEBUG_FREQ(F("] are: "));
            DEBUG_FREQLN(deltaPulses[i]);
            i++;
        }
    } while (i < MEAN_PUL_SAMPLES);
    DEBUG_FREQ(F("Exit the loop, now mean calculation"));
    secPoint->mPul = mediaPuls.mean();
    DEBUG_FREQ(F("Mean pulse is: "));
    DEBUG_FREQLN(secPoint->mPul);
    secPoint->encFreq = secPoint->mPul / readInterval / ENCODING_TYPE;
    DEBUG_FREQ(F("Frequency is: "));
    DEBUG_FREQLN(secPoint->encFreq);
}

// * Functions to handle button pressing and also reset encoder

void BestEncoder::buttonSetup(void)
{
    DEBUG_BOOTLN(F("Setting button functions"));
    button.begin();
    button.onPressed(btnToggleScreen);
    button.onPressedFor(encResetTime, resetFunc);
    DEBUG_BOOTLN("Button function set");
}

void btnToggleScreen(void)
{
    /*
        Function used to change the different screens on the oled display
    */

    mTimerCounter = millis();
    flagPoint->toggleScreen = !flagPoint->toggleScreen;
}

void resetFunc(void)
{
    /*
    Function for software reset using nano_33_BLE
    */
    DEBUG_BOOTLN("I'm reseting");
    ST_RESET_LO;
    delayMicroseconds(500);
    ST_RESET_HI;
    delay(1);
    NVIC_SystemReset();
}

void updateButton(void)
{
    /*
    Function that update button reading
    */

    button.read();
}
