*******************************************
* BESTduino encoder, A.K.A. Black Sabbath *
*******************************************

- This device uses an optical sensor (PIXART PAT9130) to detect movement and build an encoder signal
proportional to the speed of the moving surface seen by the sensor. All calculations and generation of 
encoder signals are made on ST F031K6 nucleo board, refer to that source code to get additional info
on how this is done.
- Arduino board handle the user interface: webServer and main display, also all periferal sensors as 
temperature sensor and acelerometer.
- External eeprom is also handle by the arduino, this memory is used to save encoder parameters at 
encoder shutdown, at the boot up, current parameters are read from eeprom and send to st board, any
additional modification of those values can be done from webServer, new values are automatically 
sent to ST board and saved on eeprom.
- Arduino board also provided an electronic bubble level, that allows to get a visual feedback on the
encoder position and alligment, this is achieved by reading the internal acelerometer, values are
shown on display and webServer
- It's possible to get an accurate calculation of the current encoder signal frequency, this is, the 
distances between A and B signals, visible only from the display, not from webServer
- Main functions are called from the main loop at fixed intervals, set by the programmer, using the 
tasker library. The only functions that get called from main loop can be seen on the task_fcns file,
all the other methods/functions are called within the functions present on that file.
- Except from task_fcns functions, pinConfig and interrupts, all the other functions are declared inside
classes for better organizations of differents tasks.
- Serial print for debug purposes can be enabled or disabled using the debug_Macro file, default is
disabled.
- Encoder schematics and pinout can be found here:
G:\ARCHIVIO MACCHINE\matricole 19\P1982 Progetto ispezione pelli\Documenti SED\Encoder contactless\Progetto\KiCad

-------------------------------------
- Compiling and downloading program -
-------------------------------------

- Arduino IDE V1.8.15 or later is neccesary, download and install: https://downloads.arduino.cc/arduino-1.8.15-windows.exe
- Inside Arduino IDE is necessary to install the mbed board package: Arduino mbed OS board V1.3.2, do not install a different version!
- Additional libraries are neccesary to properly compile and load the program to arduino board. Inside the BlackSabbath directory there is a folder called 
"libraries", copy all those folders inside "libraries" to the following path C:\Users\USER\Documents\Arduino\libraries. Do not update the libraries on the
Arduino IDE to ensure compatibility, use only the libraries provided. The necessary libraries are:

    * Adafruit BME280
    * Adafruit GFX 
    * Adafruit SSD1306
    * Adafruit SSD1306 Wemos mini OLED
    * Adafruit Unified sensor
    * Arduino HTS221
    * Arduino LSM9DS1
    * Average
    * EasyButton
    * Ethernet (already included on the Arduino IDE installation)
    * Madgqick
    * Nano33BLESensor
    * QEI
    * SparkFun External EEPROM Arduino
    * Tasker
    * SD (already included on the Arduino IDE installation)
    * SPI (already included on the Arduino IDE installation)
    * Wire (already included on the Arduino IDE installation)

- Also inside the BlackSabbath directory there is another folder called EthernetCustom, copy the only file inside it ("EthernetCustom.h") to the following path: 
C:\Program Files (x86)\Arduino\libraries\Ethernet\src, this is the standard ethernet library (V2.0.0) that comes with the Arduino IDE
- After all files are properly copied, compiling and uploading can be performed. The correct board and serial board must be selected on the Arduino IDE


created 30 June 2021
V1.0.0
by Alex Rondon, Riccardo Salviati, Federico Santacatterina

