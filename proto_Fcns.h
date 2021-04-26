
#ifdef WEBSERVER_ON

#ifdef ARDUINO_NANO
void resetFunc(void); // Declaration of the Arduino reset function. It is needed for rebooting from software
#elif defined(ARDUINO_MEGA)
void (*resetFunc)(void);
#endif

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

#ifdef UDP_ON
// udp functions to speak with the PLC
int listenUDP(void *Buffer, int Size);
void writeUDP(void *Buffer, int Size, IPAddress targetIP, unsigned int targetPort);
int bytesToInt(byte byte1, byte byte2);
#endif

// boot Functions
int16_t readParam(void);
#ifdef SHIELD_ON
bool bootShield(void);
#endif

// periodic functions to control systems
void checkSystems(void);

#if defined(SENSOR_BME280) || defined(SENSOR_AHT10)
// to update temperature sensor values
void tempUpdate(void);
#endif

#ifdef SCREEN_ON
void updateScreen(void); // oled screen functions
#endif

#ifdef EXTMEMORY_ON
// to start and update extEEPROM
void extEEPROMupdate(void);
void startEEPROM(void);
void loadEncSettings(void);
#endif

#ifdef ACCELEROMETER_ON
// to update imu status
void imuUpdate(void);
#endif
