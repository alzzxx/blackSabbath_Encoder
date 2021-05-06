
// preprocessing define
#define ARDUINO_NANO
#define SSD1306_I2C
#define SENSOR_BME280
#define SHIELD_ON
#define SCREEN_ON
#define WEBSERVER_ON
#define EXTMEMORY_ON
#define ACCELEROMETER_ON
#define UDP_ON
//#define SD_ON
//#define ERASE_EEPROM

// Libraries
#define TASKER_MAX_TASKS 9
#include <Tasker.h>
#include <SPI.h>
#include <Wire.h>
#include <QEI.h>
#include <Average.h>
#ifdef SENSOR_BME280
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#endif
#if defined(SSD1306_I2C) && defined(SCREEN_ON)
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#endif
#ifdef WEBSERVER_ON
#include <EthernetCustom.h>
#endif
#ifdef SD_ON
#include <SD.h>
#endif
#ifdef EXTMEMORY_ON
#include <SparkFun_External_EEPROM.h>
#endif
#ifdef ACCELEROMETER_ON
#include <Nano33BLEAccelerometer.h>
#include <Arduino_LSM9DS1.h>
#endif

//  GPIO PINS macro
#if defined(ARDUINO_NANO) && defined(SSD1306_I2C)
#define PLCEN_PIN_STATUS 2  // enable bit from PLC
#define ST_PIN_STATUS 3     // bit allarme ST
#define PIN_SQWA P1_15      // PIN 4, for SQW_A
#define TOGGLE_BUTTON 5     // toggle screen button
#define PIN_SQWB P1_14      // PIN 6, for SQW_B
#define SENSOR_PIN_STATUS 7 // input pin from STM, means "PIXART OK"
#define SD_PIN_NSS 8        // slave select for sd card from ethernet shield
#define ST_PIN_NSS 9        // slave select for F031K6
#define ET_PIN_NSS 10       // slave select for ethernet shield
#define ST_RESET A0         // reset signal to F031K6
#define PIN_ZERO NC
#define OLED_ADDRESS 0x3D // oled screen I2C address
#endif

//  OLED resolution
#ifdef SCREEN_ON
#define SCREEN_WIDHT 128
#define SCREEN_HEIGHT 64
#endif

//  PIN operation macro
#define PLC_STATUS digitalRead(PLCEN_PIN_STATUS)
#define SENSOR_STATUS digitalRead(SENSOR_PIN_STATUS)
#define ST_STATUS digitalRead(ST_PIN_STATUS)
#define ST_NSS_LO digitalWrite(ST_PIN_NSS, LOW)
#define ST_NSS_HI digitalWrite(ST_PIN_NSS, HIGH)
#define SD_NSS_LO digitalWrite(SD_PIN_NSS, LOW)
#define SD_NSS_HI digitalWrite(SD_PIN_NSS, HIGH)
#define ET_NSS_LO digitalWrite(ET_PIN_NSS, LOW)
#define ET_NSS_HI digitalWrite(ET_PIN_NSS, HIGH)
#define ST_RESET_LO digitalWrite(ST_RESET, LOW)
#define ST_RESET_HI digitalWrite(ST_RESET, HIGH)

// Sensors operation macro
#if defined(SENSOR_BME280)
#define READ_TEMPERATURE bme.readTemperature()
#define READ_HUMIDITY bme.readHumidity()
#define READ_PRESSURE bme.readPressure() / 100.0F
#endif
#ifdef SHIELD_ON
#define ETHERNET_STATUS Ethernet.linkStatus()
#else
#define ETHERNET_STATUS true
#define IS_SERVER_ON true
#endif

//  Constants definition
#define MEAN_PUL_SAMPLES 20
#define ENCODING_TYPE 4.00
#define PULSE_PER_REV 32000UL
#ifdef SENSOR_BME280
#define BME280_ADDRESS 0x76 // i2c address of BME280
#endif
#define SERVER_PORT 80
#define NUMBER_OF_PARAMETERS 7 // number of parameters exchanged with ST
#define SHORTDELAY 20          // short delay for spi communication
#define SHORTDELAY_I2C 5       // short delay for i2c communication
#define ERROR_SPI_LIMIT 150    // max amount of SPI erros allowed
#define ERROR_I2C_LIMIT 50     // max amount of i2c communication errors allowed
#define DELAY_SCREEN 1500      // delay between change of different splash screens
#define SPI_STATUS_ADDRESS 11
#define SPI_ERROR 223           //  B11011111
#define I2C_CLKFQY_DUR 400000UL // i2c clock frequency during ssd1306 function calls
#ifdef EXTMEMORY_ON
#define EEPROM_ADDRESS 0x50       // extEEPROM address
#define EEPROM_MEM_SIZE 128000UL  // mem size of EEPROM
#define EEPROM_PAGE_SIZE 128      // EEPROM page write buffer
#define EEPROM_PAG_WRITETIME 3    // EEPROM page write time
#define I2C_CLKFQY_AFTER 400000UL // i2c clock frequency after function calls when extEEPROM is present
#define LOCATION_SETTINGS 0       // starting eeprom address to read or write
#define LOCATION_DEV_INDX 0       // memory location for devIndex
#define LOCATION_MAC_ZERO 1       // memory location for MAC address
#define LOCATION_MAC_ONE 2
#define LOCATION_MAC_TWO 3
#define LOCATION_MAC_THREE 4
#define LOCATION_MAC_FOUR 5
#define LOCATION_MAC_FIVE 6
#define LOCATION_LOCAL_PORT 8 // memory location for localPort
#define LOCATION_DEV_PARAM 10 // memory location por deviceParameters
#else
#define I2C_CLKFQY_AFTER 100000UL // i2c clock frequency after ssd1306 function calls when extEEPROM is not present
#endif
#ifdef ACCELEROMETER_ON
#define INPUT_START_X -1.0
#define INPUT_END_X 1.0
#define OUTPUT_START_X 128.0
#define OUTPUT_END_X 64.0
#define INPUT_START_Y -1.0
#define INPUT_END_Y 1.0
#define OUTPUT_START_Y 55.0
#define OUTPUT_END_Y 17.0
#define MEAN_SAMPLE_NUMBER 40
#endif
