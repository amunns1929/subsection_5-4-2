//=====[Libraries]=============================================================

//probably do not need all, take out some later if need be
#include "mbed.h"
#include "arm_book_lib.h"
#include "select_time_delay.h"
#include "ignition.h"
#include "display.h"
#include "wipers.h"
 //=====[Declaration of private defines]========================================
#define INT_3_DELAY_MS 3000 //3 second delay
#define INT_6_DELAY_MS 6000 //6 second delay
#define INT_8_DELAY_MS 8000 //8 second delay
#define INT_THRESHHOLD_1 0.33
#define INT_THRESHHOLD_2 0.66
#define TIME_INCREMENT_MS 10 //for engine ignition
int SELECTED_TIME_DELAY; //leave blank so value can be assigned? or set to value that can be changed?


AnalogIn timeDelay(A2); //potentiometer for selecting the time for INT

 //=====[Implementations of public functions]===================================

void selectTimeDelay() //where the user selects the time delay for INT
{   timeDelayReading = timeDelay.read();
    if ( timeDelayReading <= INT_THRESHHOLD_1) {

      SELECTED_TIME_DELAY = INT_3_DELAY_MS;

  } else if (timeDelayReading >INT_THRESHHOLD_1 &&
             timeDelayReading <= INT_THRESHHOLD_2) {

      SELECTED_TIME_DELAY = INT_6_DELAY_MS;

  }
    else {

      SELECTED_TIME_DELAY = INT_8_DELAY_MS;

  } //maybe return selected_time_delay?? 
}
