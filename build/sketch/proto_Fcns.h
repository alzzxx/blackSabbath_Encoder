
#ifdef WEBSERVER_ON
void resetFunc(void); // Declaration of the Arduino reset function. It is needed for rebooting from software

// spi functions to communicate with F031K6
static bool checkIflistened(uint8_t *p_rx0, int BUFFERSIZE);
bool SpiWriteArd2STM(uint8_t address, uint16_t body, int slaveSelect);
bool SpiReadArd2STM(uint8_t address, uint16_t *body, int slaveSelect);
int SendParameters(void);
void statusRead(void);
static void updateDeviceStatus(uint16_t code16);
int readReg(uint8_t address, uint16_t *body, int slaveSelect);
int writeReg(uint8_t address, uint16_t body, int slaveSelect);
void spiSTM(void);

// webserver functions
void printHeader(EthernetClient client);
void printPage(EthernetClient client);
unsigned char h2d(unsigned char hex_1, unsigned char hex_2);
String findData(int from);
int parseResponse(void);
void ajaxInitialize(EthernetClient client);
void ajaxUpdateDiag(EthernetClient client);
bool displayWebServer(void);
void webServerArdST(void);
void serverStatus(void);
#endif

int16_t readParam(void); // initial parameters reading
void checkSystems(void); // periodic functions to control systems

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
