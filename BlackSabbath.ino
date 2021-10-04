
/*
* BESTduino encoder, A.K.A. Black Sabbath

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

created 30 June 2021
V1.0.0
by Alex Rondon, Riccardo Salviati, Federico Santacatterina

*/

#include "src/general_Header.h"
#include "src/debug_Macro.h"
#include "src/class_File.h"
#include "src/constants_File.h"
#include "src/glob_Var.h"
#include "src/proto_Fcns.h"
#include "src/coms_File.h"
#include "src/secFcn_File.h"
#include "src/screen_Fcns.h"
#include "src/webServer_Fcns.h"
#include "src/task_Fcns.h"
#include "src/setup_Encoder.h"

void loop()
{
  //tasker.loop();
  spiSTM();
  delay(tSPIardST);
}

void loop2()
{
  webServerArdST();
  delay(tSERVERardST);
}

void loop3()
{
  statusRead();
  delay(tStatusSPI);
}

void loop4()
{
  stCheck();
  delay(tSTcheck);
}

void loop5()
{
  updateScreen();
  yield();
}

void loop6()
{
  tempUpdate();
  delay(tBMEupdate);
}

void loop7()
{
  checkSystems();
  delay(tSystemCheck);
}

void loop8()
{
  serverStatus();
  delay(tServerStatus);
}

void loop9()
{
  updateButton();
  delay(tButtonUpdate);
}

void loop10()
{
  extEEPROMupdate();
  delay(tUpdateMemory)
}

void loop11()
{
  imuUpdate();
  delay(tUpdateACC);
}