
// * Task Functions
/*
 - These are the functions called at regular intervals, they are controlled by the tasker library
 - All main functions are called within these functions, they are the functions called on the main loop
 - Cannot be declared inside main encoder class because tasker library doesn't allow passing a method as
 - an function argument, that why they are declared here on the prototype functions file
*/

void stCheck(void);      // to send upd packet to PLC
void checkSystems(void); // periodic functions to control systems
#ifdef SENSOR_BME280
void tempUpdate(void); // to update temperature sensor values
#endif
#ifdef EXTMEMORY_ON
void extEEPROMupdate(void); // to update eeprom status "if it's alive"
#endif
#ifdef ACCELEROMETER_ON
void imuUpdate(void); // to update imu status
#endif
#ifdef WEBSERVER_ON
void statusRead(void);     // spi functions to communicate with F031K6
void spiSTM(void);         // spi functions to communicate with F031K6
void serverStatus(void);   // to check if server if alive
void webServerArdST(void); // main function that shows the webserver
#endif
#ifdef SCREEN_ON
void updateScreen(void); // oled screen functions
#endif

void resetFunc(void);       // for encoder reset, from HW/SW
void btnToggleScreen(void); // for screen toggling
void updateButton(void);    // to update button pressing
int16_t readParam(void);    // initial parameters reading
#ifdef DEBUG_FCN_TIME
void pinConfig(int pin); // Function for measuring function exec time, debug purposes only
#endif
#ifdef WEBSERVER_ON
// webserver functions
void printHeader(EthernetClient client);
void printPage(EthernetClient client);
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
// to start and update extEEPROM
#ifdef EXTMEMORY_ON
void startEEPROM(void);
void loadEncSettings(void);
#endif
