
void BestEncoder::startScreen(void)
{
    /*
    Function that starts the oled screen, there are different configurations according to the hardware used
    if the screen don't start, the program remains blocked
    */

#if defined(ARDUINO_NANO) && defined(SSD1306_I2C)
    while (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
    {
        DEBUG_BOOTLN(F("SSD1306 allocation failed"));
    }
#endif

    // if the screen starts show debug info and move on
    onScreen = true;
    DEBUG_BOOTLN(F("Screen started"));
    DEBUG_DELAY(1000);
    display.clearDisplay();
    display.display();
}

void BestEncoder::frameHeader(uint8_t cursorX, uint8_t cursorY, uint8_t sizeText, bool varInverted, const char *const buffer[], uint8_t num, bool isAccelerometer)
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

    BestEncoder::setDisp(sizeText, varInverted, 0, 0, false);   // set text settings
    BestEncoder::showText(cursorX, cursorY, buffer, num, true); // display header message
}

void BestEncoder::showText(uint16_t xCursor, uint16_t yCursor, const char *const bufferText[], uint8_t bufferNumber, bool isCentered)
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
        uint16_t xPosition = (SCREEN_WIDHT - stringWidth) / 2;                                                    // calculate xposition of the string using its width
        display.setCursor(xPosition, yCursor);                                                                    // set cursor with the calculated coordinates
    }
    else
    {
        display.setCursor(xCursor, yCursor); // if text is not centered set cursor with the input parameters
    }
    display.print(bufferText[bufferNumber]); // show message
}

void BestEncoder::setDisp(uint8_t textSize, bool isInverted, uint8_t xCursor, uint8_t yCursor, bool isCursor)
{
    /*
    TODO: Write description and comments
    */

    display.setTextSize(textSize);
    if (isInverted)
        display.setTextColor(BLACK, WHITE);
    else
        display.setTextColor(WHITE);
    if (isCursor)
        display.setCursor(xCursor, yCursor);
}

void BestEncoder::dispWarning(uint8_t xCursor, uint8_t yCursor)
{
    /*
    TODO: Write description and comments
    */

    if (!flagPoint->sysOK)
    {
        display.cp437(true);
        display.setCursor(xCursor, yCursor);
        display.write(40);
        display.write(33);
        display.write(41);
    }
}

void BestEncoder::displayIndicator(uint8_t displayNumber)
{
    /*
    TODO: Write description and comments
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

void BestEncoder::updateScreenNum(void)
{
    /*
    TODO: Write description and comments
    */

    const uint8_t displayScreenNumMax = 5;
    const uint32_t waitScreen = 300000;
    static bool offFlag;

    if (flagPoint->toggleScreen == prevTogScr && onScreen == true)
    {
        DEBUG_SCREENLN(F("Button not pressed, time is running"));
        if (offFlag == true)
        {
            DEBUG_SCREENLN(F("offFlag is true, shutting down screen"));
            displayScreenNum = 6;
            offFlag = false;
        }
        else if (millis() > mTimerCounter + waitScreen)
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
    else if (flagPoint->toggleScreen == prevTogScr && onScreen == false)
    {
        DEBUG_SCREENLN(F("Screen is off, waiting for restart"));
    }
#endif
    else if (flagPoint->toggleScreen != prevTogScr)
    {
        prevTogScr = flagPoint->toggleScreen;
        if (onScreen == true)
        {
            if (displayScreenNum < displayScreenNumMax)
            {
                displayScreenNum++;
            }
            else
            {
                displayScreenNum = 0;
            }
        }
        else
        {
            DEBUG_SCREENLN(F("Screen was off, i'm waking it on"));
            displayScreenNum = 7;
        }
    }
}

void BestEncoder::displayInitial(void)
{
    /*
    TODO: Write description and comments
    */

    display.clearDisplay();
    BestEncoder::displayIndicator(displayScreenNum);
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 7, false);
    BestEncoder::dispWarning(108, 5);
    BestEncoder::showText(5, 20, oledMessage_table, 12, false);
    BestEncoder::showText(5, 33, oledMessage_table, 13, false);
    BestEncoder::showText(5, 46, oledMessage_table, 14, false);
    if (flagPoint->patFlag)
    {
        BestEncoder::setDisp(1, true, 0, 0, false);
        BestEncoder::showText(80, 20, oledMessage_table, 16, false);
        DEBUG_SCREENLN(F("Pixart error"));
    }
    else
    {
        BestEncoder::setDisp(1, true, 0, 0, false);
        BestEncoder::showText(80, 20, oledMessage_table, 15, false);
        DEBUG_SCREENLN(F("Pixart OK"));
    }
    if (flagPoint->stFlag)
    {
        BestEncoder::setDisp(1, true, 0, 0, false);
        BestEncoder::showText(80, 33, oledMessage_table, 16, false);
        DEBUG_SCREENLN(F("ST error"));
    }
    else
    {
        BestEncoder::setDisp(1, true, 0, 0, false);
        BestEncoder::showText(80, 33, oledMessage_table, 15, false);
        DEBUG_SCREENLN(F("ST OK"));
    }
    if (PLC_STATUS == HIGH)
    {
        BestEncoder::setDisp(1, true, 0, 0, false);
        BestEncoder::showText(80, 46, oledMessage_table, 17, false);
        DEBUG_SCREENLN(F("PLC enable"));
    }
    else
    {
        BestEncoder::setDisp(1, true, 0, 0, false);
        BestEncoder::showText(80, 46, oledMessage_table, 18, false);
        DEBUG_SCREENLN(F("PLC off"));
    }
    display.display();
}

void BestEncoder::displayTempHum(void)
{
    display.clearDisplay();
    BestEncoder::displayIndicator(displayScreenNum);
    BestEncoder::frameHeader(5, 5, 1, false, oledMessage_table, 8, false);
    if (flagPoint->tFlag)
    {
        DEBUG_SCREEN(F("bmeTemp: "));
        DEBUG_SCREENLN(secPoint->tC);
        DEBUG_SCREEN(F("bmeHum: "));
        DEBUG_SCREENLN(secPoint->hP);
        display.drawBitmap(10, 22, oledIcon_3, 16, 16, WHITE);
        display.drawBitmap(10, 39, oledIcon_4, 16, 16, WHITE);
        BestEncoder::setDisp(2, false, 35, 22, true);
        display.print(secPoint->tC);
        display.setCursor(35, 39);
        display.print(secPoint->hP);
        display.cp437(true);
        BestEncoder::setDisp(1, false, 97, 22, true);
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
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 22, true);
    }
    display.display();
}

void BestEncoder::displayDigitalLevel(void)
{
    /*
    TODO: Write description and comments
    */

    display.clearDisplay();
    BestEncoder::displayIndicator(displayScreenNum);
    BestEncoder::frameHeader(35, 5, 1, false, oledMessage_table, 9, true);
#ifdef ACCELEROMETER_ON
    int16_t cursorX, cursorY;
    display.cp437(true);
    display.drawBitmap(24, 19, oledIcon_5, 17, 17, WHITE);
    BestEncoder::imuRead();
    display.drawCircle(96, 36, 6, WHITE);
    if (imuPoint->outputX < 69)
        cursorX = 69;
    else if (imuPoint->outputX > 122)
        cursorX = 122;
    else
        cursorX = imuPoint->outputX;
    if (imuPoint->outputY < 22)
        cursorY = 22;
    else if (imuPoint->outputY > 50)
        cursorY = 50;
    else
        cursorY = imuPoint->outputY;
    display.fillCircle(cursorX, cursorY, 4, WHITE);
    display.setCursor(4, 36);
    display.write(233);
    display.print("x:");
    display.setCursor(22, 36);
    display.print(imuPoint->angX, 1);
    display.setCursor(55, 36);
    display.write(167);
    display.setCursor(4, 46);
    display.write(233);
    display.print("z:");
    display.print(imuPoint->angZ, 1);
    display.setCursor(55, 46);
    display.write(167);
#else
    BestEncoder::showText(5, 34, oledMessage_table, 42, true);
#endif
    display.display();
}

void BestEncoder::displayIPMAC(void)
{
    /*
    TODO: Write description and comments
    */

    display.clearDisplay();
    BestEncoder::displayIndicator(displayScreenNum);
    BestEncoder::frameHeader(22, 5, 1, false, oledMessage_table, 10, false);
#ifdef SHIELD_ON
    if (flagPoint->eFlag)
    {
        BestEncoder::showText(5, 20, oledMessage_table, 23, false);
        display.setCursor(50, 20);
        display.print(encPoint->deviceIndex);
        BestEncoder::showText(5, 30, oledMessage_table, 24, false);
        display.setCursor(50, 30);
        String myIP = "192.168.1." + String(20 + encPoint->deviceIndex);
        display.print(myIP);
        DEBUG_SCREEN(F("Local IP: "));
        DEBUG_SCREENLN(ip);
        BestEncoder::showText(5, 39, oledMessage_table, 25, false);
        display.setCursor(5, 48);
        String myMac = String(encPoint->mac[0], HEX) + ":" + String(encPoint->mac[1], HEX) + ":" + String(encPoint->mac[2], HEX) +
                       ":" + String(encPoint->mac[3], HEX) + ":" + String(encPoint->mac[4], HEX) + ":" + String(encPoint->mac[5], HEX);
        display.print(myMac);
        DEBUG_SCREEN(F("MAC Address: "));
        DEBUG_SCREEN(myMac)
        DEBUG_SCREENLN(F(""));
    }
    else
    {
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 26, true);
    }
#endif
#ifndef SHIELD_ON
    BestEncoder::showText(5, 20, oledMessage_table, 23, false);
    display.setCursor(47, 20);
    display.print(encPoint->deviceIndex);
    BestEncoder::showText(5, 30, oledMessage_table, 24, false);
    display.setCursor(47, 30);
    display.cp437(true);
    for (uint8_t i = 0; i < 4; i++)
    {
        display.print(ip[i], DEC);
        if (i < 3)
            display.write(46);
    }
    BestEncoder::showText(5, 39, oledMessage_table, 25, false);
    display.setCursor(5, 48);
    for (uint8_t i = 0; i < 6; i++)
    {
        display.print(encPoint->mac[i], HEX);
        if (i < 5)
        {
            display.write(58);
        }
    }
#endif
    display.display();
}

void BestEncoder::displayPixVal(void)
{
    /*
    TODO: Write description and comments
    */

    display.clearDisplay();
    BestEncoder::displayIndicator(displayScreenNum);
    BestEncoder::frameHeader(25, 5, 1, false, oledMessage_table, 11, false);
    if (ST_STATUS == LOW && SENSOR_STATUS == LOW)
    {
        BestEncoder::showText(3, 19, oledMessage_table, 30, false);
        display.setCursor(45, 19);
        display.print(encPoint->deviceParameters[0]);
        DEBUG_SCREEN(F("encDist: "));
        DEBUG_SCREENLN(encPoint->deviceParameters[0]);
        BestEncoder::showText(64, 19, oledMessage_table, 31, false);
        display.setCursor(108, 19);
        display.print(encPoint->deviceParameters[1]);
        DEBUG_SCREEN(F("camRes: "));
        DEBUG_SCREENLN(encPoint->deviceParameters[1]);
        BestEncoder::showText(3, 29, oledMessage_table, 36, false);
        display.setCursor(45, 29);
        display.print(encPoint->deviceParameters[6]);
        DEBUG_SCREEN(F("patCurr: "));
        DEBUG_SCREENLN(encPoint->deviceParameters[6]);
        BestEncoder::showText(64, 29, oledMessage_table, 35, false);
        display.setCursor(102, 29);
        display.print(encPoint->deviceParameters[5]);
        DEBUG_SCREEN(F("tSample: "));
        DEBUG_SCREENLN(encPoint->deviceParameters[5]);
        BestEncoder::showText(3, 39, oledMessage_table, 34, false);
        display.setCursor(45, 39);
        display.print(encPoint->deviceParameters[4]);
        DEBUG_SCREEN(F("outFilter: "));
        DEBUG_SCREENLN(encPoint->deviceParameters[4]);
        BestEncoder::showText(64, 39, oledMessage_table, 33, false);
        display.setCursor(108, 39);
        display.print(encPoint->deviceParameters[3]);
        DEBUG_SCREEN(F("inFilter: "));
        DEBUG_SCREENLN(encPoint->deviceParameters[3]);
        BestEncoder::showText(3, 49, oledMessage_table, 32, false);
        display.setCursor(45, 49);
        display.print(encPoint->deviceParameters[2]);
        DEBUG_SCREEN(F("patRes: "));
        DEBUG_SCREENLN(encPoint->deviceParameters[2]);
    }
    else
    {
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        BestEncoder::showText(25, 43, oledMessage_table, 4, true);
    }
    display.display();
}

void BestEncoder::displayFreqSpeed(void)
{
    /*
    TODO: Write description and comments
    */
    display.clearDisplay();
    BestEncoder::displayIndicator(displayScreenNum);
    BestEncoder::frameHeader(25, 5, 1, false, oledMessage_table, 43, false);
    if (PLC_STATUS == HIGH)
    {
        display.drawBitmap(3, 20, oledIcon_6, 23, 21, WHITE);
        display.setTextSize(2);
        display.setCursor(30, 34);
        BestEncoder::readEncoder();
        display.print(secPoint->encFreq);
        display.setTextSize(2);
        display.setCursor(80, 34);
        display.print("kHz");
    }
    else
    {
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        BestEncoder::showText(25, 43, oledMessage_table, 45, true);
    }
    display.display();
}

void BestEncoder::displaySleep(void)
{
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    onScreen = false;
}

void BestEncoder::displayWake(void)
{
    display.ssd1306_command(SSD1306_DISPLAYON);
    onScreen = true;
}

void BestEncoder::splashScreen(void)
{
    /*
    TODO: Write description and comments
    */

    display.drawBitmap(0, 5, oledIcon_2, 128, 64, WHITE);
    display.display();
    delay(DELAY_SCREEN);
    display.clearDisplay();
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    BestEncoder::setDisp(1, false, 0, 0, false);
    BestEncoder::showText(35, 30, oledMessage_table, 0, true);
    BestEncoder::showText(42, 40, oledMessage_table, 1, true);
    display.display();
    DEBUG_BOOTLN(F("Encoder BS"));
    DEBUG_BOOTLN(F("V 1.0.0"));
    delay(DELAY_SCREEN);
    display.clearDisplay();
    display.display();
}

void BestEncoder::initialCheck(void)
{
    /*
    TODO: Write description and comments
    */

    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    BestEncoder::showText(17, 36, oledMessage_table, 3, true);
    display.display();
    delay(DELAY_SCREEN);
    while (!(SENSOR_STATUS == LOW && ST_STATUS == LOW))
    {
        DEBUG_BOOTLN(F("Pixart sensor error"));
        display.clearDisplay();
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
        BestEncoder::showText(25, 43, oledMessage_table, 4, true);
        display.display();
    }
    DEBUG_BOOTLN(F("Pixart sensor started"));
    display.clearDisplay();
    display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    BestEncoder::showText(20, 43, oledMessage_table, 5, true);
    display.display();
    delay(DELAY_SCREEN);
    display.clearDisplay();
    display.display();
}

bool BestEncoder::initParam(void)
{
    /*
    TODO: Write description and comments
    */

    bool eepromOK;
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    BestEncoder::showText(17, 36, oledMessage_table, 37, true);
    display.display();
    delay(DELAY_SCREEN);
    display.clearDisplay();
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
#ifdef EXTMEMORY_ON
    if (readParam() == 0)
    {
        display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 39, true);
        eepromOK = true;
    }
    else
    {
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 40, true);
        eepromOK = false;
    }
#else
    DEBUG_BOOTLN(F("ExtEEPROM not present, moving on"));
    BestEncoder::setDisp(1, false, 0, 0, false);
    BestEncoder::showText(17, 43, oledMessage_table, 38, true);
    eepromOK = true;
#endif
    display.display();
    delay(DELAY_SCREEN);
    display.clearDisplay();
    display.display();
    return eepromOK;
}

bool BestEncoder::sensorStart(void)
{
    /*
    TODO: Write description and comments
    */

    bool sensorOK = false;
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    BestEncoder::showText(17, 36, oledMessage_table, 19, true);
    display.display();
    delay(DELAY_SCREEN);
#if defined(SENSOR_BME280)
    BestEncoder::bmeStart();
#elif defined(SENSOR_AHT10)
    BestEncoder::ahtStart();
#endif
#ifdef ACCELEROMETER_ON
    flagPoint->imuFlag = BestEncoder::startIMU();
#endif
    display.clearDisplay();
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    if (flagPoint->tFlag && flagPoint->imuFlag)
    {
        DEBUG_BOOTLN(F("All sensor started"));
        display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 20, true);
        sensorOK = true;
    }
    else
    {
        DEBUG_BOOTLN(F("Some sensor failed, check wiring"));
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 21, true);
        sensorOK = false;
    }
    display.display();
    delay(DELAY_SCREEN);
    display.clearDisplay();
    display.display();
    return sensorOK;
}

bool BestEncoder::shieldStart(void)
{
    /*
    TODO: Write description and comments
    */

    bool shieldOK = false;
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    BestEncoder::showText(17, 36, oledMessage_table, 27, true);
    display.display();
    delay(DELAY_SCREEN);
    display.clearDisplay();
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
#ifdef SHIELD_ON
    if (bootShield())
    {
        DEBUG_BOOTLN(F("Ethernet shield started"));
        display.drawBitmap(55, 23, oledIcon_0, 18, 17, WHITE);
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 28, true);
        shieldOK = true;
    }
    else
    {
        DEBUG_BOOTLN(F("Check ethernet shield"));
        display.drawBitmap(55, 22, oledIcon_1, 18, 19, WHITE);
        BestEncoder::setDisp(1, false, 0, 0, false);
        BestEncoder::showText(17, 43, oledMessage_table, 29, true);
        shieldOK = false;
    }
#else
    DEBUG_BOOTLN(F("Shield not present, moving on"));
    BestEncoder::setDisp(1, false, 0, 0, false);
    BestEncoder::showText(17, 43, oledMessage_table, 2, true);
    shieldOK = true;
#endif
    display.display();
    delay(DELAY_SCREEN);
    display.clearDisplay();
    display.display();
    return shieldOK;
}

void BestEncoder::finishSetup(void)
{
    BestEncoder::frameHeader(23, 5, 1, false, oledMessage_table, 6, false);
    BestEncoder::showText(17, 36, oledMessage_table, 44, true);
    display.display();
    delay(DELAY_SCREEN);
}
