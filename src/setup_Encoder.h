

void setup()
{

  /* #region  PIN_SETUP */
  DEBUG_BOOTLN(F("Starting pins"));
  DEBUG_SERIALBEGIN(debugbaudRate);
  pinMode(ST_RESET, OUTPUT);
  ST_RESET_HI;
  pinMode(PLCEN_PIN_STATUS, INPUT);
  pinMode(ST_PIN_STATUS, INPUT);
  pinMode(TOGGLE_BUTTON, INPUT_PULLUP);
  pinMode(SENSOR_PIN_STATUS, INPUT);
  pinMode(ST_PIN_STATUS, INPUT);
  pinMode(SD_PIN_NSS, OUTPUT);
  pinMode(ST_PIN_NSS, OUTPUT);
  pinMode(ET_PIN_NSS, OUTPUT);
  pinMode(EN_ENCODER_ARD_TO_ST, OUTPUT);
  DISABLE_ENCODER_LO;
/* #endregion */

// start screen functions
#ifdef SCREEN_ON
  DEBUG_BOOTLN(F("Starting screen now"));
  myScreen.startScreen();                   // start oled screen
  myScreen.splashScreen();                  // show initial message
  myScreen.initialCheck();                  // check all systems
  bool tempEEPROM = myScreen.initParam();   // read parameters from eeprom
  bool tempShield = myScreen.shieldStart(); // start ethernet shield
  bool tempSens = myScreen.sensorStart();   // start secondary sensors
  fP->sysOK = tempSens && tempShield && tempEEPROM;
#else
  mySystem.bootShield();                    // start ethernet shield if screen is off
  int16_t parStatus = mySystem.readParam(); // read parameters if screen is off
  if (parStatus != 0)
    DEBUG_BOOTLN(F("EEPROM not started, check wiring"));
  else
    DEBUG_BOOTLN(F("Parameters read OK!"));
  DEBUG_BOOTLN(F("Starting IMU"));
#ifdef ACCELEROMETER_ON
  bool tempIMU = mySensor.startIMU(); // start IMU when the screen is off
#endif
#if defined(SENSOR_BME280)
  mySensor.bmeStart();
#endif
#endif

// set interrupt function for toggle button
#ifdef SCREEN_ON
  myScreen.finishSetup();
  myScreen.buttonSetup();
#endif

// activate debug function measuring
#ifdef DEBUG_FCN_TIME
  pinConfig(DEBUG_PIN);
#endif

  // set intervals for repeating functions
  DEBUG_BOOTLN(F("Setting tasker intervals"));

#ifdef WEBSERVER_ON
  tasker.setInterval(spiSTM, tSPIardST, highPriority);              // SPI between ST and arduino *10
  tasker.setInterval(webServerArdST, tSERVERardST, mediumPriority); // handling of webServer functions *20
  tasker.setInterval(statusRead, tStatusSPI, lowPriority);          // to check if spi coms between arduino and ST is OK
  tasker.setInterval(serverStatus, tServerStatus, lowestPriority);  // to check if webServer is OK
#endif
  tasker.setInterval(stCheck, tSTcheck, lowPriority);
#ifdef SCREEN_ON
  tasker.setInterval(updateScreen, tScreenUpdate, mediumPriority); // update page to shown on oled screen *50
  tasker.setInterval(updateButton, tButtonUpdate, mediumPriority); // update button reading
#endif
#ifdef SENSOR_BME280
  tasker.setInterval(tempUpdate, tBMEupdate, lowestPriority); // check if tempSensor is OK
#endif
  tasker.setInterval(checkSystems, tSystemCheck, lowestPriority); /// general check of all systems
#ifdef EXTMEMORY_ON
  tasker.setInterval(extEEPROMupdate, tUpdateMemory, lowestPriority); // check if extEEPROm is ok
#endif
#ifdef ACCELEROMETER_ON
  tasker.setInterval(imuUpdate, tUpdateACC, lowestPriority); // check if IMU is ok
#endif

// finish the setup
#ifdef SCREEN_ON
  display.clearDisplay();
  display.display();
  sP->mTimerCounter = millis();
#endif
  DEBUG_BOOTLN(F("Setup finished"));
}