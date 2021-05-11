
void resetFunc(void);       // for encoder reset, from HW/SW
void btnToggleScreen(void); // for screen toggling
void updateButton(void);    // to update button pressing
void checkSystems(void);    // periodic functions to control systems
int16_t readParam(void);    // initial parameters reading
void stCheck(void);         // to send upd packet to PLC
#ifdef DEBUG_FCN_TIME
void pinConfig(int pin); // Function for measuring function exec time, debug purposes only
#endif

#ifdef WEBSERVER_ON
// spi functions to communicate with F031K6
bool SpiWriteArd2STM(uint8_t address, uint16_t body, int slaveSelect);
bool SpiReadArd2STM(uint8_t address, uint16_t *body, int slaveSelect);
int SendParameters(void);
int readReg(uint8_t address, uint16_t *body, int slaveSelect);
int writeReg(uint8_t address, uint16_t body, int slaveSelect);
void statusRead(void);
void spiSTM(void);
static void updateDeviceStatus(uint16_t code16);
static bool checkIflistened(uint8_t *p_rx0, int BUFFERSIZE);

// webserver functions
void printHeader(EthernetClient client);
void printPage(EthernetClient client);
void webServerArdST(void);
void serverStatus(void);
void ajaxInitialize(EthernetClient client);
void ajaxUpdateDiag(EthernetClient client);
unsigned char h2d(unsigned char hex_1, unsigned char hex_2);
String findData(int from);
int parseResponse(void);
bool displayWebServer(void);
#endif

#ifdef SHIELD_ON
bool bootShield(void);
#endif

#ifdef SENSOR_BME280
void tempUpdate(void); // to update temperature sensor values
#endif

#ifdef SCREEN_ON
void updateScreen(void); // oled screen functions
#endif

// to start and update extEEPROM
#ifdef EXTMEMORY_ON
void extEEPROMupdate(void);
void startEEPROM(void);
void loadEncSettings(void);
#endif

// to update imu status
#ifdef ACCELEROMETER_ON
void imuUpdate(void);
#endif
