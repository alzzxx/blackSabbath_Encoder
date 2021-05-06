
void setup()
{

  DEBUG_SERIALBEGIN(115200);

  // set pins
  DEBUG_BOOTLN(F("Starting pins"));
  delay(500);
  pinMode(TOGGLE_BUTTON, INPUT_PULLUP);
  pinMode(ST_RESET, OUTPUT);
  pinMode(SENSOR_PIN_STATUS, INPUT_PULLUP);
  ST_RESET_HI;

  // start screen functions
#ifdef SCREEN_ON
  DEBUG_BOOTLN(F("Starting screen now"));
  delay(500);
  myEncoder.startScreen();                   // start oled screen
  myEncoder.splashScreen();                  // show initial message
  myEncoder.initialCheck();                  // check all systems
  bool tempEEPROM = myEncoder.initParam();   // read parameters from eeprom
  bool tempSens = myEncoder.sensorStart();   // start secondary sensors
  bool tempShield = myEncoder.shieldStart(); // start ethernet shield
  flagPoint->sysOK = tempSens && tempShield && tempEEPROM;
#else
  bootShield();                    // start ethernet shield if screen is off
  int16_t parStatus = readParam(); // read parameters if screen is off
  if (parStatus != 0)
    DEBUG_BOOTLN(F("EEPROM not started, check wiring"));
  else
    DEBUG_BOOTLN(F("Parameters read OK!"));
  DEBUG_BOOTLN(F("Starting IMU"));
#ifdef ACCELEROMETER_ON
  bool tempIMU = myEncoder.startIMU(); // start IMU when the screen is off
#endif
#if defined(SENSOR_BME280)
  myEncoder.bmeStart();
#endif
#endif

  // set interrupt function for toggle button
#ifdef SCREEN_ON
  myEncoder.finishSetup();
  myEncoder.buttonSetup();
#endif

  // set intervals for repeating functions
  DEBUG_BOOTLN(F("Setting tasker intervals"));
  delay(500);
#ifdef WEBSERVER_ON
  tasker.setInterval(spiSTM, 10, 0);              // SPI between ST and arduino
  tasker.setInterval(webServerArdST, 20, 1);      // handling of webServer functions
  tasker.setInterval(statusRead, 2000UL, 2);      // to check if spi coms between arduino and ST is OK
  tasker.setInterval(serverStatus, 3600000UL, 3); // to check if webServer is OK
#endif
#ifdef SCREEN_ON
  tasker.setInterval(updateScreen, 50, 1); // update page to shown on oled screen
  tasker.setInterval(updateButton, 50, 1); // update button reading
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

  // finish the setup
#ifdef SCREEN_ON
  display.clearDisplay();
  display.display();
  mTimerCounter = millis();
#endif
  DEBUG_BOOTLN(F("Setup finished"));
}