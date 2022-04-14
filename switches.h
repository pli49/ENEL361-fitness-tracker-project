#ifndef SWITCHS_H_
#define SWITCHS_H_

// *******************************************************
// switches.h
//ENEL361 Fitness Monitor Project
// Written by:
// *  - Pengcheng Liu  49791816
// *  - Scott Parkin   82581593
// *  - Thomas wang    65193909
// Last modified:  18.05.2020
//
// *******************************************************

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
// Constants
//*****************************************************************************
enum sw_Names {SW_1 = 0, SW_2, NUM_SWITCHES};
enum sw_States {OFF = 0, ON};
// Switch 1
#define SW_1_PERIPH  SYSCTL_PERIPH_GPIOA
#define SW_1_PORT_BASE  GPIO_PORTA_BASE
#define SW_1_PIN  GPIO_PIN_7
#define SW_1_NORMAL  true
// Switch 2
#define SW_2_PERIPH  SYSCTL_PERIPH_GPIOA
#define SW_2_PORT_BASE  GPIO_PORTA_BASE
#define SW_2_PIN  GPIO_PIN_6
#define SW_2_NORMAL  true

// *******************************************************
// initButtons: Initialise the variables associated with the set of buttons
// defined by the constants above.
void
initSwitches (void);

// *******************************************************
// updateButtons: Function designed to be called regularly. It polls all
// buttons once and updates variables associated with the buttons if
// necessary.  It is efficient enough to be part of an ISR, e.g. from
// a SysTick interrupt.
void
updateSwitches (void);

// *******************************************************
// checkButton: Function returns the new button state if the button state
// (PUSHED or RELEASED) has changed since the last call, otherwise returns
// NO_CHANGE.  The argument butName should be one of constants in the
// enumeration butStates, excluding 'NUM_BUTS'. Safe under interrupt.
uint8_t
checkSwitch (uint8_t SwitchName);

#endif /*SWITCHS_H_*/
