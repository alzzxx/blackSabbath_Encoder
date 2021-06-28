
void setup()
{

  DEBUG_SERIALBEGIN(115200);

  // set pins
  DEBUG_BOOTLN(F("Starting pins"));
  delay(500);
  pinMode(TOGGLE_BUTTON, INPUT_PULLUP);
  pinMode(ST_RESET, OUTPUT);
  pinMode(SENSOR_PIN_STATUS, INPUT);
  pinMode(ST_PIN_STATUS, INPUT);
  pinMode(PLCEN_PIN_STATUS, INPUT);
  ST_RESET_HI;

// start screen functions
#ifdef SCREEN_ON
  DEBUG_BOOTLN(F("Starting screen now"));
  delay(500);
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

  delay(500);
#ifdef WEBSERVER_ON
  tasker.setInterval(spiSTM, 20, 0);              // SPI between ST and arduino *10
  tasker.setInterval(webServerArdST, 100, 1);     // handling of webServer functions *20
  tasker.setInterval(statusRead, 2000UL, 2);      // to check if spi coms between arduino and ST is OK
  tasker.setInterval(serverStatus, 3600000UL, 3); // to check if webServer is OK
#endif
  tasker.setInterval(stCheck, 3000UL, 2);
#ifdef SCREEN_ON
  tasker.setInterval(updateScreen, 100, 1); // update page to shown on oled screen *50
  tasker.setInterval(updateButton, 50, 1);  // update button reading
#endif
#ifdef SENSOR_BME280
  tasker.setInterval(tempUpdate, 5000UL, 3); // check if tempSensor is OK
#endif
  tasker.setInterval(checkSystems, 60000UL, 3); /// general check of all systems
#ifdef EXTMEMORY_ON
  tasker.setInterval(extEEPROMupdate, 3600000UL, 3); // check if extEEPROm is ok
#endif
#ifdef ACCELEROMETER_ON
  tasker.setInterval(imuUpdate, 3600000UL, 3); // check if IMU is ok
#endif
  attachInterrupt(digitalPinToInterrupt(PLCEN_PIN_STATUS), enableFlagEncoder, CHANGE);

// finish the setup
#ifdef SCREEN_ON
  display.clearDisplay();
  display.display();
  sP->mTimerCounter = millis();
#endif
  DEBUG_BOOTLN(F("Setup finished"));
}