
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
    inline void updateScreenNum(void) __attribute__((always_inline));
    inline void startScreen(void) __attribute__((always_inline));
    void displayInitial(void);
    void displayTempHum(void);
    void displayDigitalLevel(void);
    void displayIPMAC(void);
    void displayPixVal(void);
    void displayFreqSpeed(void);
    void displaySleep(void);
    void displayWake(void);
    void splashScreen(void);
    void initialCheck(void);
    bool initParam(void);
    bool sensorStart(void);
    bool shieldStart(void);
    void finishSetup(void);
    void buttonSetup(void);
};
#endif

#ifdef WEBSERVER_ON
class ServerEncoder
{
private:
    inline static bool checkIflistened(uint8_t *p_rx0, int BUFFERSIZE) __attribute__((always_inline));
    inline bool spiWriteArd2STM(uint8_t address, uint16_t body, int slaveSelect) __attribute__((always_inline));
    inline int writeReg(uint8_t address, uint16_t body, int slaveSelect) __attribute__((always_inline));
    inline int readReg(uint8_t address, uint16_t *body, int slaveSelect) __attribute__((always_inline));
    //void printHeader(EthernetClient client);

public:
    inline int sendParameters(void) __attribute__((always_inline));
    inline bool spiReadArd2STM(uint8_t address, uint16_t *body, int slaveSelect) __attribute__((always_inline));
    static void updateDeviceStatus(uint16_t code16);
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