
/*
* Global variables 
*/

#ifdef WEBSERVER_ON
String webGetString; // To store the HTTP requests from the client
String deviceParamNames[numberParameters] = {"encDist", "camRes", "patRes", "inFilter", "outFilter", "tSample",
                                             "patCurr", "encSim"}; // to be shown on debug and webServer
String arduinoParamNames[ardParameters] = {"rotDeg"};              // arduino internal parameters
#else
uint8_t ip[4] = {192, 168, 1, 25}; // fixed ip address to show on screen, only if webserver is not active
#endif
int SPIerrorIndex = -1;   // do not delete this
byte plcEnable = 0x00;    // to indicate if the device is in SPI mode or encoder mode
byte deviceStatus = 0xFF; // to indicate encoder status, if everything is ok should be always dec 255 or 0xFF or 0B11111111

typedef struct flagSystems
{
    bool tFlag;                 // for temperature sensor control
    bool eFlag;                 // for ethernet control
    bool sysOK;                 // for systems check
    bool extMemFlag;            // for EEPROM check
    bool imuFlag;               // for imu check
    bool patFlag;               // for pixart sensor
    bool stFlag;                // for st mcu check
    bool onScreen;              // to control autoOFF wakeON of oled screen
    volatile bool toggleScreen; // to change screen
    bool prevTogScr;            // to control screen change
    bool saveParameters;        // keep initial value = 1
    bool statusReadFlag;
    bool enableServer; // enable encoder from webServer
    bool enablePLC;    // enable from PLC
};

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

// to navigate flagEnc struct
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

// to navigate secVar struct
secSystems *sP = &secVar;

typedef struct struct_encoderSettings
{
    uint8_t deviceIndex; // Index of the device. This will affect its IP address and the port used for UDP transmission
    uint8_t mac[6];      // Mac address of device
    uint16_t localPort;  // local port to listen on
    uint16_t deviceParameters[numberParameters];
    uint16_t arduinoParameters[ardParameters]; // parameters for screen orientation
    uint16_t remotePort;                       // remote port to transmit on
};

// default encoder parameters
struct_encoderSettings encSettings = {
    encSettings.deviceIndex = 1,
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
    encSettings.arduinoParameters[0] = 0,
    encSettings.remotePort = 3001,
};

// to navigate encSettings struct
struct_encoderSettings *eP = &encSettings;

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

// to navigate imuValues struct
struct_accgyroValues *iP = &imuValues;

#if !defined(ACCELEROMETER_ON)
iP->angX = 0.00;
iP->angY = 0.00;
#endif

/*
* Objects and instances
*/

ScreenEncoder myScreen; // for screen functions
#ifdef WEBSERVER_ON
ServerEncoder myServer; // for server functions
#endif
SensorEncoder mySensor;                                 // for sensor functions
SystemEncoder mySystem;                                 // for comunication functions
Tasker tasker(true);                                    // for tasking
QEI myPulse(PIN_SQWA, PIN_SQWB, PIN_ZERO, pulsePerRev); // to read encPulses
Average<double> mediaPuls(meanPulSamples);              // to calculate mean pulse value
EasyButton button(TOGGLE_BUTTON);                       // to toggle screen and reset encoder

#ifdef SENSOR_BME280
Adafruit_BME280 bme; // for temperature sensor
#endif

#if defined(WEBSERVER_ON) || defined(UDP_ON)
IPAddress ip(192, 168, 0, 21);
IPAddress remote(192, 168, 0, 1);
EthernetServer server(serverPort); // Server is configured in default port 80
#endif

#if defined(ARDUINO_NANO) && defined(SCREEN_ON)
Adafruit_SSD1306 display(screenW, screenH, &Wire, ST_RESET, i2cDurClk, i2cAftClk); // define OLED screen
#endif

#ifdef UDP_ON
EthernetUDP Udp;
#endif

#ifdef EXTMEMORY_ON
ExternalEEPROM myEEPROM;
#endif

#ifdef ACCELEROMETER_ON
Nano33BLEAccelerometerData accelerometerData; // to read imu sensor
Average<float> mediaAccX(meanSampleNumber);   // for average calculation (same below)
Average<float> mediaAccY(meanSampleNumber);
Average<float> mediaAccZ(meanSampleNumber);
#endif
