/*******************************************************************************
 *
 * clock.c
 * ENEL361 Fitness Monitor Project
 * Written by:
 *  - Pengcheng Liu  49791816
 *  - Scott Parkin   82581593
 *  - Thomas wang    65193909
 *
 * This file contains portions of code that written by P.J. Bones.
 * These portions are noted in the comments.
 *
 *The initialization function to set the system clock
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"

#include "clock.h"

/**
 * Originally Code by P.J. Bones
 * Initialization functions for the clock
 */
void
initClock (void)
{
    // Set the clock rate to 20 MHz
    SysCtlClockSet (SYSCTL_SYSDIV_10 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

}
