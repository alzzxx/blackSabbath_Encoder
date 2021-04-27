#include <Arduino.h>
#line 1 "c:\\Users\\a.rondon\\Documents\\GitHub\\blackSabbath_Encoder\\BlackSabbath.ino"

#include "general_Head.h"
#include "debug_Macro.h"
#include "class_File.h"
#include "glob_Var.h"
#include "proto_Fcns.h"
#include "spi_Fcns.h"
#include "i2c_Fcns.h"
#include "imu_Fcns.h"
#include "screen_Fcns.h"
#include "webServer_Fcns.h"
#include "udp_Fcns.h"
#include "boot_Fcns.h"
#include "freq_Fcns.h"
#include "task_Fcns.h"
#include "setup_Encoder.h"

void loop()
{
  tasker.loop();
}
