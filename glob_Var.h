
/*
* Global variables 
*/

// globVar for webServer
#ifdef WEBSERVER_ON
String webGetString; // Will be used for storing the HTTP requests from the client
String deviceParamNames[numberParameters] = {"encDist", "camRes", "patRes", "inFilter", "outFilter", "tSample",
                                             "patCurr", "encSim"}; // to be shown on debug and webServer
#else
uint8_t ip[4] = {192, 168, 1, 25}; // fixed ip address to show on screen, only if webserver is not active
#endif
int SPIerrorIndex = -1;   // do not delete this
byte plcEnable = 0x00;    // byte to indicate if the device is in SPI mode or encoder mode
byte deviceStatus = 0xFF; // byte to indicate encoder status, if everything is ok should be always dec 255 or 0xFF or 0B11111111

// globVar secondary systems
typedef struct flagSystems
{
    bool tFlag;                 // flag for temperature sensor control
    bool eFlag;                 // flag for ethernet control
    bool sysOK;                 // flag for systems check
    bool extMemFlag;            // flag for EEPROM check
    bool imuFlag;               // flag for imu check
    bool patFlag;               // flag for pixart sensor
    bool stFlag;                // flag for st mcu
    bool onScreen;              // to control autoOFF wakeON of oled screen
    volatile bool toggleScreen; // flag to change screen
    bool prevTogScr;            // to control screen change
    bool saveParameters;        // keep initial value = 1
    bool statusReadFlag;
    bool enableServer; // enable encoder from webServer
    bool enablePLC;    // enable from PLC
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
    .onScreen = false,
    .toggleScreen = false,
    .prevTogScr = false,
    .saveParameters = true,
    .statusReadFlag = false,
    .enableServer = false,
    .enablePLC = false,
};

flagSystems *fP = &flagEnc;

#ifndef EXTMEMORY_ON
fP->extMemFlag = true;
#endif
#ifndef ACCELEROMETER_ON
fP->imuFlag = true;
#endif
#if !defined(SENSOR_BME280)
fP->tFlag = true;
#endif

// for tempSensor and encoder reading
typedef struct secSystems
{
    float tC;                 // temperature value
    float hP;                 // humidity value
    float bPre;               // pressure value
    double mPul;              // pulse read from encoder
    double encFreq;           // calculated pulse frequency
    byte diagBuffer[1];       // buffer to send to PLC
    uint8_t displayScreenNum; // current display
    uint16_t debug1;
    uint16_t cntDebug;
    uint32_t mTimerCounter; // to hold on screen time
};

secSystems secVar = {
    secVar.tC = 0.00,
    secVar.hP = 0.00,
    secVar.bPre = 0.00,
    secVar.mPul = 0.00,
    secVar.encFreq = 0.00,
    secVar.diagBuffer[0] = 0,
    secVar.displayScreenNum = 0,
    secVar.mTimerCounter = 0,
    secVar.debug1 = 0,
    secVar.cntDebug = 0,
};

secSystems *sP = &secVar; // pointer to struct to navigate the secVar variables
// for encoder parameters
typedef struct struct_encoderSettings
{
    uint8_t deviceIndex; // Index of the device. This will affect its IP address and the port used for UDP transmission
    uint8_t mac[6];      // Mac address of device
    uint16_t localPort;  // local port to listen on
    uint16_t deviceParameters[numberParameters];
    uint16_t remotePort; // remote port to transmit on
};

// default encoder parameters
struct_encoderSettings encSettings = {
    encSettings.deviceIndex = 0,
    encSettings.mac[0] = 0xFD,
    encSettings.mac[1] = 0x1F,
    encSettings.mac[2] = 0x4D,
    encSettings.mac[3] = 0x1A,
    encSettings.mac[4] = 0xFC,
    encSettings.mac[5] = 0xDA,
    encSettings.localPort = 3000,
    encSettings.deviceParameters[0] = 25,
    encSettings.deviceParameters[1] = 42,
    encSettings.deviceParameters[2] = 2006,
    encSettings.deviceParameters[3] = 10,
    encSettings.deviceParameters[4] = 10,
    encSettings.deviceParameters[5] = 400,
    encSettings.deviceParameters[6] = 6,
    encSettings.deviceParameters[7] = 0,
    encSettings.remotePort = 3000,
};

struct_encoderSettings *eP = &encSettings; // pointer to struct to navigate the encoder parameters

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

struct_accgyroValues *iP = &imuValues; // pointer to navigate imuValues struct

#if !defined(ACCELEROMETER_ON)
iP->angX = 0.00;
iP->angY = 0.00;
#endif

// Objects and instances
ScreenEncoder myScreen; // Object for screen functions
#ifdef WEBSERVER_ON
ServerEncoder myServer; // Object for server functions
#endif
SensorEncoder mySensor;                                 // Object for sensor functions
SystemEncoder mySystem;                                 // Object for comunication functions
Tasker tasker(true);                                    // object for tasking
QEI myPulse(PIN_SQWA, PIN_SQWB, PIN_ZERO, pulsePerRev); // to read encPulses
Average<double> mediaPuls(meanPulSamples);              // to calculate mean pulse value
EasyButton button(TOGGLE_BUTTON);                       // to toggle screen and reset encoder

#ifdef SENSOR_BME280
Adafruit_BME280 bme; // object for temperature sensor
#endif

#if defined(WEBSERVER_ON) || defined(UDP_ON)
IPAddress ip(192, 168, 1, 20);     // Local IP address
IPAddress remote(192, 168, 1, 10); // remote IP address
EthernetServer server(serverPort); // Server is configured in default port 80
#endif

#if defined(ARDUINO_NANO) && defined(SCREEN_ON)
Adafruit_SSD1306 display(screenW, screenH, &Wire, ST_RESET, i2cDurClk, i2cAftClk); // define OLED screen
#endif

#ifdef UDP_ON
EthernetUDP Udp; // An EthernetUDP instance to let us send and receive packets over UDP
#endif

#ifdef EXTMEMORY_ON
ExternalEEPROM myEEPROM; // eeprom object that allow us to write and read from extEEPROM
#endif

#ifdef ACCELEROMETER_ON
Nano33BLEAccelerometerData accelerometerData; // to read imu sensor
Average<float> mediaAccX(meanSampleNumber);   // for average calculation (same below)
Average<float> mediaAccY(meanSampleNumber);
Average<float> mediaAccZ(meanSampleNumber);
#endif
