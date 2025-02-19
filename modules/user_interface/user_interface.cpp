//=====[Libraries]=============================================================

#include "display.h"
#include "ignition.h"
#include "mbed.h"
#include "arm_book_lib.h"
#include "select_time_delay.h"
#include "user_interface.h"
#include "wipers.h"

//=====[Declaration of private defines]========================================

#define INT_3_DELAY_MS 3000 //3 second delay
#define INT_6_DELAY_MS 6000 //6 second delay
#define INT_8_DELAY_MS 8000 //8 second delay


 //=====[Implementations of public functions]===================================
 void userInterfaceDisplayInit()
{
    displayInit();
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Mode:" );

}

void userInterfaceDisplayUpdate()
{
    if (wiperState == WIPER_STATE_OFF) {
        displayCharPositionWrite ( 5,0 );
        displayStringWrite( "OFF ");
    }
    if (wiperState == WIPER_STATE_LO) {
        displayCharPositionWrite ( 5,0 );
        displayStringWrite( "LO ");
    }
    if (wiperState == WIPER_STATE_HI) {
        displayCharPositionWrite ( 5,0 );
        displayStringWrite( "HI ");
    }
    if (wiperState == WIPER_STATE_INT) {
        displayCharPositionWrite ( 5,0 );
        displayStringWrite( "INT ");
        displayCharPositionWrite ( 0,1 );
        displayStringWrite( "Delay Time:     ");
        if (SELECTED_TIME_DELAY == INT_3_DELAY_MS){
            displayCharPositionWrite ( 11,1 );
            displayStringWrite( "SHORT");
        }
        if (SELECTED_TIME_DELAY == INT_6_DELAY_MS){
            displayCharPositionWrite ( 11,1 );
            displayStringWrite( "MED.");
        }
        if (SELECTED_TIME_DELAY == INT_8_DELAY_MS){
            displayCharPositionWrite ( 11,1 );
            displayStringWrite( "LONG");
        }
    }

}