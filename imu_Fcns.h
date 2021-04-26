
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
    uint8_t w = 0;
    do
    {
        if (IMU.begin() == false)
        {
            DEBUG_IMULN(F("Failed to initialize IMU"));
            w++;
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
    } while (w < 10);
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
    imuPoint->outputY = OUTPUT_START_Y + BestEncoder::roundFunction(imuPoint->slopeY * (avgY - INPUT_START_Y));

    //  calculate inclination angle on x and y axis using trigonometry
    imuPoint->angX = atan(avgX / sqrt(pow(avgY, 2) + pow(avgZ, 2))) * (RAD_TO_DEG);
    imuPoint->angY = atan(avgY / sqrt(pow(avgX, 2) + pow(avgZ, 2))) * (RAD_TO_DEG);

    DEBUG_IMU(F("xAngle: "));
    DEBUG_IMULNFLO(imuPoint->angX, 1);
    DEBUG_IMU(F("yAngle: "));
    DEBUG_IMULNFLO(imuPoint->angY, 1);
}