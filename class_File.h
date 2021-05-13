
/*
* Main encoder class for encoder functions
*/

#ifdef SCREEN_ON
class ScreenEncoder
{
private:
    inline void setDisp(uint8_t tSize, bool isInverted, uint8_t xC, uint8_t xY, bool isCursor) __attribute__((always_inline));
    inline void dispWarning(uint8_t xx, uint8_t yy) __attribute__((always_inline));
    inline void displayIndicator(uint8_t displayNumber) __attribute__((always_inline));
    void frameHeader(uint8_t cursorX, uint8_t cursorY, uint8_t sizeText, bool invIS, const char *const buffer[], uint8_t num, bool isAcc);
    void showText(uint16_t cx1, uint16_t cy1, const char *const bufferText[], uint8_t numB, bool isCentered);

public:
    void startScreen(void);
    void splashScreen(void);
    void initialCheck(void);
    bool initParam(void);
    bool shieldStart(void);
    bool sensorStart(void);
    void finishSetup(void);
    inline void updateScreenNum(void) __attribute__((always_inline));
    inline void displayInitial(void) __attribute__((always_inline));
    inline void displayPixVal(void) __attribute__((always_inline));
    inline void displayFreqSpeed(void) __attribute__((always_inline));
    inline void displayIPMAC(void) __attribute__((always_inline));
    inline void displayDigitalLevel(void) __attribute__((always_inline));
    inline void displayTempHum(void) __attribute__((always_inline));
    void displaySleep(void);
    void displayWake(void);
    void buttonSetup(void);
};
#endif

#ifdef WEBSERVER_ON
class ServerEncoder
{
private:
    inline static bool checkIflistened(uint8_t *p_rx0, uint8_t BUFFERSIZE) __attribute__((always_inline));
    inline bool spiWriteArd2STM(uint8_t address, uint16_t body, uint8_t slaveSelect) __attribute__((always_inline));
    inline uint16_t writeReg(uint8_t address, uint16_t body, uint8_t slaveSelect) __attribute__((always_inline));
    inline uint16_t readReg(uint8_t address, uint16_t *body, uint8_t slaveSelect) __attribute__((always_inline));
    inline void printHeader(EthernetClient client) __attribute__((always_inline));
    inline void serverHeader(EthernetClient client) __attribute__((always_inline));
    inline void serverJavaScript(EthernetClient client) __attribute__((always_inline));
    inline void serverCSS(EthernetClient client) __attribute__((always_inline));
    inline void serverSVG(EthernetClient client) __attribute__((always_inline));
    inline void serverBody(EthernetClient client) __attribute__((always_inline));
    uint8_t parseResponse(void);
    inline String findData(int16_t from) __attribute__((always_inline));
    inline unsigned char h2d(unsigned char hex_1, unsigned char hex_2) __attribute__((always_inline));
    void printPage(EthernetClient client);
    void ajaxInitialize(EthernetClient client);
    void ajaxUpdateDiag(EthernetClient client);

public:
    inline uint16_t sendParameters(void) __attribute__((always_inline));
    inline bool spiReadArd2STM(uint8_t address, uint16_t *body, uint8_t slaveSelect) __attribute__((always_inline));
    static void updateDeviceStatus(uint16_t code16);
    bool displayWebServer(void);
};
#endif

class SensorEncoder
{
private:
#ifdef ACCELEROMETER_ON
    inline int16_t roundFunction(int16_t d) __attribute__((always_inline));
    inline void slopeCalc(void) __attribute__((always_inline));
#endif

public:
#ifdef SENSOR_BME280
    void bmeStart(void);
#endif
#ifdef ACCELEROMETER_ON
    bool startIMU(void);
    inline void imuRead(void) __attribute__((always_inline));
#endif
};

class SystemEncoder
{
private:
#ifdef UDP_ON
    int16_t bytesToInt(byte byte1, byte byte2);
#endif
#ifdef EXTMEMORY_ON
    void startEEPROM(void);
    void loadEncSettings(void);
#endif

public:
    inline void readEncoder(void) __attribute__((always_inline));
#ifdef SHIELD_ON
    bool bootShield(void);
#endif
#ifdef UDP_ON
    uint16_t listenUDP(byte *buffer, uint8_t size);
    inline void writeUDP(uint8_t *buffer, uint16_t size, IPAddress targetIP, uint16_t targetPort) __attribute__((always_inline));
#endif
#ifdef EXTMEMORY_ON
    int16_t readParam(void);
    inline bool writeReadBI2C(uint32_t addr, uint8_t body) __attribute__((always_inline));
    inline bool writeReadWI2C(uint32_t addr, uint16_t body) __attribute__((always_inline));
    void putEncParameters(uint32_t addr);
    void writeEncParameter(uint32_t addr, uint8_t byteToSave);
#endif
};