// *******************************************************
//Support switch1 on the Tiva/Orbit.
//
// switches.h
//ENEL361 Fitness Monitor Project
//Written by:
// *  - Pengcheng Liu  49791816
// *  - Scott Parkin   82581593
// *  - Thomas wang    65193909
//
// *******************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "inc/tm4c123gh6pm.h"  // Board specific defines (for PF0)
#include "switches.h"


// *******************************************************
// Globals to module
// *******************************************************
static bool sw_state[NUM_SWITCHES];    // Corresponds to the electrical state
static uint8_t sw_count[NUM_SWITCHES];
static bool sw_normal[NUM_SWITCHES];   // Corresponds to the electrical state

// *******************************************************
// initButtons: Initialise the variables associated with the set of buttons
// defined by the constants in the buttons2.h header file.
void
initSwitches (void)
{
    int i;

    // SW_1 switch (active HIGH)
    SysCtlPeripheralEnable (SW_1_PERIPH);
    GPIOPinTypeGPIOInput (SW_1_PORT_BASE, SW_1_PIN);
    GPIOPadConfigSet (SW_1_PORT_BASE, SW_1_PIN, GPIO_STRENGTH_2MA,
       GPIO_PIN_TYPE_STD_WPD);
    sw_normal[SW_1] = SW_1_NORMAL;
    // SW_2 button (active HIGH)
    SysCtlPeripheralEnable (SW_1_PERIPH);
    GPIOPinTypeGPIOInput (SW_2_PORT_BASE, SW_2_PIN);
    GPIOPadConfigSet (SW_2_PORT_BASE, SW_2_PIN, GPIO_STRENGTH_2MA,
       GPIO_PIN_TYPE_STD_WPD);
    sw_normal[SW_2] = SW_2_NORMAL;

    for (i = 0; i < NUM_SWITCHES; i++)
    {
        sw_state[i] = sw_normal[i];
    }
}

// *******************************************************
// updateButtons: Function designed to be called regularly. It polls all
// buttons once and updates variables associated with the buttons if
// necessary.  It is efficient enough to be part of an ISR, e.g. from
// a SysTick interrupt.

void
updateSwitches (void)
{
    // Read the pins; true means HIGH, false means LOW
    sw_state[SW_1] = (GPIOPinRead (SW_1_PORT_BASE, SW_1_PIN) == SW_1_PIN);
    sw_state[SW_2] = (GPIOPinRead (SW_2_PORT_BASE, SW_2_PIN) == SW_2_PIN);
    // Iterate through the buttons, updating button variables as required
}

uint8_t
checkSwitch (uint8_t switchName)
{
    if (sw_state[switchName] == sw_normal[switchName]) {
        return ON;
    } else if (sw_state[switchName] != sw_normal[switchName]) {
        return OFF;
    }
}
