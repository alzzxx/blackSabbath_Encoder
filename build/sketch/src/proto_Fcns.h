#line 1 "c:\\Users\\a.rondon\\Documents\\GitHub\\BlackSabbath\\src\\proto_Fcns.h"

// * Prototype functions
/*
 - These are the functions called at regular intervals, controlled by the tasker library
 - All the other functions are called within these functions, can't be declared inside main 
 - encoder class because tasker library doesn't allow passing a method as an argument, that 
 - why they are declared here on the prototype functions file
 - Also there are present some functions that are passed as arguments
*/

void btnToggleScreen(void); // for screen toggling
void resetFunc(void);       // for encoder reset, from HW/SW
void stCheck(void);         // to send upd packet to PLC
void checkSystems(void);    // periodic functions to control systems
void updateButton(void);    // to update button pressing
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
#ifdef DEBUG_FCN_TIME
void pinConfig(int pin); // Function for measuring function exec time, debug purposes only
#endif
