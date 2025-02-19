//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

//=====[Declaration of public defines]=========================================



//=====[Declaration of public data types]======================================

typedef enum {
   IDLE,
   IGNITION_ON,
   ENGINE_ON
} IgnitionState_t;

extern IgnitionState_t ignitionState;

extern bool engineRunning; // Tracks if the engine is running
extern bool driverSeated;  // tracks if the headlight mode is auto
extern bool reasonInhibition;


extern bool ignitionButtonReleased;
extern int ignitionReleaseTimes;
//=====[Declarations (prototypes) of public functions]=========================

void handleIgnition();
void engineStop();
void displayInhibitionReasons();
void inputsInit();
void outputsInit();
void engineStop();
void checkSystemState();

//=====[#include guards - end]=================================================

#endif // _IGNITION_H_