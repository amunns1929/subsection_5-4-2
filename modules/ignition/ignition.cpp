
//=====[Libraries]=============================================================

//probably do not need all, take out some later if need be
#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"
#include "wipers.h"
#include "select_time_delay.h"
#include "display.h"

//include all other modules this relates to

#define TIME_INCREMENT_MS 10 //for engine ignition

//=====[Declaration and initialization of public global objects]===============


DigitalIn ignitionButton(BUTTON1); // Simulates the ignition button

DigitalIn pSeatSens(D11);      // Passenger seat sensor
DigitalIn dSeatSens(D10);      // Driver seat sensor

DigitalIn pSeatBelt(D13);      // Passenger seatbelt switch
DigitalIn dSeatBelt(D12);      // Driver seatbelt switch

DigitalOut ignitionLed(LED1); // Green LED: Ignition enabled
DigitalOut engineLed(LED2);   // Blue LED: Engine started
DigitalInOut alarmBuzzer(PE_10); // Alarm Buzzer for inhibited ignition

BufferedSerial uartUsb(USBTX, USBRX, 115200); // UART for messages

IgnitionState_t ignitionState = IDLE;
bool reasonInhibition = false;
bool driverSeated = false;
bool engineRunning = false;
bool ignitionButtonReleased = false;
int ignitionReleaseTimes = 0;
 //=====[Implementations of public functions]===================================
 
void handleIgnition()
{
   switch ( ignitionState ) {
       case IDLE:
           if ( ignitionButton ) {
               if ( ignitionLed ) {
                   ignitionState = IGNITION_ON;
               } else {
                   alarmBuzzer.output();
                   if ( !reasonInhibition ) {
                       reasonInhibition = true;
                       uartUsb.write( "Ignition inhibited. \r\n", 22 );
                       displayInhibitionReasons();
                   }
               }
           }
           break;




       case IGNITION_ON:
           ignitionLed = OFF;
           engineLed = ON;
           uartUsb.write( "Engine started. \r\n", 18 );
           engineRunning = true;
           ignitionState = ENGINE_ON;
           alarmBuzzer.input();
           ignitionReleaseTimes = 0;
           break;
     
       case ENGINE_ON:
           if ( ignitionButton ){
               ignitionButtonReleased = false;
               if ( ignitionReleaseTimes < 1 ) {
                   delay( TIME_INCREMENT_MS );
                   if ( !ignitionButton ) {
                       ignitionButtonReleased = true;
                       ignitionReleaseTimes++;
                   }
               }
           }




           if ( ignitionReleaseTimes >= 1 ) {
               engineStop();
           }
           break;




   }
}

void displayInhibitionReasons() {
   if ( !dSeatSens ){
       uartUsb.write( "Driver seat not occupied.\r\n", 27 );
   }
   if ( !pSeatSens ){
       uartUsb.write( "Passenger seat not occupied\r\n", 30 );
   }
   if ( !dSeatBelt ){
       uartUsb.write( "Driver seatbelt not fastened\r\n", 30 );
   }
   if ( !pSeatBelt ){
       uartUsb.write( "Passenger seatbelt not fastened\r\n", 33 );
   }
}
  
void inputsInit()
{
   // Configure inputs as pull-down to ensure default state is LOW
   ignitionButton.mode( PullDown );
   pSeatSens.mode( PullDown );
   dSeatSens.mode( PullDown );
   pSeatBelt.mode( PullDown );
   dSeatBelt.mode( PullDown );
   alarmBuzzer.input(); //turns it off because when it's input it's not connected to ground
}



void outputsInit()
{
   // Initialize outputs to OFF
   ignitionLed = OFF;
   engineLed = OFF;

}


void engineStop()
{
   engineLed = OFF;
   uartUsb.write( "Engine stopped.\r\n", 17 );
   ignitionState = IDLE;
   engineRunning = false;
   handleWipers();

}

void checkSystemState()
{
   if ( dSeatSens && !driverSeated ) {
       uartUsb.write( "Welcome to enhanced alarm system model 218-W24 \r\n", 49 );
       driverSeated = true;
   }




   if ( ignitionState == ENGINE_ON ) {
       return;
   }
 
   if ( dSeatSens && pSeatSens && dSeatBelt && pSeatBelt ) {
       ignitionLed = ON;
   } else {
       ignitionLed = OFF;
   }
}
