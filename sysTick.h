#ifndef SYSTICK_H_
#define SYSTICK_H_

// *******************************************************
//Switch and button push detector for the fitness monitor project
//
// sysTick.h
//
// ENEL361 Fitness Monitor Project
//
//  Written by:
// *  - Pengcheng Liu  49791816
// *  - Scott Parkin   82581593
// *  - Thomas wang    65193909
//
// *******************************************************


/*********************************************************
 * ISR action. Determine if a button is pushed or if the switch is switched,
 * if so, change the display accordingly
 *********************************************************/
void
SysTickIntHandler (uint8_t toggle, uint8_t toggle_units, uint32_t steps, uint32_t distance, uint32_t hold_count);


/*********************************************************
 * Initialize periodic ISR
 *********************************************************/
void
initSysTick (void);

#endif /* SYSTICK_H_ */
