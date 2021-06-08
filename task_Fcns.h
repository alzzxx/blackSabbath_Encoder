
void stCheck(void)
{
  /*
  - Function to control st and pixart status, if the encoder if in error mode
  - start UDP and send packet with deviceStatus byte to plc for diagnose

  */
  PIN_UP;
  DEBUG_TASKSLN(F("Checking pixart and ST"));
  if (SENSOR_STATUS == HIGH)
  {
    fP->patFlag = true;
    DEBUG_TASKS(F("Pixart error"));
  }
  else
  {
    fP->patFlag = false;
    DEBUG_TASKSLN(F("Pixart OK"));
  }
  if (ST_STATUS == LOW)
  {
    fP->stFlag = false;
    DEBUG_TASKSLN(F("ST ok"));
  }
  else
  {
    DEBUG_TASKS(F("ST error"));
    fP->stFlag = true;
    sP->diagBuffer[0] = deviceStatus;
#ifdef UDP_ON
    delay(10);
    mySystem.writeUDP(sP->diagBuffer, sizeof(sP->diagBuffer), remote, eP->remotePort);
#endif
    DEBUG_TASKS(F("deviceStatus is: "));
    DEBUG_TASKSLN(sP->diagBuffer[0]);
  }
  PIN_DOWN;
}

void checkSystems(void)
{
  /*
  - Function to check secondary systems, check all flags
  - and set o clear sysOK flag
  */

  PIN_UP;
#ifdef SHIELD_ON
  if (fP->tFlag && fP->eFlag && fP->extMemFlag && fP->imuFlag)
  {
    fP->sysOK = true;
    DEBUG_TASKSLN(F("Systems ok!"));
  }
  else
  {
    fP->sysOK = false;
    DEBUG_TASKSLN(F("Systems not OK :("));
  }
#else
  if (fP->tFlag && ETHERNET_STATUS && IS_SERVER_ON && fP->extMemFlag && fP->imuFlag)
  {
    fP->sysOK = true;
    DEBUG_TASKSLN(F("Systems ok!"));
  }
  else
  {
    fP->sysOK = false;
    DEBUG_TASKSLN(F("Systems not OK :("));
  }
#endif
  PIN_DOWN;
}

void updateButton(void)
{
  /*
    Function that updates button reading
    */

  button.read();
}

#if defined(SENSOR_BME280)
void tempUpdate(void)
{
  /*
  Function to update temperature/humidity values from BME280
  */

  PIN_UP;
#ifdef SENSOR_BME280
  sP->tC = READ_TEMPERATURE;
  sP->hP = READ_HUMIDITY;
  sP->bPre = READ_PRESSURE;
#endif

  if (sP->tC > 0 && sP->hP > 0)
  {
    fP->tFlag = true;
    DEBUG_TASKSLN(F("tempSensor OK"));
  }
  else
  {
    fP->tFlag = false;
    DEBUG_TASKSLN(F("Problem with tempSensor, check wiring"));
  }
  PIN_DOWN;
}
#endif

#ifdef EXTMEMORY_ON
void extEEPROMupdate(void)
{
  /*
  Function to check if extEEPROM is alive
  */

  PIN_UP;
  if (!myEEPROM.isConnected(eepromAddress))
  {
    DEBUG_TASKSLN(F("Problem with extEEPROM, check wiring"));
    fP->extMemFlag = false;
  }
  else
  {
    DEBUG_TASKSLN(F("extEEPROM ok"));
    fP->extMemFlag = true;
  }
  PIN_DOWN;
}
#endif

#ifdef ACCELEROMETER_ON
void imuUpdate(void)
{
  /*
  Function to check if the imu is alive
  */

  PIN_UP;
  if (IMU.begin() == false)
  {
    DEBUG_TASKSLN(F("Problem with IMU"));
    fP->imuFlag = false;
  }
  else
  {
    DEBUG_TASKSLN(F("IMU ok"));
    fP->imuFlag = true;
  }
  PIN_DOWN;
}
#endif

#ifdef WEBSERVER_ON
void statusRead(void)
{
  PIN_UP;
  fP->statusReadFlag = true;
  PIN_DOWN;
}

void webServerArdST()
{
  /*
  - Function that shows the webServer
  */

  PIN_UP;
  fP->saveParameters = myServer.displayWebServer() || fP->saveParameters;
  PIN_DOWN;
}

void serverStatus(void)
{
  /*
  - Function to check is server if alive, if it not
  - try to restart it
  */

  PIN_UP;
  if (ETHERNET_STATUS == LinkON && server)
  {
    fP->eFlag = true;
    DEBUG_TASKSLN(F("Ethernet OK"));
#ifdef DEBUG_ETHERNET
    if (ETHERNET_STATUS == LinkOFF)
      DEBUG_SCREENLN("LINKOFF");
    else if (ETHERNET_STATUS == LinkON)
      DEBUG_SCREENLN("LINKON");
    else if (ETHERNET_STATUS == Unknown)
      DEBUG_SCREENLN("UNKNOWN");
    if (server)
      DEBUG_SCREENLN("Server true");
    else
      DEBUG_SCREENLN("Server false");
#endif
  }
  else if (ETHERNET_STATUS == LinkOFF || !server)
  {
    fP->eFlag = false;
    DEBUG_SCREENLN(F("Ethernet shield error"));
#ifdef DEBUG_ETHERNET
    if (ETHERNET_STATUS == LinkOFF)
      DEBUG_SCREENLN("LINKOFF");
    else if (ETHERNET_STATUS == LinkON)
      DEBUG_SCREENLN("LINKON");
    else if (ETHERNET_STATUS == Unknown)
      DEBUG_SCREENLN("UNKNOWN");
    if (server)
      DEBUG_SCREENLN("Server true");
    else
      DEBUG_SCREENLN("Server false");
#endif
  }
  PIN_DOWN;
}

void spiSTM(void)
{
  /*
  - Function that handles spi communication between arduino and ST
  */

  PIN_UP;

  if (ENCODER_ENABLE)
  {
    ENABLE_ENCODER_HI;
  }
  else if (ENCODER_DISABLE)
  {
    DISABLE_ENCODER_LO;
  }
  if (fP->saveParameters)
  {

    // statusRead();
    DEBUG_SERVERLN(F("Sending parameters"));
    SPIerrorIndex = myServer.sendParameters();
    // TODO here start the thing for saying to webserver "hey param transmitted OK"
    DEBUG_SERVER(F("SPI return: "));
    DEBUG_SERVERLN(SPIerrorIndex);
  }
  if (fP->statusReadFlag == true && fP->saveParameters == false)
  {
    int errorCnt = 0;
    uint16_t readTemp = 0;
    if (!(PLC_STATUS))
    { // do this only if STM is in SPI mode, and not running as encoder
      while (1)
      { //Try 200 times to read the variable
        if (myServer.spiReadArd2STM(spiStatusAddress, &readTemp, ST_PIN_NSS))
        {
          break;
        }
        else
        {
          errorCnt++;
          if (errorCnt >= spiErrorLimit)
          {
            readTemp = spiError << 8;
            break;
          }
        }
      }
      myServer.updateDeviceStatus(readTemp);
    }
    fP->statusReadFlag = 0;
  }
  fP->saveParameters = false;
  PIN_DOWN;
}
#endif

#ifdef SCREEN_ON
void updateScreen(void)
{
  /*
  - Function that handle oled Display, it changes
  - between the differents screen according to user decision
  */

  PIN_UP;
  myScreen.updateScreenNum();
  switch (sP->displayScreenNum)
  {
  case 0:
    myScreen.displayInitial();
    break;

  case 1:
    myScreen.displayPixVal();
    break;

  case 2:
    myScreen.displayFreqSpeed();
    break;

  case 3:
    myScreen.displayIPMAC();
    break;

  case 4:
    myScreen.displayDigitalLevel();
    break;

  case 5:
    myScreen.displayTempHum();
    break;

  case 6:
    myScreen.displaySleep();
    sP->displayScreenNum = 8;
    break;

  case 7:
    myScreen.displayWake();
    sP->displayScreenNum = 0;
    break;

  default:
    DEBUG_SCREENLN(F("Call to updateScreen, but the screen is off"));
    delayMicroseconds(1);
    break;
  }
  PIN_DOWN;
}
#endif
