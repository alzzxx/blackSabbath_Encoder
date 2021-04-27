
void stCheck(void)
{
  /*
  Function to control st and pixart status
  */
  DEBUG_TASKSLN(F("checking pixart and ST"));
  if (SENSOR_STATUS == HIGH)
  {
    flagPoint->patFlag = true;
    DEBUG_TASKS(F("Pixart error"));
  }
  else
  {
    flagPoint->patFlag = false;
    DEBUG_TASKS(F("Pixart OK"));
  }
  if (ST_STATUS == LOW)
  {
    flagPoint->stFlag = false;
    DEBUG_TASKS(F("ST ok"));
  }
  else
  {
    DEBUG_TASKS(F("ST error"));
    flagPoint->stFlag = true;
    diagBuffer[0] = deviceStatus;
#ifdef UDP_ON
    myEncoder.writeUDP(diagBuffer, sizeof(diagBuffer), remote, encPoint->remotePort);
#endif
    DEBUG_TASKS(F("deviceStatus is: "));
    DEBUG_TASKSLN(diagBuffer[0]);
  }
}

#if defined(SENSOR_BME280) || defined(SENSOR_AHT10)
void tempUpdate(void)
{
  /*
  Function to update temperature/humidity values from BME280
  */
#ifdef SENSOR_AHT10
  UPDATE_AHT;
#endif
  secPoint->tC = READ_TEMPERATURE;
  secPoint->hP = READ_HUMIDITY;
#ifdef SENSOR_BME280
  secPoint->bPre = READ_PRESSURE;
#endif
  if (secPoint->tC > 0 && secPoint->hP > 0)
  {
    flagPoint->tFlag = true;
    DEBUG_TASKSLN(F("tempSensor OK"));
  }
  else
  {
    flagPoint->tFlag = false;
    DEBUG_TASKSLN(F("Problem with tempSensor, check wiring"));
  }
}
#endif

#ifdef EXTMEMORY_ON
void extEEPROMupdate(void)
{
  /*
  Function to check if extEEPROM is alive
  */

  if (!myEEPROM.isConnected(EEPROM_ADDRESS))
  {
    DEBUG_TASKSLN(F("Problem with extEEPROM, check wiring"));
    flagPoint->extMemFlag = false;
  }
  else
  {
    DEBUG_TASKSLN(F("extEEPROM ok"));
    flagPoint->extMemFlag = true;
  }
}
#endif

#ifdef ACCELEROMETER_ON
void imuUpdate(void)
{
  /*
  Function to check if the imu is alive
  */

  if (IMU.begin() == false)
  {
    DEBUG_TASKSLN(F("Problem with IMU"));
    flagPoint->imuFlag = false;
  }
  else
  {
    DEBUG_TASKSLN(F("IMU ok"));
    flagPoint->imuFlag = true;
  }
}
#endif

void checkSystems(void)
{
  /*
  Function to check secondary systems
  */
#ifdef SHIELD_ON
  if (flagPoint->tFlag && flagPoint->eFlag && flagPoint->extMemFlag && flagPoint->imuFlag)
  {
    flagPoint->sysOK = true;
    DEBUG_TASKSLN(F("Systems ok!"));
  }
  else
  {
    flagPoint->sysOK = false;
    DEBUG_TASKSLN(F("Systems not OK :("));
  }
#else
  if (flagPoint->tFlag && ETHERNET_STATUS && IS_SERVER_ON && flagPoint->extMemFlag && flagPoint->imuFlag)
  {
    flagPoint->sysOK = true;
    DEBUG_TASKSLN(F("Systems ok!"));
  }
  else
  {
    flagPoint->sysOK = false;
    DEBUG_TASKSLN(F("Systems not OK :("));
  }
#endif
}

#ifdef WEBSERVER_ON
void statusRead(void)
{
  statusReadFlag = true;
}

void webServerArdST()
{
  saveParameters = displayWebServer() || saveParameters;
}

void serverStatus(void)
{
  if (ETHERNET_STATUS == LinkON && server)
  {
    flagPoint->eFlag = true;
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
    flagPoint->eFlag = false;
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
}

void spiSTM(void)
{
  if (saveParameters)
  {
    //   statusRead();
    DEBUG_SERVERLN(F("sending parameters"));
    SPIerrorIndex = SendParameters();
    // TODO here start the thing for saying to webserver "hey param transmitted OK"
    DEBUG_SERVER(F(" SPI return: "));
    DEBUG_SERVERLN(SPIerrorIndex);
  }
  if (statusReadFlag == 1 && saveParameters == 0)
  {
    int errorCnt = 0;
    uint16_t readTemp = 0;
    if (!(PLC_STATUS))
    { // do this only if STM is in SPI mode, and not running as encoder
      while (1)
      { //Try 200 times to read the variable
        if (SpiReadArd2STM(SPI_STATUS_ADDRESS, &readTemp, ST_PIN_NSS))
        {
          break;
        }
        else
        {
          errorCnt++;
          if (errorCnt >= ERROR_SPI_LIMIT)
          {
            readTemp = SPI_ERROR << 8;
            break;
          }
        }
      }
      updateDeviceStatus(readTemp);
    }
    statusReadFlag = 0;
  }
  saveParameters = 0;
}
#endif

#ifdef SCREEN_ON
void updateScreen(void)
{
  // TODO : write description
  myEncoder.updateScreenNum();
  switch (displayScreenNum)
  {
  case 0:
    myEncoder.displayInitial();
    break;

  case 1:
    myEncoder.displayPixVal();
    break;

  case 2:
    myEncoder.displayFreqSpeed();
    break;

  case 3:
    myEncoder.displayIPMAC();
    break;

  case 4:
    myEncoder.displayDigitalLevel();
    break;

  case 5:
    myEncoder.displayTempHum();
    break;

  case 6:
    myEncoder.displaySleep();
    displayScreenNum = 8;
    break;

  case 7:
    myEncoder.displayWake();
    displayScreenNum = 0;
    break;

  default:
    DEBUG_SCREENLN(F("Call to updateScreen, but the screen is off"));
    delayMicroseconds(1);
    break;
  }
}
#endif
