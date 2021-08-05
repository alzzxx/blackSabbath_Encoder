

void ScreenEncoder::startScreen(void)
{
    /*
     Start the oled screen, if it fails, block the entire program, the encoder 
     does not boot up
    */

#if defined(ARDUINO_NANO)
    while (!display.begin(SSD1306_SWITCHCAPVCC, oledAddress))
    {
        DEBUG_BOOTLN(F("SSD1306 allocation failed"));
    }
#endif

    // if the screen starts show debug info and move on
    fP->onScreen = true;
    DEBUG_BOOTLN(F("Screen started"));
    DEBUG_DELAY(1000);
    display.clearDisplay();
    display.invertDisplay(true);
    display.display();
}

void ScreenEncoder::splashScreen(void)
{
    /*
     Shows initial brevetti cea logo, encoder name and firmware version
    */

    display.drawBitmap(0, 5, oledIcon_2, 128, 64, WHITE); // brevetti logo
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::setDisp(1, false, 0, 0, false);
    ScreenEncoder::showText(35, 30, oledMessage_table, 0, true);
    ScreenEncoder::showText(42, 40, oledMessage_table, 1, true);
    display.display();
    DEBUG_BOOTLN(F("Encoder BS"));
    DEBUG_BOOTLN(F("V 1.0.0"));
    delay(delayScreen);
    display.clearDisplay();
    display.display();
}

void ScreenEncoder::initialCheck(void)
{
    /*
     This function performs an initial check on ST and pixart sensor,
     if both are OK, the program continues to boot up, if not it stops
     because encoder can't work without F031K6 board or PAT9130 sensor.
     If everything is correct, shows the message "encoder started"
    */

    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 3, true);
    display.display();
    delay(delayScreen);
    while (!(SENSOR_STATUS == LOW && ST_STATUS == HIGH))
    {
        // if ST or Pixart have a problem, block the program and
        // shows the problem on the display
        DEBUG_BOOTLN(F("Pixart sensor error"));
        display.clearDisplay();
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
        ScreenEncoder::showText(25, 43, oledMessage_table, 4, true);
        display.display();
    }
    DEBUG_BOOTLN(F("Pixart sensor started"));
    display.clearDisplay();
    display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(20, 43, oledMessage_table, 5, true);
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    display.display();
}

bool ScreenEncoder::initParam(void)
{
    /*
     This function starts the eeprom and read the parameters saved, if 
     reading is correct, shows the message "Parameters loaded" and returns
     true, otherwise shows "Read parameters failed" and returns false
    */

    bool eepromOK;
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 37, true);
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
#ifdef EXTMEMORY_ON

    // if eeprom started properly readOaram functions returns 0, otherwise -1
    if (mySystem.readParam() == 0)
    {
        display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 39, true);
        eepromOK = true;
    }
    else
    {
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 40, true);
        eepromOK = false;
    }
#else
    DEBUG_BOOTLN(F("ExtEEPROM not present, moving on"));
    ScreenEncoder::setDisp(1, false, 0, 0, false);
    ScreenEncoder::showText(17, 43, oledMessage_table, 38, true);
    eepromOK = true;
#endif
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    display.display();
    return eepromOK;
}

bool ScreenEncoder::shieldStart(void)
{
    /*
     Function that calls bootShield to start the ethernet shield, if correct
     shows "webServer ready" message on oled screen, otherwise shows error
     message
    */

    // shows initial messages
    bool shieldOK = false;
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 27, true);
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);

    // calls bootshield
#ifdef SHIELD_ON
    if (mySystem.bootShield())
    {
        DEBUG_BOOTLN(F("Ethernet shield started"));
        display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 28, true);
        shieldOK = true;
    }
    else
    {
        DEBUG_BOOTLN(F("Check ethernet shield"));
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 29, true);
        shieldOK = false;
    }
#else
    DEBUG_BOOTLN(F("Shield not present, moving on"));
    ScreenEncoder::setDisp(1, false, 0, 0, false);
    ScreenEncoder::showText(17, 43, oledMessage_table, 2, true);
    shieldOK = true;
#endif
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    display.display();

    //if shield is ok returns true, otherwise false
    return shieldOK;
}

bool ScreenEncoder::sensorStart(void)
{
    /*
     Function that calls initialization of temperature sensor and
     accelerometer, if both are ok returns true, otherwise false
    */

    bool sensorOK = false;

    //shows initial messages
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 19, true);
    display.display();
    delay(delayScreen);
#if defined(SENSOR_BME280)
    mySensor.bmeStart(); // start temp sensor
#endif
#ifdef ACCELEROMETER_ON
    fP->imuFlag = mySensor.startIMU(); // start accelerometer
#endif
    display.clearDisplay();
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    if (fP->tFlag && fP->imuFlag)
    {
        DEBUG_BOOTLN(F("All sensor started"));
        display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 20, true);
        sensorOK = true;
    }
    else
    {
        DEBUG_BOOTLN(F("Some sensor failed, check wiring"));
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 21, true);
        sensorOK = false;
    }
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    display.display();

    // if both are ok returns true, otherwise false
    return sensorOK;
}

void ScreenEncoder::finishSetup(void)
{
    /*
     Last page shown during boot up, message "finishing setup"
     is displayed on oled screen
    */

    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 44, true);
    display.display();
    delay(delayScreen);
}

void ScreenEncoder::displayInitial(void)
{
    /*
     Initial page shown on the display, shows the general encoder status: 
     - ST board status, PAT9130 sensor status, and PLC enable status
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 7, false);
    ScreenEncoder::dispWarning(108, 5);
    ScreenEncoder::showText(5, 20, oledMessage_table, 12, false);
    ScreenEncoder::showText(5, 33, oledMessage_table, 13, false);
    ScreenEncoder::showText(5, 46, oledMessage_table, 14, false);

    // check pat9130 status
    if (fP->patFlag)
    {
        ScreenEncoder::setDisp(1, true, 0, 0, false);
        ScreenEncoder::showText(80, 20, oledMessage_table, 16, false);
        DEBUG_SCREENLN(F("Pixart error"));
    }
    else
    {
        ScreenEncoder::setDisp(1, true, 0, 0, false);
        ScreenEncoder::showText(80, 20, oledMessage_table, 15, false);
        DEBUG_SCREENLN(F("Pixart OK"));
    }

    // check st board status
    if (fP->stFlag)
    {
        ScreenEncoder::setDisp(1, true, 0, 0, false);
        ScreenEncoder::showText(80, 33, oledMessage_table, 16, false);
        DEBUG_SCREENLN(F("ST error"));
    }
    else
    {
        ScreenEncoder::setDisp(1, true, 0, 0, false);
        ScreenEncoder::showText(80, 33, oledMessage_table, 15, false);
        DEBUG_SCREENLN(F("ST OK"));
    }

    // scheck plc enable status
    if (PLC_STATUS == HIGH)
    {
        ScreenEncoder::setDisp(1, true, 0, 0, false);
        ScreenEncoder::showText(80, 46, oledMessage_table, 17, false);
        DEBUG_SCREENLN(F("PLC enable"));
    }
    else
    {
        ScreenEncoder::setDisp(1, true, 0, 0, false);
        ScreenEncoder::showText(80, 46, oledMessage_table, 18, false);
        DEBUG_SCREENLN(F("PLC off"));
    }
    display.display();
}

void ScreenEncoder::displayPixVal(void)
{
    /*
     Page that shows all encoder parameters on the display
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(25, 5, 1, false, oledMessage_table, 11, false);

    // if both st board and pat9130 are ok, shows values
    if (ST_STATUS == HIGH && SENSOR_STATUS == LOW)
    {
        ScreenEncoder::showText(3, 19, oledMessage_table, 30, false);
        display.setCursor(45, 19);
        display.print(eP->deviceParameters[0]); // encDist parameter
        DEBUG_SCREEN(F("encDist: "));
        DEBUG_SCREENLN(eP->deviceParameters[0]);
        ScreenEncoder::showText(64, 19, oledMessage_table, 31, false);
        display.setCursor(108, 19);
        display.print(eP->deviceParameters[1]); // camRes parameter
        DEBUG_SCREEN(F("camRes: "));
        DEBUG_SCREENLN(eP->deviceParameters[1]);
        ScreenEncoder::showText(3, 29, oledMessage_table, 36, false);
        display.setCursor(45, 29);
        display.print(eP->deviceParameters[6]); // patCurrent parameter
        DEBUG_SCREEN(F("patCurr: "));
        DEBUG_SCREENLN(eP->deviceParameters[6]);
        ScreenEncoder::showText(64, 29, oledMessage_table, 35, false);
        display.setCursor(102, 29);
        display.print(eP->deviceParameters[5]); // tSample parameter
        DEBUG_SCREEN(F("tSample: "));
        DEBUG_SCREENLN(eP->deviceParameters[5]);
        ScreenEncoder::showText(3, 39, oledMessage_table, 34, false);
        display.setCursor(45, 39);
        display.print(eP->deviceParameters[4]); // outFilter parameter
        DEBUG_SCREEN(F("outFilter: "));
        DEBUG_SCREENLN(eP->deviceParameters[4]);
        ScreenEncoder::showText(64, 39, oledMessage_table, 33, false);
        display.setCursor(108, 39);
        display.print(eP->deviceParameters[3]); // inFilter parameter
        DEBUG_SCREEN(F("inFilter: "));
        DEBUG_SCREENLN(eP->deviceParameters[3]);
        ScreenEncoder::showText(3, 49, oledMessage_table, 32, false);
        display.setCursor(45, 49);
        display.print(eP->deviceParameters[2]); // patRes parameter
        DEBUG_SCREEN(F("patRes: "));
        DEBUG_SCREENLN(eP->deviceParameters[2]);
    }
    // otherwise shows message "encoder error"
    else
    {
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::showText(25, 43, oledMessage_table, 4, true);
    }
    display.display();
}

void ScreenEncoder::displayFreqSpeed(void)
{
    /*
      Function that shows on display the current frequency of the 
      encoder signal, e.g., the distance (in Hz) between each rising
      edge of A and B signals. If the encoder is enable the values are
      displayed, otherwise shows "Encoder disable"
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(25, 5, 1, false, oledMessage_table, 43, false);
    if (ENCODER_ENABLE)
    {
        display.drawBitmap(3, 20, oledIcon_6, 23, 21, WHITE);
        display.setTextSize(2);
        display.setCursor(30, 34);
        mySystem.readEncoder(); // call to function that read pulses and calculate frequency
        display.print(sP->encFreq);
        display.setTextSize(2);
        display.setCursor(80, 34);
        display.print("kHz");
    }
    else
    {
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::showText(25, 43, oledMessage_table, 45, true);
    }
    display.display();
}

void ScreenEncoder::displayIPMAC(void)
{
    /*
     Shows current IP, device number and mac address of the encoder if the 
     ethernet shield is ok, otherwise shows error
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(22, 5, 1, false, oledMessage_table, 10, false);
#ifdef SHIELD_ON
    // if shield if ok
    if (fP->eFlag)
    {
        ScreenEncoder::showText(5, 20, oledMessage_table, 23, false);
        display.setCursor(50, 20);
        display.print(eP->deviceIndex); // shows device index
        ScreenEncoder::showText(5, 30, oledMessage_table, 24, false);
        display.setCursor(50, 30);
        String myIP = "192.168.0." + String(20 + eP->deviceIndex);
        display.print(myIP); // shows current ip
        DEBUG_SCREEN(F("Local IP: "));
        DEBUG_SCREENLN(ip);
        ScreenEncoder::showText(5, 39, oledMessage_table, 25, false);
        display.setCursor(5, 48);
        String myMac = String(eP->mac[0], HEX) + ":" + String(eP->mac[1], HEX) + ":" + String(eP->mac[2], HEX) +
                       ":" + String(eP->mac[3], HEX) + ":" + String(eP->mac[4], HEX) + ":" + String(eP->mac[5], HEX);
        display.print(myMac); // shows current mac address
        DEBUG_SCREEN(F("MAC Address: "));
        DEBUG_SCREEN(myMac);
        DEBUG_SCREENLN(F(""));
    }
    else
    {
        // shows error message
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 26, true);
    }
#endif
#ifndef SHIELD_ON
    ScreenEncoder::showText(5, 20, oledMessage_table, 23, false);
    display.setCursor(47, 20);
    display.print(eP->deviceIndex);
    ScreenEncoder::showText(5, 30, oledMessage_table, 24, false);
    display.setCursor(47, 30);
    display.cp437(true);
    for (uint8_t i = 0; i < 4; i++)
    {
        display.print(ip[i], DEC);
        if (i < 3)
            display.write(46);
    }
    ScreenEncoder::showText(5, 39, oledMessage_table, 25, false);
    display.setCursor(5, 48);
    for (uint8_t i = 0; i < 6; i++)
    {
        display.print(eP->mac[i], HEX);
        if (i < 5)
        {
            display.write(58);
        }
    }
#endif
    display.display();
}

void ScreenEncoder::displayDigitalLevel(void)
{
    /*
     Shows electronic bubble level on the display, also x and z
     inclination angles to properly orientate the encoder
    */

    display.clearDisplay();
    // show fiex messages
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(35, 5, 1, false, oledMessage_table, 9, true);
#ifdef ACCELEROMETER_ON
    int16_t cursorX, cursorY;
    display.cp437(true);
    display.drawBitmap(24, 19, oledIcon_5, 17, 17, WHITE);  // shows accelerometer icon
    mySensor.imuRead();                                     // read imu sensor
    display.drawCircle(96, 36, 6, WHITE);                   // shows fixed circle for bubble level
    display.fillCircle(iP->outputX, iP->outputY, 4, WHITE); // show filled circle that change position according to inclination of encoder
    display.setCursor(4, 36);
    display.write(233);
    display.print("x:");
    display.setCursor(22, 36);
    display.print(iP->angX, 1); // shows x inclination angle
    display.setCursor(55, 36);
    display.write(167);
    display.setCursor(4, 46);
    display.write(233);
    display.print("z:");
    display.print(iP->angZ, 1); // shows z inclination angle
    display.setCursor(55, 46);
    display.write(167);
#else
    ScreenEncoder::showText(5, 34, oledMessage_table, 42, true);
#endif
    display.display();
}

void ScreenEncoder::displayTempHum(void)
{
    /*
     Shows the values from temperature sensor bme280 only if the sensor is ok,
     otherwise shows an error message
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(5, 5, 1, false, oledMessage_table, 8, false);
    if (fP->tFlag)
    {
        DEBUG_SCREEN(F("bmeTemp: "));
        DEBUG_SCREENLN(sP->tC);
        DEBUG_SCREEN(F("bmeHum: "));
        DEBUG_SCREENLN(sP->hP);
        display.drawBitmap(10, 22, oledIcon_3, 16, 16, WHITE); // temperature icon
        display.drawBitmap(10, 39, oledIcon_4, 16, 16, WHITE); // humidity icon
        ScreenEncoder::setDisp(2, false, 35, 22, true);
        display.print(sP->tC); // temp value
        display.setCursor(35, 39);
        display.print(sP->hP); // humidity value
        display.cp437(true);
        ScreenEncoder::setDisp(1, false, 97, 22, true);
        display.write(167);
        display.print("");
        display.write(67);
        display.setCursor(97, 39);
        display.write(37);
    }
    else
    {
        DEBUG_SCREENLN(F("BME280 sensor error"));
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        ScreenEncoder::setDisp(1, false, 0, 0, false);
        ScreenEncoder::showText(17, 43, oledMessage_table, 22, true);
    }
    display.display();
}

void ScreenEncoder::frameHeader(uint8_t cursorX, uint8_t cursorY, uint8_t sizeText, bool varInverted, const char *const buffer[], uint8_t num, bool isAccelerometer)
{
    /*
    Function that creates the frame and header for each page on the oled screen
    Parameters description:
    - cursorX: x position of the message on the oled screen (goes from 0 to 128)
    - cursorY: y position of the message on the oled screen (goes from 0 to 64)
    - sizeText: size of the text, minValue: 1 maxValue: 2
    - varInverted: to create the inverted text effect, if true the background will
    be white and the letters hollow, otherwise the background will be black and the
    letters white
    - buffer: pointer to the array containing all messages available to be shown on screen
    - num:  is the number, inside the previous array, of the desired message
    - isAccelerometer: to indicate wether the display shows accelerometer values or not

    */

    display.drawRect(0, 0, 128, 16, WHITE);  // draw upper frame
    display.drawRect(0, 17, 128, 47, WHITE); // draw lower frame

    /*
     if the display is on the electronic bubble page, draw additional lines to
     divide the page
    */
    if (isAccelerometer == true)
    {
        display.drawFastVLine(64, 17, 40, WHITE);
        display.drawFastHLine(0, 55, 128, WHITE);
    }

    ScreenEncoder::setDisp(sizeText, varInverted, 0, 0, false);   // set text settings
    ScreenEncoder::showText(cursorX, cursorY, buffer, num, true); // display header message
}

void ScreenEncoder::showText(uint16_t xCursor, uint16_t yCursor, const char *const bufferText[], uint8_t bufferNumber, bool isCentered)
{
    /*
    Show the desired message on the screen, message must be choosen from the oledMessage_table
    Parameters description: 
    - xCursor: x position of the message on the oled screen (goes from 0 to 128)
    - yCursor: y position of the message on the oled screen (goes from 0 to 64)
    - bufferText: pointer to the array containing all messages available to be shown on screen
    - bufferNumber: is the number, inside the previous array, of the desired message
    - isCentered: to indicate if the message should be centered or not, if true, the function
    automatically calculate the new xCursor position to have the message centered
    */

    if (isCentered)
    {
        // if the text should be centered, calculate string lenght
        int16_t x1, y1;
        uint16_t stringWidth, stringHeight;
        display.getTextBounds(bufferText[bufferNumber], xCursor, yCursor, &x1, &y1, &stringWidth, &stringHeight); // string lenght calculation
        uint16_t xPosition = (screenW - stringWidth) / 2;                                                         // calculate xposition of the string using its width
        display.setCursor(xPosition, yCursor);                                                                    // set cursor with the calculated coordinates
    }
    else
    {
        display.setCursor(xCursor, yCursor); // if text is not centered set cursor with the input parameters
    }
    display.print(bufferText[bufferNumber]); // show message
}

void ScreenEncoder::setDisp(uint8_t textSize, bool isInverted, uint8_t xCursor, uint8_t yCursor, bool isCursor)
{
    /*
    - Set text parameters like textsSize, color and cusor position
    Parameters description:
    - textSize: to set the size of the text, goes from 1 to 2
    - isInverted, to create the inverted text effect, if true the background will
    be white and the letters hollow, otherwise the background will be black and the
    letters white
    - xCursor: x position of text
    - yCursor: y position of text
    - isCursor: if true cursor will be positioned at (xCursor, yCursor) coordinate,
    else cursor will be positioned using showText function
    */

    display.setTextSize(textSize);
    if (isInverted)
        display.setTextColor(BLACK, WHITE);
    else
        display.setTextColor(WHITE);
    if (isCursor)
        display.setCursor(xCursor, yCursor);
}

void ScreenEncoder::dispWarning(uint8_t xCursor, uint8_t yCursor)
{
    /*
     Function that displays a warning sign (!) on main screen
     sysOK flag is not true, to let the user knows that there is a problem
     with the encoder
     Parameters description:
     xCursor: x position of warning symbol
     yCursor: y position of warning symbol
    */

    if (!fP->sysOK)
    {
        display.cp437(true);
        display.setCursor(xCursor, yCursor);
        display.write(40);
        display.write(33);
        display.write(41);
    }
}

void ScreenEncoder::displayIndicator(uint8_t displayNumber)
{
    /*
     Function that displays the small indicator circles of the screen bottom
     If actual page is the same as display number draw a filled circle
     Parameters description:
     - displayNumber: actual page shown on the oled screen

    */

    uint8_t xCoordinates[6] = {39, 49, 59, 69, 79, 89};
    for (uint8_t i = 0; i < 6; i++)
    {
        if (i == displayNumber)
        {
            display.fillCircle(xCoordinates[i], 59, 2, WHITE);
        }
        else
        {
            display.drawCircle(xCoordinates[i], 59, 2, WHITE);
        }
    }
}

void ScreenEncoder::updateScreenNum(void)
{
    /*
     - This function updates the displayScreenNum when the button is pressed, then the updateScreen
     function read that number and shows the desired page on oled screen
     - Also Handle the auto OFF after 1 minute, when the button is not pressed for 1 minute the screen
     goes off, then when it's off and the used press the button it turns on and shows the first page
    */

    const uint8_t displayScreenNumMax = 5;
    const uint32_t waitScreen = 60000;
    static bool offFlag;

    // if button isn't pressed and screen if on
    if (fP->toggleScreen == fP->prevTogScr && fP->onScreen == true)
    {
        DEBUG_SCREENLN(F("Button not pressed, time is running"));
        if (offFlag == true)
        {
            // if 1 minute have passed, goes to screen 6, displaySleep to turn off oled
            DEBUG_SCREENLN(F("offFlag is true, shutting down screen"));
            sP->displayScreenNum = 6;
            offFlag = false;
        }
        else if (millis() > sP->mTimerCounter + waitScreen)
        {
            // to check the 1 minute have passed
            DEBUG_SCREENLN(F("Time has passed, setting offFlag true"));
            offFlag = true;
        }
#ifdef DEBUG_SCREEN
        else
        {
            DEBUG_SCREENLN(F("Time is running, screen still on"));
        }
#endif
    }
#ifdef DEBUG_SCREEN
    else if (fP->toggleScreen == fP->prevTogScr && fP->onScreen == false)
    {
        // is screen is off and the button is not pressed, just keep
        // running and wait
        DEBUG_SCREENLN(F("Screen is off, waiting for restart"));
    }
#endif
    else if (fP->toggleScreen != fP->prevTogScr)
    {
        fP->prevTogScr = fP->toggleScreen;
        if (fP->onScreen == true)
        {
            // if screen is on and button is pressed, update
            // page to be shown
            if (sP->displayScreenNum < displayScreenNumMax)
            {
                sP->displayScreenNum++;
            }
            else
            {
                sP->displayScreenNum = 0;
            }
        }
        else
        {
            // if screen if off and button is pressed, goes to
            // display 7, displayWake and turn on screen
            DEBUG_SCREENLN(F("Screen was off, i'm waking it on"));
            sP->displayScreenNum = 7;
        }
    }
}

void ScreenEncoder::displaySleep(void)
{
    /*
     Turns off oled screen
    */

    display.ssd1306_command(SSD1306_DISPLAYOFF);
    fP->onScreen = false;
}

void ScreenEncoder::displayWake(void)
{
    /*
     Turns on oled screen
    */

    display.ssd1306_command(SSD1306_DISPLAYON);
    fP->onScreen = true;
}
