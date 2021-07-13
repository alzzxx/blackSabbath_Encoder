#line 1 "c:\\Users\\a.rondon\\Documents\\GitHub\\BlackSabbath\\src\\constants_File.h"

/*
* Constants definition
*/

const uint8_t meanPulSamples = 20;  // samples ammount for frequency average calculation
const uint16_t pulsePerRev = 32000; // encoder pulse per revolution
const double encodingType = 4.00;
#ifdef SENSOR_BME280
const uint8_t bmeAddress = 0x76; // i2c address of BME280
#endif
const uint8_t serverPort = 80;      // port for UDP communication
const uint8_t numberParameters = 8; // number of parameters exchanged with ST
const uint8_t shortDelay = 20;      // short delay for spi communication [us]
const uint8_t delayI2C = 5;         // short delay for i2c communication
const uint8_t spiErrorLimit = 150;  // max amount of SPI erros allowed
const uint8_t i2cErrorLimit = 50;   // max amount of i2c communication errors allowed
const uint8_t spiStatusAddress = 11;
const uint8_t spiError = 223;      //  B11011111
const uint16_t delayScreen = 1500; // delay between change of different splash screens
const uint32_t i2cDurClk = 400000; // i2c clock frequency during ssd1306 function calls
#ifdef EXTMEMORY_ON
const uint8_t eepromAddress = 0x50;   // extEEPROM address
const uint8_t eepromStartAddress = 0; // starting eeprom address to read or write
const uint8_t locationDevIndex = 0;   // memory location for devIndex
const uint8_t locationMacZero = 1;    // memory location for MAC address
const uint8_t locationMacOne = 2;
const uint8_t locationMacTwo = 3;
const uint8_t locationMacThree = 4;
const uint8_t locationMacFour = 5;
const uint8_t locationMacFive = 6;
const uint8_t locationLocalPort = 8;   // memory location for localPort
const uint8_t locationDevParam = 10;   // memory location por deviceParameters
const uint8_t eepromPageSize = 120;    // EEPROM page write buffer
const uint8_t eepromPageWriteTime = 3; // EEPROM page write time
const uint32_t eepromMemSize = 128000; // mem size of EEPROM
const uint32_t i2cAftClk = 400000;     // i2c clock frequency after function calls when extEEPROM is present
#else
const uint32_t i2cAftClk = 100000; // i2c clock frequency after ssd1306 function calls when extEEPROM is not present
#endif
#ifdef SCREEN_ON
const uint8_t oledAddress = 0x3D; // oled screen I2C address
const uint8_t screenW = 128;
const uint8_t screenH = 64;
const uint16_t mDebTime = 300;      // debounce time for toggle screen button
const uint16_t encResetTime = 5000; // time to reset encoder
#endif
#ifdef ACCELEROMETER_ON
const uint8_t meanSampleNumber = 40; // number of sample read from imu sensor before averaging
const float inputStartX = -1.00;     // To map values from imu sensor to oled display (same for const below)
const float inputEndX = 1.00;
const float outputStartX = 122.00;
const float outputEndX = 69;
const float inputStartY = -1.00;
const float inputEndY = 1.00;
const float outputStartY = 50.00;
const float outputEndY = 22.00;
#endif

// const for messages and icons shown on oled display
#ifdef SCREEN_ON
static const char oledMessage_0[] PROGMEM = "BESTduino";
static const char oledMessage_1[] PROGMEM = "V 1.0.0";
static const char oledMessage_2[] PROGMEM = "Shield not present";
static const char oledMessage_3[] PROGMEM = "Checking encoder";
static const char oledMessage_4[] PROGMEM = "Encoder error";
static const char oledMessage_5[] PROGMEM = "Encoder started";
static const char oledMessage_6[] PROGMEM = "Booting systems";
static const char oledMessage_7[] PROGMEM = "Encoder status";
static const char oledMessage_8[] PROGMEM = "Temperature/Humidity";
static const char oledMessage_9[] PROGMEM = "Digital level";
static const char oledMessage_10[] PROGMEM = "IP/MAC address";
static const char oledMessage_11[] PROGMEM = "Sensor values";
static const char oledMessage_12[] PROGMEM = "Main sensor:";
static const char oledMessage_13[] PROGMEM = "Main system:";
static const char oledMessage_14[] PROGMEM = "PLC enable:";
static const char oledMessage_15[] PROGMEM = "OK";
static const char oledMessage_16[] PROGMEM = "ERROR";
static const char oledMessage_17[] PROGMEM = "ON";
static const char oledMessage_18[] PROGMEM = "OFF";
static const char oledMessage_19[] PROGMEM = "Starting sensors";
static const char oledMessage_20[] PROGMEM = "Sensors OK!";
static const char oledMessage_21[] PROGMEM = "Check sensors";
static const char oledMessage_22[] PROGMEM = "Tsensor error";
static const char oledMessage_23[] PROGMEM = "ID dev: ";
static const char oledMessage_24[] PROGMEM = "IP add: ";
static const char oledMessage_25[] PROGMEM = "MAC address:";
static const char oledMessage_26[] PROGMEM = "Ethernet error";
static const char oledMessage_27[] PROGMEM = "Starting ethernet";
static const char oledMessage_28[] PROGMEM = "WebServer ready";
static const char oledMessage_29[] PROGMEM = "Check shield wires";
static const char oledMessage_30[] PROGMEM = "encDis:";
static const char oledMessage_31[] PROGMEM = "encRes:";
static const char oledMessage_32[] PROGMEM = "patRes:";
static const char oledMessage_33[] PROGMEM = "inFil:";
static const char oledMessage_34[] PROGMEM = "outFil:";
static const char oledMessage_35[] PROGMEM = "tSamp:";
static const char oledMessage_36[] PROGMEM = "patCur:";
static const char oledMessage_37[] PROGMEM = "Reading parameters";
static const char oledMessage_38[] PROGMEM = "EEPROM not present";
static const char oledMessage_39[] PROGMEM = "Parameters loaded";
static const char oledMessage_40[] PROGMEM = "Check EEPROM";
static const char oledMessage_41[] PROGMEM = "IMU error";
static const char oledMessage_42[] PROGMEM = "IMU disabled";
static const char oledMessage_43[] PROGMEM = "Encoder frequency";
static const char oledMessage_44[] PROGMEM = "Finishing setup";
static const char oledMessage_45[] PROGMEM = "Encoder disabled";
static const char oledMessage_46[] PROGMEM = "";
static const char oledMessage_47[] PROGMEM = "";

static const char *const oledMessage_table[] PROGMEM = {
    oledMessage_0, oledMessage_1, oledMessage_2, oledMessage_3,
    oledMessage_4, oledMessage_5, oledMessage_6, oledMessage_7,
    oledMessage_8, oledMessage_9, oledMessage_10, oledMessage_11,
    oledMessage_12, oledMessage_13, oledMessage_14, oledMessage_15,
    oledMessage_16, oledMessage_17, oledMessage_18, oledMessage_19,
    oledMessage_20, oledMessage_21, oledMessage_22, oledMessage_23,
    oledMessage_24, oledMessage_25, oledMessage_26, oledMessage_27,
    oledMessage_28, oledMessage_29, oledMessage_30, oledMessage_31,
    oledMessage_32, oledMessage_33, oledMessage_34, oledMessage_35,
    oledMessage_36, oledMessage_37, oledMessage_38, oledMessage_39,
    oledMessage_40, oledMessage_41, oledMessage_42, oledMessage_43,
    oledMessage_44, oledMessage_45, oledMessage_46, oledMessage_47};

static const unsigned char oledIcon_0[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x07, 0x80, 0x03, 0xef, 0x00, 0x0c, 0x1e, 0x00, 0x10,
    0x3c, 0x00, 0x20, 0x7a, 0x00, 0x4c, 0x72, 0x00, 0x5e, 0xf1, 0x00, 0x5f, 0xe1, 0x00, 0x4f, 0xe1,
    0x00, 0x47, 0xc1, 0x00, 0x23, 0xc2, 0x00, 0x11, 0x84, 0x00, 0x0c, 0x18, 0x00, 0x03, 0xe0, 0x00,
    0x00, 0x00, 0x00}; // check sign

static const unsigned char oledIcon_1[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0xe0, 0x00, 0x01, 0x20, 0x00, 0x03,
    0x30, 0x00, 0x02, 0x10, 0x00, 0x06, 0xd8, 0x00, 0x06, 0xd8, 0x00, 0x0c, 0xcc, 0x00, 0x0c, 0xcc,
    0x00, 0x18, 0xc6, 0x00, 0x18, 0x06, 0x00, 0x30, 0xc3, 0x00, 0x30, 0xc3, 0x00, 0x60, 0x01, 0x80,
    0x7f, 0xff, 0x80, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00}; // Warning sign

static const unsigned char oledIcon_2[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x3f, 0x81, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7f, 0xe3, 0xff, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xff, 0xf3, 0xff, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0xf8, 0xff, 0xfb, 0xff, 0x7f, 0xcf, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1f, 0xfe, 0xff, 0xf9, 0xfe, 0x3f, 0xdf, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3f, 0xff, 0x7f, 0xf0, 0x7c, 0x1f, 0x9f, 0xf7, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x3f, 0xff, 0x1f, 0xe0, 0x00, 0x00, 0x0f, 0xef, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7f, 0xcf, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xff, 0xf3, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xe0, 0x00, 0x00, 0x00, 0x00,
    0x03, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1f, 0xf0, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
    0x1f, 0xe0, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x7f, 0xfc, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x40, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xfe, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x80, 0x00, 0x03, 0xfc, 0xfd, 0xfd, 0x83, 0x3f, 0x7f, 0xfb, 0x03, 0xf9, 0xf8, 0xfe,
    0x7f, 0xff, 0x80, 0x00, 0x03, 0xfe, 0xfb, 0xfd, 0x83, 0x7f, 0xff, 0xfb, 0x07, 0xf3, 0xfc, 0xff,
    0x3f, 0xff, 0x00, 0x00, 0x03, 0x06, 0xc3, 0x0e, 0xc6, 0xe1, 0xb8, 0xc3, 0x06, 0x07, 0x0c, 0x03,
    0x0f, 0xfe, 0x00, 0x00, 0x03, 0x06, 0xc3, 0x0e, 0xc6, 0xc1, 0xb8, 0xc3, 0x0e, 0x06, 0x0c, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0xc7, 0xfe, 0xc6, 0xff, 0xb8, 0xc3, 0x0e, 0x07, 0xfc, 0xff,
    0x0f, 0xf0, 0x00, 0x00, 0x03, 0x06, 0xc7, 0xfe, 0xec, 0xff, 0xb8, 0xc3, 0x0e, 0x07, 0xfd, 0xdf,
    0x1f, 0xfe, 0x00, 0x00, 0x03, 0x06, 0xc7, 0x00, 0x6c, 0xc0, 0x38, 0xc3, 0x0e, 0x06, 0x01, 0x83,
    0x3f, 0xff, 0x00, 0x00, 0x03, 0x06, 0xc3, 0x00, 0x6c, 0xc0, 0x38, 0xc3, 0x06, 0x06, 0x01, 0x83,
    0x3f, 0xff, 0x80, 0x00, 0x03, 0x8e, 0xc3, 0x04, 0x78, 0x60, 0xb8, 0xc3, 0x06, 0x07, 0x05, 0x87,
    0x1f, 0xff, 0x80, 0x00, 0x03, 0xfc, 0xc3, 0xfc, 0x38, 0x7f, 0x9f, 0xff, 0x07, 0xfb, 0xfc, 0xff,
    0x0f, 0xff, 0x80, 0x00, 0x03, 0x78, 0xc1, 0xfc, 0x38, 0x3f, 0x1f, 0x7b, 0x03, 0xf1, 0xf8, 0xfb,
    0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3f, 0xf8, 0x00, 0x02, 0x49, 0x8e, 0x73, 0xb9, 0x1c, 0xa0, 0x68, 0x47, 0x28, 0x94, 0x63,
    0x00, 0x3f, 0xfc, 0x00, 0x02, 0x69, 0x0a, 0x42, 0x11, 0x34, 0xe0, 0x68, 0xc4, 0x28, 0x9c, 0x44,
    0x00, 0x1f, 0xfc, 0x00, 0x02, 0x79, 0xce, 0x62, 0x11, 0x24, 0xe0, 0x7c, 0xe4, 0x38, 0x9c, 0x63,
    0x00, 0x0f, 0xf8, 0x00, 0x02, 0x58, 0x4c, 0x42, 0x11, 0x34, 0xa0, 0x74, 0xe4, 0x28, 0x94, 0x45,
    0x00, 0x00, 0x0f, 0xe0, 0x02, 0x09, 0x88, 0x73, 0x91, 0x18, 0xa0, 0x54, 0x23, 0x28, 0x14, 0x67,
    0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0xfb, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xef, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xe7, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0xf7, 0xef, 0x9c, 0xef, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xef, 0xfe, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x9c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Brevetti logo

static const unsigned char oledIcon_3[] PROGMEM = {
    0b00000001, 0b11000000, //        ###
    0b00000011, 0b11100000, //       #####
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00001111, 0b11110000, //     ########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000111, 0b11100000, //      ######
};                          // temperature icon

static const unsigned char oledIcon_4[] PROGMEM = {
    0b00000000, 0b00000000, //
    0b00000001, 0b10000000, //        ##
    0b00000011, 0b11000000, //       ####
    0b00000111, 0b11100000, //      ######
    0b00001111, 0b11110000, //     ########
    0b00001111, 0b11110000, //     ########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11011000, //    ####### ##
    0b00111111, 0b10011100, //   #######  ###
    0b00111111, 0b10011100, //   #######  ###
    0b00111111, 0b00011100, //   ######   ###
    0b00011110, 0b00111000, //    ####   ###
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000011, 0b11000000, //       ####
    0b00000000, 0b00000000, //
};                          // humidity icon

static const unsigned char oledIcon_5[] PROGMEM = {

    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0xe0, 0x00, 0x01, 0x50, 0x00, 0x00, 0x40, 0x00, 0x00,
    0x40, 0x00, 0x03, 0xf0, 0x00, 0x12, 0x10, 0x00, 0x22, 0xd0, 0x00, 0x7e, 0xd0, 0x00, 0x22, 0x10,
    0x00, 0x13, 0xf0, 0x00, 0x00, 0x08, 0x00, 0x00, 0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x07, 0x00,
    0x00, 0x00, 0x00}; // gyroscope icon

static const unsigned char oledIcon_6[] PROGMEM = {

    0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x03, 0x01, 0x80, 0x04, 0x00, 0x40, 0x08, 0x00, 0x20, 0x10,
    0x00, 0x10, 0x23, 0xcf, 0x08, 0x22, 0x49, 0x08, 0x42, 0x49, 0x04, 0x5e, 0x79, 0xe4, 0x40, 0x00,
    0x04, 0x4f, 0x3c, 0xf4, 0x41, 0x24, 0x84, 0x21, 0x24, 0x88, 0x21, 0xe7, 0x88, 0x10, 0x00, 0x10,
    0x08, 0x00, 0x20, 0x04, 0x00, 0x40, 0x03, 0x83, 0x80, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00}; // 'myEncoder, 23x21px

#endif