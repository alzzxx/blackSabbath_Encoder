
/*
* Debug macro, to enable or disable Serial.print for debug purposes
*/

#define DEBUG_OLED_SCREEN
//#define DEBUG_WEBSERVER
//#define DEBUG_ETHERNET
//#define DEBUG_IMU_SENSOR
//#define DEBUG_SPI_ONE
//#define DEBUG_SPI_TWO
//#define DEBUG_I2C_COM
#define DEBUG_BOOT_FCN
//#define DEBUG_UDP_COM
//#define DEBUG_TASKS_FCN
//#define DEBUG_FREQ_FCN
//#define DEBUG_FCN_TIME

#if defined(DEBUG_OLED_SCREEN) || defined(DEBUG_WEBSERVER) || defined(DEBUG_IMU_SENSOR) || defined(DEBUG_I2C_COM) || defined(DEBUG_SPI_ONE) || defined(DEBUG_SPI_TWO) || defined(DEBUG_BOOT_FCN) || defined(DEBUG_UDP_COM) || defined(DEBUG_TASKS_FCN) || defined(DEBUG_FREQ_FCN)
#define DEBUG_SERIALBEGIN(x) Serial.begin(x)
#define DEBUG_DELAY(x) delay(x)
#else
#define DEBUG_SERIALBEGIN(x)
#define DEBUG_DELAY(x)
#endif

#ifdef DEBUG_OLED_SCREEN
#define DEBUG_SCREEN(x) Serial.print(x)
#define DEBUG_SCREENFLO(x, y) Serial.print(x, y)
#define DEBUG_SCREENLN(x) Serial.println(x)
#define DEBUG_SCREENLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_SCREEN(x)
#define DEBUG_SCREENFLO(x, y)
#define DEBUG_SCREENLN(x)
#define DEBUG_SCREENLNFLO(x, y)
#endif

#ifdef DEBUG_WEBSERVER
#define DEBUG_SERVER(x) Serial.print(x)
#define DEBUG_SERVERFLO(x, y) Serial.print(x, y)
#define DEBUG_SERVERLN(x) Serial.println(x)
#define DEBUG_SERVERLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_SERVER(x)
#define DEBUG_SERVERFLO(x, y)
#define DEBUG_SERVERLN(x)
#define DEBUG_SERVERLNFLO(x, y)
#endif

#ifdef DEBUG_SPI_ONE
#define DEBUG_SPIONE(x) Serial.print(x)
#define DEBUG_SPIONEFLO(x, y) Serial.print(x, y)
#define DEBUG_SPIONELN(x) Serial.println(x)
#define DEBUG_SPIONELNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_SPIONE(x)
#define DEBUG_SPIONEFLO(x, y)
#define DEBUG_SPIONELN(x)
#define DEBUG_SPIONELNFLO(x, y)
#endif

#ifdef DEBUG_SPI_TWO
#define DEBUG_SPITWO(x) Serial.print(x)
#define DEBUG_SPITWOFLO(x, y) Serial.print(x, y)
#define DEBUG_SPITWOLN(x) Serial.println(x)
#define DEBUG_SPITWOLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_SPITWO(x)
#define DEBUG_SPITWOFLO(x, y)
#define DEBUG_SPITWOLN(x)
#define DEBUG_SPITWOLNFLO(x, y)
#endif

#ifdef DEBUG_IMU_SENSOR
#define DEBUG_IMU(x) Serial.print(x)
#define DEBUG_IMUFLO(x, y) Serial.print(x, y)
#define DEBUG_IMULN(x) Serial.println(x)
#define DEBUG_IMULNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_IMU(x)
#define DEBUG_IMUFLO(x, y)
#define DEBUG_IMULN(x)
#define DEBUG_IMULNFLO(x, y)
#endif

#ifdef DEBUG_I2C_COM
#define DEBUG_I2C(x) Serial.print(x)
#define DEBUG_I2CFLO(x, y) Serial.print(x, y)
#define DEBUG_I2CLN(x) Serial.println(x)
#define DEBUG_I2CLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_I2C(x)
#define DEBUG_I2CFLO(x, y)
#define DEBUG_I2CLN(x)
#define DEBUG_I2CLNFLO(x, y)
#endif

#ifdef DEBUG_UDP_COM
#define DEBUG_UDP(x) Serial.print(x)
#define DEBUG_UDPFLO(x, y) Serial.print(x, y)
#define DEBUG_UDPLN(x) Serial.println(x)
#define DEBUG_UDPLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_UDP(x)
#define DEBUG_UDPFLO(x, y)
#define DEBUG_UDPLN(x)
#define DEBUG_UDPLNFLO(x, y)
#endif

#ifdef DEBUG_BOOT_FCN
#define DEBUG_BOOT(x) Serial.print(x)
#define DEBUG_BOOTFLO(x, y) Serial.print(x, y)
#define DEBUG_BOOTLN(x) Serial.println(x)
#define DEBUG_BOOTLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_BOOT(x)
#define DEBUG_BOOTFLO(x, y)
#define DEBUG_BOOTLN(x)
#define DEBUG_BOOTLNFLO(x, y)
#endif

#ifdef DEBUG_TASKS_FCN
#define DEBUG_TASKS(x) Serial.print(x)
#define DEBUG_TASKSFLO(x, y) Serial.print(x, y)
#define DEBUG_TASKSLN(x) Serial.println(x)
#define DEBUG_TASKSLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_TASKS(x)
#define DEBUG_TASKSFLO(x, y)
#define DEBUG_TASKSLN(x)
#define DEBUG_TASKSLNFLO(x, y)
#endif

#ifdef DEBUG_FREQ_FCN
#define DEBUG_FREQ(x) Serial.print(x)
#define DEBUG_FREQFLO(x, y) Serial.print(x, y)
#define DEBUG_FREQLN(x) Serial.println(x)
#define DEBUG_FREQLNFLO(x, y) Serial.println(x, y)
#else
#define DEBUG_FREQ(x)
#define DEBUG_FREQFLO(x, y)
#define DEBUG_FREQLN(x)
#define DEBUG_FREQLNFLO(x, y)
#endif

// Macro for debug, to set and clear pin A2 on arduino, used to measure exec. time of task functions
#ifdef DEBUG_FCN_TIME
#define DEBUG_PIN 30
#define PIN_UP NRF_GPIO->OUTSET = (1UL << DEBUG_PIN)
#define PIN_DOWN NRF_GPIO->OUTCLR = (1UL << DEBUG_PIN)
#else
#define PIN_UP
#define PIN_DOWN
#endif