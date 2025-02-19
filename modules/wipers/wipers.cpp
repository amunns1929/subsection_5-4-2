//=====[Libraries]=============================================================

//probably do not need all, take out some later if need be
#include "mbed.h"
#include "arm_book_lib.h"
#include "user_interface.h"
#include "wipers.h"
#include "ignition.h"
#include "display.h"
#include "select_time_delay.h"

//=====[Declaration of private defines]========================================
#define HI_TIME_DELAY 279// fill in
#define LO_TIME_DELAY 370// fill in
#define POTENTIOMETER_HI_SELECT 0.75
#define POTENTIOMETER_LO_SELECT 0.25
#define POTENTIOMETER_OFF_CUTOFF 0
#define DUTY_MIN 0.025 //the starting position for the servo motor
#define DUTY_MAX 0.057 //change this value so that the motor moves 67 
#define POTENTIOMETER_INT_SELECT 0.5
#define INT_3_DELAY_MS 3000 //3 second delay
#define INT_6_DELAY_MS 6000 //6 second delay
#define INT_8_DELAY_MS 8000 //8 second delay
#define INT_THRESHHOLD_1 0.33
#define INT_THRESHHOLD_2 0.66
#define TIME_INCREMENT_MS 10 //for engine ignition
//#define SELECTED_TIME_DELAY //leave blank so value can be assigned? or set to value that can be changed?
#define PERIOD 0.02 //units are seconds

//=====[Declaration and initialization of public global objects]===============

AnalogIn wiperMode(A1); //potentiometer reading in mode selection
//AnalogIn timeDelay(A2); //potentiometer for selecting the time for INT

PwmOut servo(PF_9);    // wiper 1

float wiperModeReading = 0.0;
float timeDelayReading = 0.0;
WiperState_t wiperState = WIPER_STATE_OFF;
WiperMovement_t wiperMovement = WIPER_FLAT;

 //=====[Implementations of public functions]===================================

void handleWipers() {
   wiperUpdateMode();
   userInterfaceDisplayUpdate();
   if ( engineRunning ) { //could change this to while loop so it executes multiple times??
       switch ( wiperState ) { 
           case WIPER_STATE_OFF:
               servo.period(PERIOD); //optional if not moving?
               servo.write(DUTY_MIN);
               delay(200); //resets servo to initial position
            //may need to add delay here
               break;
           case WIPER_STATE_LO: //need to figure out value for LO_TIME_DELAY
               servoMovement(); //may need delay after
               servo.period(PERIOD);
               servo.write(DUTY_MIN);
               delay( LO_TIME_DELAY );
               servo.write(DUTY_MAX);
               delay(200);
               break;
           case WIPER_STATE_HI: //need to figure out value for HI_TIME_DELAY
               servoMovement(); //may need delay after
               servo.period(PERIOD);
               servo.write(DUTY_MIN);
               delay( HI_TIME_DELAY );
               servo.write(DUTY_MAX);
               delay(200);
               break;
           case WIPER_STATE_INT:
               servoMovement(); //may need delay after
               delay(200);
               wiperModeINT();
       }
   } else {



        servo.period(PERIOD);
        servo.write(DUTY_MIN); //while engine is off, wipers are in off position and do not move
        delay(TIME_INCREMENT_MS);

            }
}

void servoMovement(){
    while (engineRunning) {
        if (!engineRunning) {
            switch ( wiperMovement ) { //change all of these to continuous servo
                case WIPER_RISING:
                    servo.period(PERIOD);
                    servo.write(DUTY_MAX); //wiper continues up to the top
            //may need to add delay here
                    servo.write(DUTY_MIN); //wiper goes to bottom again
                    break;
                case WIPER_FALLING: //brings wiper down to initial position, continues falling
                    servo.period(PERIOD);
                    servo.write(DUTY_MIN);

                    break;
                case WIPER_FLAT: //I believe this makes it so the wiper does not move
                    servo.period(PERIOD);
                    servo.write(DUTY_MIN);


                }
            
            }
    }
}

void wiperUpdateMode() { //potentiometer choosing what wiper state we are in
    wiperModeReading = wiperMode.read();

    if ( wiperModeReading <= POTENTIOMETER_LO_SELECT) {

      wiperState = WIPER_STATE_OFF;

  } else if ( wiperModeReading > POTENTIOMETER_LO_SELECT &&
              wiperModeReading <= POTENTIOMETER_INT_SELECT) {

      wiperState = WIPER_STATE_LO;

  } else if ( wiperModeReading > POTENTIOMETER_INT_SELECT &&
              wiperModeReading <= POTENTIOMETER_HI_SELECT) {

      wiperState = WIPER_STATE_INT;

  }
    else {

      wiperState= WIPER_STATE_HI;
  }
}






void wiperModeINT() //what happens when INT is selected
{ //make this a loop, unless while loop change made above?
    selectTimeDelay();
    servo.period(PERIOD);
    servo.write(DUTY_MIN);
    delay( SELECTED_TIME_DELAY );
    servo.write(DUTY_MAX);
}
