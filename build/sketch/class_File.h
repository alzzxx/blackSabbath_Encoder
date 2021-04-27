
class BestEncoder
{
private:
#ifdef SCREEN_ON
    inline void setDisp(uint8_t tSize, bool isInverted, uint8_t xC, uint8_t xY, bool isCursor) __attribute__((always_inline));

    inline void dispWarning(uint8_t xx, uint8_t yy) __attribute__((always_inline));

    inline void displayIndicator(uint8_t displayNumber) __attribute__((always_inline));

    void frameHeader(uint8_t cursorX, uint8_t cursorY, uint8_t sizeText, bool invIS, const char *const buffer[], uint8_t num, bool isAcc);

    void showText(uint16_t cx1, uint16_t cy1, const char *const bufferText[], uint8_t numB, bool isCentered);
#endif

#ifdef ACCELEROMETER_ON
    inline int16_t roundFunction(int16_t d) __attribute__((always_inline));

    inline void slopeCalc(void) __attribute__((always_inline));
#endif

#ifdef UDP_ON
    int16_t bytesToInt(byte byte1, byte byte2);
#endif

public:
#ifdef SCREEN_ON
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
#endif

#ifdef UDP_ON
    uint16_t listenUDP(byte *buffer, uint8_t size);

    void writeUDP(uint8_t *buffer, uint16_t size, IPAddress targetIP, uint16_t targetPort);
#endif

#if defined(SENSOR_BME280)
    void bmeStart(void);
#elif defined(SENSOR_AHT10)
    void ahtStart(void);
#endif

#ifdef ACCELEROMETER_ON
    bool startIMU(void);

    void imuRead(void);
#endif

#ifdef EXTMEMORY_ON
    bool writeReadBI2C(uint32_t addr, uint8_t body);

    bool writeReadWI2C(uint32_t addr, uint16_t body);

    void putEncParameters(uint32_t addr);

    void writeEncParameter(uint32_t addr, uint8_t byteToSave);
#endif

    inline void readEncoder(void) __attribute__((always_inline));
};