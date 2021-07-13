#line 1 "c:\\Users\\a.rondon\\Documents\\GitHub\\BlackSabbath\\src\\general_Header.h"

/*
* General header file
*/

// preprocessing define
#define ARDUINO_NANO
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
#define TASKER_MAX_TASKS 12
#include <Tasker.h>
#include <SPI.h>
#include <Wire.h>
#include <QEI.h>
#include <Average.h>
#include <EasyButton.h>
#ifdef SENSOR_BME280
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#endif
#ifdef SCREEN_ON
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#endif
#if defined(WEBSERVER_ON) || defined(UDP_ON)
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
#if defined(ARDUINO_NANO)
#define PLCEN_PIN_STATUS 2      // enable bit from PLC
#define ST_PIN_STATUS 3         // bit allarme ST
#define PIN_SQWA P1_15          // PIN 4, for SQW_A
#define TOGGLE_BUTTON 5         // toggle screen button
#define PIN_SQWB P1_14          // PIN 6, for SQW_B
#define SENSOR_PIN_STATUS 7     // input pin from STM, means "PIXART OK"
#define SD_PIN_NSS 8            // slave select for sd card from ethernet shield
#define ST_PIN_NSS 9            // slave select for F031K6
#define ET_PIN_NSS 10           // slave select for ethernet shield
#define ST_RESET A0             // reset signal to F031K6
#define EN_ENCODER_ARD_TO_ST A1 // enable signal from arduino to plc
#define PIN_ZERO NC
#endif

//  PIN operations macro
#define PLC_STATUS digitalRead(PLCEN_PIN_STATUS)
#define ENCODER_ENABLE fP->enablePLC || fP->enableServer
#define ENCODER_DISABLE !fP->enablePLC && !fP->enableServer
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
#define ENABLE_ENCODER_HI digitalWrite(EN_ENCODER_ARD_TO_ST, HIGH)
#define DISABLE_ENCODER_LO digitalWrite(EN_ENCODER_ARD_TO_ST, LOW)

// Sensors operations macro
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
