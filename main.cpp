//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "ignition.h"
#include "select_time_delay.h"
#include "user_interface.h"
#include "wipers.h"
//=====[Main function, the program entry point after power on or reset]========

int main()
{
   inputsInit();
   outputsInit();
   userInterfaceDisplayInit();
   while( true ) {
       checkSystemState();
       handleIgnition();
       handleWipers();
       delay(10);

   }
}
