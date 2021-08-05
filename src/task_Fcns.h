
/*
 * Tasks functions: those are the only functions that get called inside the main loop, all the other functions
 * are called within task functions. The intervals are fixed for each functions, with the more important ones 
 * called at a higher frequency. In the constanst_File each interval can be modified, on the setup the priority
 * of the function can also be modified, with 0 being the highest and 3 the lowest.
*/

void stCheck(void)
{
  /*
   Function to control st and pixart status, if the encoder if in error mode
   start UDP and send packet with deviceStatus byte to plc for diagnose

  */
  PIN_UP;
  DEBUG_TASKSLN(F("Checking pixart and ST"));
  if (SENSOR_STATUS == HIGH)
  {
    fP->patFlag = true; // flag to control pat9130 sensor
    DEBUG_TASKS(F("Pixart error"));
  }
  else
  {
    fP->patFlag = false;
    DEBUG_TASKSLN(F("Pixart OK"));
  }
  if (ST_STATUS == LOW)
  {
    fP->stFlag = true; // flag to control st board
    DEBUG_TASKSLN(F("ST error"));
    sP->diagBuffer[0] = deviceStatus;
#ifdef UDP_ON
    DEBUG_TASKSLN(F("Calling to writeUDP"));
    delay(10);
    mySystem.writeUDP(sP->diagBuffer, sizeof(sP->diagBuffer), remote, eP->remotePort); // call upd function, and send to plc diagnostic byte
#endif
    DEBUG_TASKS(F("deviceStatus is: "));
    DEBUG_TASKSLN(sP->diagBuffer[0]);
  }
  else
  {
    fP->stFlag = false;
    DEBUG_TASKSLN(F("ST ok"));
  }
  PIN_DOWN;
}

void checkSystems(void)
{
  /*
   Function to check secondary systems, check all flags
   and set o clear sysOK flag
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
    Function that updates button reading,  it's called at fixed
    intervals to check wether the button has been pressed or not
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
  - Function that shows the webserver
  */

  PIN_UP;
  fP->saveParameters = myServer.displayWebServer() || fP->saveParameters;
  PIN_DOWN;
}

void serverStatus(void)
{
  /*
  - Function to check is server if alive, if it not try to restart it
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
   Function that handles spi communication between arduino and ST
  */

  PIN_UP;

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
    if (!(ENCODER_ENABLE))
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

  if (ENCODER_ENABLE)
  {
    ENABLE_ENCODER_HI;
  }
  else if (ENCODER_DISABLE)
  {
    DISABLE_ENCODER_LO;
  }

  PIN_DOWN;
}
#endif

#ifdef SCREEN_ON
void updateScreen(void)
{
  /*
   Function that handle oled Display, it changes between the 
   differents pages according to user decision
  */

  PIN_UP;
  myScreen.updateScreenNum(); // update page to be shown

  // switch case to decide wich page is shown on the display
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
