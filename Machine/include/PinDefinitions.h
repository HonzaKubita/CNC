// PinDefinitions.h

#ifndef __PIN_DEFINITIONS_H__
#define __PIN_DEFINITIONS_H__

// Rotary encoder
#define encoderSW 51
#define encoderDT 52
#define encoderCLK 53

// LCD (I2C)
#define displayAddress 0x27
#define displayChars 16
#define displayRows 4

// CNC Shield - Motors
#define stepperDirY1 7
#define stepperDirY2 6
#define stepperDirX 5
#define stepperStepY1 4
#define stepperStepY2 3
#define stepperStepX 2
// CNC Shield -  Endstops
#define endstopY1 11
#define endstopY2 10
#define endstopX  9

#endif // __PIN_DEFINITIONS_H__