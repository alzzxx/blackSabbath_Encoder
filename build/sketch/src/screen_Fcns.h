#line 1 "c:\\Users\\a.rondon\\Documents\\GitHub\\blackSabbath_Encoder\\src\\screen_Fcns.h"

void ScreenEncoder::startScreen(void)
{
    /*
    Function that starts the oled screen, there are different configurations according to the hardware used
    if the screen don't start, the program remains blocked
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
    display.display();
}

void ScreenEncoder::splashScreen(void)
{
    /*
    TODO: Write description and comments
    */

    display.drawBitmap(0, 5, oledIcon_2, 128, 64, WHITE);
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
    TODO: Write description and comments
    */

    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 3, true);
    display.display();
    delay(delayScreen);
    while (!(SENSOR_STATUS == LOW && ST_STATUS == HIGH))
    {
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
    TODO: Write description and comments
    */

    bool eepromOK;
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 37, true);
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
#ifdef EXTMEMORY_ON
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
    TODO: Write description and comments
    */

    bool shieldOK = false;
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 27, true);
    display.display();
    delay(delayScreen);
    display.clearDisplay();
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
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
    return shieldOK;
}

bool ScreenEncoder::sensorStart(void)
{
    /*
    TODO: Write description and comments
    */

    bool sensorOK = false;
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 19, true);
    display.display();
    delay(delayScreen);
#if defined(SENSOR_BME280)
    mySensor.bmeStart();
#endif
#ifdef ACCELEROMETER_ON
    fP->imuFlag = mySensor.startIMU();
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
    return sensorOK;
}

void ScreenEncoder::finishSetup(void)
{
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    ScreenEncoder::showText(17, 36, oledMessage_table, 44, true);
    display.display();
    delay(delayScreen);
}

void ScreenEncoder::displayInitial(void)
{
    /*
    TODO: Write description and comments
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 7, false);
    ScreenEncoder::dispWarning(108, 5);
    ScreenEncoder::showText(5, 20, oledMessage_table, 12, false);
    ScreenEncoder::showText(5, 33, oledMessage_table, 13, false);
    ScreenEncoder::showText(5, 46, oledMessage_table, 14, false);
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
    TODO: Write description and comments
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(25, 5, 1, false, oledMessage_table, 11, false);
    if (ST_STATUS == HIGH && SENSOR_STATUS == LOW)
    {
        ScreenEncoder::showText(3, 19, oledMessage_table, 30, false);
        display.setCursor(45, 19);
        display.print(eP->deviceParameters[0]);
        DEBUG_SCREEN(F("encDist: "));
        DEBUG_SCREENLN(eP->deviceParameters[0]);
        ScreenEncoder::showText(64, 19, oledMessage_table, 31, false);
        display.setCursor(108, 19);
        display.print(eP->deviceParameters[1]);
        DEBUG_SCREEN(F("camRes: "));
        DEBUG_SCREENLN(eP->deviceParameters[1]);
        ScreenEncoder::showText(3, 29, oledMessage_table, 36, false);
        display.setCursor(45, 29);
        display.print(eP->deviceParameters[6]);
        DEBUG_SCREEN(F("patCurr: "));
        DEBUG_SCREENLN(eP->deviceParameters[6]);
        ScreenEncoder::showText(64, 29, oledMessage_table, 35, false);
        display.setCursor(102, 29);
        display.print(eP->deviceParameters[5]);
        DEBUG_SCREEN(F("tSample: "));
        DEBUG_SCREENLN(eP->deviceParameters[5]);
        ScreenEncoder::showText(3, 39, oledMessage_table, 34, false);
        display.setCursor(45, 39);
        display.print(eP->deviceParameters[4]);
        DEBUG_SCREEN(F("outFilter: "));
        DEBUG_SCREENLN(eP->deviceParameters[4]);
        ScreenEncoder::showText(64, 39, oledMessage_table, 33, false);
        display.setCursor(108, 39);
        display.print(eP->deviceParameters[3]);
        DEBUG_SCREEN(F("inFilter: "));
        DEBUG_SCREENLN(eP->deviceParameters[3]);
        ScreenEncoder::showText(3, 49, oledMessage_table, 32, false);
        display.setCursor(45, 49);
        display.print(eP->deviceParameters[2]);
        DEBUG_SCREEN(F("patRes: "));
        DEBUG_SCREENLN(eP->deviceParameters[2]);
    }
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
    TODO: Write description and comments
    */
    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(25, 5, 1, false, oledMessage_table, 43, false);
    if (ENCODER_ENABLE)
    {
        display.drawBitmap(3, 20, oledIcon_6, 23, 21, WHITE);
        display.setTextSize(2);
        display.setCursor(30, 34);
        mySystem.readEncoder();
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
    TODO: Write description and comments
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(22, 5, 1, false, oledMessage_table, 10, false);
#ifdef SHIELD_ON
    if (fP->eFlag)
    {
        ScreenEncoder::showText(5, 20, oledMessage_table, 23, false);
        display.setCursor(50, 20);
        display.print(eP->deviceIndex);
        ScreenEncoder::showText(5, 30, oledMessage_table, 24, false);
        display.setCursor(50, 30);
        String myIP = "192.168.1." + String(20 + eP->deviceIndex);
        display.print(myIP);
        DEBUG_SCREEN(F("Local IP: "));
        DEBUG_SCREENLN(ip);
        ScreenEncoder::showText(5, 39, oledMessage_table, 25, false);
        display.setCursor(5, 48);
        String myMac = String(eP->mac[0], HEX) + ":" + String(eP->mac[1], HEX) + ":" + String(eP->mac[2], HEX) +
                       ":" + String(eP->mac[3], HEX) + ":" + String(eP->mac[4], HEX) + ":" + String(eP->mac[5], HEX);
        display.print(myMac);
        DEBUG_SCREEN(F("MAC Address: "));
        DEBUG_SCREEN(myMac);
        DEBUG_SCREENLN(F(""));
    }
    else
    {
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
    TODO: Write description and comments
    */

    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(35, 5, 1, false, oledMessage_table, 9, true);
#ifdef ACCELEROMETER_ON
    int16_t cursorX, cursorY;
    display.cp437(true);
    display.drawBitmap(24, 19, oledIcon_5, 17, 17, WHITE);
    mySensor.imuRead();
    display.drawCircle(96, 36, 6, WHITE);
    display.fillCircle(iP->outputX, iP->outputY, 4, WHITE);
    display.setCursor(4, 36);
    display.write(233);
    display.print("x:");
    display.setCursor(22, 36);
    display.print(iP->angX, 1);
    display.setCursor(55, 36);
    display.write(167);
    display.setCursor(4, 46);
    display.write(233);
    display.print("z:");
    display.print(iP->angZ, 1);
    display.setCursor(55, 46);
    display.write(167);
#else
    ScreenEncoder::showText(5, 34, oledMessage_table, 42, true);
#endif
    display.display();
}

void ScreenEncoder::displayTempHum(void)
{
    display.clearDisplay();
    ScreenEncoder::displayIndicator(sP->displayScreenNum);
    ScreenEncoder::frameHeader(5, 5, 1, false, oledMessage_table, 8, false);
    if (fP->tFlag)
    {
        DEBUG_SCREEN(F("bmeTemp: "));
        DEBUG_SCREENLN(sP->tC);
        DEBUG_SCREEN(F("bmeHum: "));
        DEBUG_SCREENLN(sP->hP);
        display.drawBitmap(10, 22, oledIcon_3, 16, 16, WHITE);
        display.drawBitmap(10, 39, oledIcon_4, 16, 16, WHITE);
        ScreenEncoder::setDisp(2, false, 35, 22, true);
        display.print(sP->tC);
        display.setCursor(35, 39);
        display.print(sP->hP);
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
    */
    display.drawRect(0, 0, 128, 16, WHITE);  // draw upper frame
    display.drawRect(0, 17, 128, 47, WHITE); // draw lower frame

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
    - Function that displays a warning sign (!) on main screen
    - sysOK flag is not true, to let the user knows that there is a problem
    - with the encoder
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
    - Function that displays the small indicator circles of the screen bottom
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
    TODO: Write description and comments
    */

    const uint8_t displayScreenNumMax = 5;
    const uint32_t waitScreen = 300000;
    static bool offFlag;

    if (fP->toggleScreen == fP->prevTogScr && fP->onScreen == true)
    {
        DEBUG_SCREENLN(F("Button not pressed, time is running"));
        if (offFlag == true)
        {
            DEBUG_SCREENLN(F("offFlag is true, shutting down screen"));
            sP->displayScreenNum = 6;
            offFlag = false;
        }
        else if (millis() > sP->mTimerCounter + waitScreen)
        {
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
        DEBUG_SCREENLN(F("Screen is off, waiting for restart"));
    }
#endif
    else if (fP->toggleScreen != fP->prevTogScr)
    {
        fP->prevTogScr = fP->toggleScreen;
        if (fP->onScreen == true)
        {
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
            DEBUG_SCREENLN(F("Screen was off, i'm waking it on"));
            sP->displayScreenNum = 7;
        }
    }
}

void ScreenEncoder::displaySleep(void)
{
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    fP->onScreen = false;
}

void ScreenEncoder::displayWake(void)
{
    display.ssd1306_command(SSD1306_DISPLAYON);
    fP->onScreen = true;
}
