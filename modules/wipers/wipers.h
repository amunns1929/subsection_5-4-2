//=====[#include guards - begin]===============================================

#ifndef _WIPERS_H_
#define _WIPERS_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================
typedef enum {
  WIPER_STATE_OFF,
  WIPER_STATE_LO,
  WIPER_STATE_HI,
  WIPER_STATE_INT
} WiperState_t;

typedef enum {
    WIPER_RISING,
    WIPER_FALLING,
    WIPER_FLAT
} WiperMovement_t;

extern WiperMovement_t wiperMovement;
extern WiperState_t wiperState;
extern float wiperModeReading;
extern float timeDelayReading;
//=====[Declarations (prototypes) of public functions]=========================

void handleWipers();
void wiperUpdateMode();
void wiperInit();
void wiperModeINT();
void selectTimeDelay();
void servoMovement();

//=====[#include guards - end]=================================================

#endif // _WIPERS_H_