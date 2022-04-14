// *******************************************************
//
//Switch and button push detector for the fitness monitor project
// sysTick.c
//
// ENEL361 Fitness Monitor Project
//
// Written by:
// *  - Pengcheng Liu  49791816
// *  - Scott Parkin   82581593
// *  - Thomas wang    65193909
// This file contains portions of code that written by P.J. Bones.
//
// *******************************************************
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/pin_map.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "buttons4.h"
#include "switches.h"
#include "sysTick.h"


/*********************************************************
 * ISR action. Determine if a button is pushed or if the switch is switched,
 * if so, change the display accordingly
 *********************************************************/
void
SysTickIntHandler (uint8_t toggle, uint8_t toggle_units, uint32_t steps, uint32_t distance, uint32_t hold_count)
{
    //toggle between the steps and distance
    uint8_t butState_left;
    uint8_t butState_right;
    uint8_t butState_up;
    uint8_t butState_down;
    uint8_t sw_1state;
    uint8_t adjust_enable = 0; //enables the change in step number with buttons


    updateButtons ();
    updateSwitches ();

    // Check if switch 1 is up or down
    sw_1state = checkSwitch(SW_1);
    switch (sw_1state)
    {
    case ON:
        adjust_enable = 1;
        break;
    case OFF:
        adjust_enable = 0;
        break;
    }

    //Check if left button is pressed
    butState_left = checkButton (LEFT);
    switch (butState_left)
    {
    case PUSHED:
        if (toggle < 1) {
            toggle++;
        } else{
            toggle = 0;
        }
        break;
    case RELEASED:
        break;
    }

    //Check if right button is pressed
    butState_right = checkButton (RIGHT);
    switch (butState_right)
    {
    case PUSHED:
        if (toggle < 1) {
            toggle++;
        } else{
            toggle = 0;
        }
        break;
    case RELEASED:
        break;
    }

    //Check if top button is pressed
    butState_up =checkButton (UP);
    switch (butState_up)
    {
    case PUSHED:
        if (toggle_units < 1 && adjust_enable == 0) {
            toggle_units++;
        } else if (adjust_enable == 0) {
            toggle_units = 0;
        } else if (adjust_enable == 1) {
            steps += 100;
        }
        break;
    case RELEASED:
        break;
    }

    //Check if down button is pressed or hold
    butState_down =checkButton (DOWN);
    switch (butState_down)
    {
    case PUSHED:
        if (adjust_enable == 0) {
        hold_count = 1;
        break;
        } else if (adjust_enable == 1){
            steps -= 100;
            break;
        }
    case NO_CHANGE:
        if (hold_count == 100 && adjust_enable == 0) {
            steps = 0;
            distance = 0;
            break;
        } else if (hold_count != 0 && adjust_enable == 0) {
            hold_count++;
            break;
        } else {
            break;
        }
    case RELEASED:
        if (adjust_enable == 0){
            hold_count = 0;
            break;
        } else {
            break;
        }
    }
}
/*********************************************************
 * Initialize periodic ISR
 *********************************************************/
void
initSysTick (void)
{
    SysTickPeriodSet (SysCtlClockGet ()/ 100);
    SysTickIntRegister (SysTickIntHandler);
    SysTickIntEnable ();
    SysTickEnable ();
}
