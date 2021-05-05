
/*
Global variables for encoder program
*/

// globVar for webServer and UDP

#ifdef WEBSERVER_ON
String webGetString;      // Will be used for storing the HTTP requests from the client
byte plcEnable = 0x00;    // byte to indicate if the device is in SPI mode or encoder mode
byte deviceStatus = 0xFF; // byte to indicate encoder status, if everything is ok should be always dec 255 or 0xFF or 0B11111111
String deviceParamNames[NUMBER_OF_PARAMETERS] = {"encDist", "camRes", "patRes", "inFilter", "outFilter", "tSample",
                                                 "patCurr"}; // to be shown on debug and webServer

//globVar for SPI com with F031K6
int SPIerrorIndex = -1;  // do not delete this
bool saveParameters = 1; // TODO check with RS keep initial value = 1
int debug1 = 0;          // TODO check with RS
int cnt_debug = 0;
bool statusReadFlag = false;
#else
uint8_t ip[4] = {192, 168, 1, 25}; // fixed ip address to show on screen, only if webserver is not active
#endif

// globvar for screen
#ifdef SCREEN_ON
const uint16_t mDebTime = 300;       // debounce time for toggle screen button
bool fAllarmeSchermo = false;        // flag to inform that there is a problem with the oled screen
bool prevTogScr = false;             // to control screen change
bool onScreen = false;               // to control autoOFF wakeON of oled screen
uint8_t displayScreenNum = 0;        // current display
volatile bool toggleScreen = false;  // flag to change screen number
volatile uint32_t mTimerCounter = 0; // to hold elapsed time on debouncing function inside ISR
#endif

// globVar secondary systems
typedef struct flagSystems
{
    bool tFlag;      // flag for temperature sensor control
    bool eFlag;      // flag for ethernet control
    bool sysOK;      // flag for systems check
    bool extMemFlag; // flag for EEPROM check
    bool imuFlag;    // flag for imu check
    bool patFlag;    // flag for pixart sensor
    bool stFlag;     // flag for st mcu
};

// default values for flag variables
flagSystems flagEnc = {
    .tFlag = false,
    .eFlag = false,
    .sysOK = false,
    .extMemFlag = false,
    .imuFlag = false,
    .patFlag = false,
    .stFlag = false,
};

flagSystems *flagPoint = &flagEnc;

#ifndef EXTMEMORY_ON
flagPoint->extMemFlag = true;
#endif
#ifndef ACCELEROMETER_ON
flagPoint->imuFlag = true;
#endif
#if !defined(SENSOR_BME280) && !defined(SENSOR_AHT10)
flagPoint->tFlag = true;
#endif

// for tempSensor and encoder reading
typedef struct secSystems
{
    float tC;           // temperature value
    float hP;           // humidity value
    float bPre;         // pressure value
    double mPul;        // pulse read from encoder
    double encFreq;     // calculated pulse frequency
    byte diagBuffer[1]; // buffer to send to PLC
};

secSystems secVar = {
    secVar.tC = 0.00,
    secVar.hP = 0.00,
    secVar.bPre = 0.00,
    secVar.mPul = 0.00,
    secVar.encFreq = 0.00,
    secVar.diagBuffer[0] = 0,
};

secSystems *secPoint = &secVar;

// for encoder parameters
typedef struct struct_encoderSettings
{
    uint8_t deviceIndex; // Index of the device. This will affect its IP address and the port used for UDP transmission
    uint8_t mac[6];      // Mac address of device
    uint16_t localPort;  // local port to listen on
    uint16_t remotePort; // remote port to transmit on
    uint16_t deviceParameters[NUMBER_OF_PARAMETERS];
};

// struct holding all encoder parameters, with the default parameters
struct_encoderSettings encSettings = {
    encSettings.deviceIndex = 0,
    encSettings.mac[0] = 0xFD,
    encSettings.mac[1] = 0x1F,
    encSettings.mac[2] = 0x4D,
    encSettings.mac[3] = 0x1A,
    encSettings.mac[4] = 0xFC,
    encSettings.mac[5] = 0xDA,
    encSettings.localPort = 3000,
    encSettings.remotePort = 3000,
    encSettings.deviceParameters[0] = 25,
    encSettings.deviceParameters[1] = 42,
    encSettings.deviceParameters[2] = 2006,
    encSettings.deviceParameters[3] = 10,
    encSettings.deviceParameters[4] = 10,
    encSettings.deviceParameters[5] = 400,
    encSettings.deviceParameters[6] = 6,
};

struct_encoderSettings *encPoint = &encSettings; // pointer to struct to navigate the encoder parameters

// for all acc/gyro values
typedef struct struct_accgyroValues
{
    int16_t slopeX;
    int16_t slopeY;
    int16_t outputX;
    int16_t outputY;
    float angX;
    float angY;
    float angZ;
    float gyroX;
    float gyroY;
    float gyroZ;
};

// struct holding all imu values, with the default values
struct_accgyroValues imuValues = {
    imuValues.slopeX,
    imuValues.slopeY,
    imuValues.outputX,
    imuValues.outputY,
    imuValues.angX,
    imuValues.angY,
    imuValues.angZ,
    imuValues.gyroX,
    imuValues.gyroY,
    imuValues.gyroZ,
};

struct_accgyroValues *imuPoint = &imuValues; // pointer to navigate imuValues struct

#if !defined(ACCELEROMETER_ON)
imuPoint->angX = 0.00;
imuPoint->angY = 0.00;
#endif

#ifdef SCREEN_ON
static const char oledMessage_0[] PROGMEM = "BESTduino";
static const char oledMessage_1[] PROGMEM = "V 1.3.0";
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
static const char oledMessage_44[] PROGMEM = "";
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

// Objects and instances
Tasker tasker(true);                                      // object for tasking
QEI myPulse(PIN_SQWA, PIN_SQWB, PIN_ZERO, PULSE_PER_REV); // to read encPulses
Average<double> mediaPuls(MEAN_PUL_SAMPLES);              // to calculate mean pulse value

#ifdef SENSOR_BME280
Adafruit_BME280 bme; // object for temperature sensor
#endif

#ifdef WEBSERVER_ON
IPAddress ip(192, 168, 1, 20);      // Local IP address
IPAddress remote(192, 168, 1, 10);  // remote IP address
EthernetServer server(SERVER_PORT); // Server is configured in default port 80
#endif

#if defined(ARDUINO_NANO) && defined(SSD1306_I2C) && defined(SCREEN_ON)
Adafruit_SSD1306 display(SCREEN_WIDHT, SCREEN_HEIGHT, &Wire, ST_RESET, I2C_CLKFQY_DUR, I2C_CLKFQY_AFTER); // define OLED screen
#endif

BestEncoder myEncoder; // internal class for screen, extEEPROM, IMU, UDP

#ifdef UDP_ON
EthernetUDP Udp; // An EthernetUDP instance to let us send and receive packets over UDP
#endif

#ifdef EXTMEMORY_ON
ExternalEEPROM myEEPROM; // eeprom object that allow us to write and read from extEEPROM
#endif

#ifdef ACCELEROMETER_ON
Nano33BLEAccelerometerData accelerometerData;
Average<float> mediaAccX(MEAN_SAMPLE_NUMBER);
Average<float> mediaAccY(MEAN_SAMPLE_NUMBER);
Average<float> mediaAccZ(MEAN_SAMPLE_NUMBER);
#endif
