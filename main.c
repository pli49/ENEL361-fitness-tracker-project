/*******************************************************************************
 *
 * main.c
 *
 * ENEL361 Fitness Monitor Project
 *
 *
 * Written by:
 *  - Pengcheng Liu  49791816
 *  - Scott Parkin   82581593
 *  - Thomas wang    65193909
 *
 *
 * Description:
 * This module contains the main entry point for the program.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_i2c.h"
#include "driverlib/pin_map.h" //Needed for pin configure
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "../OrbitOLED/OrbitOLEDInterface.h"
#include "../OrbitOLED/lib_OrbitOled/OrbitOled.h"
#include "../OrbitOLED/lib_OrbitOled/OrbitOledChar.h"
#include "utils/ustdlib.h"
#include "acc.h"
#include "i2c_driver.h"
#include "driverlib/adc.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/debug.h"
#include "circBufT.h"
#include "buttons4.h"
#include "switches.h"

#include "display.h"
#include "readAcc.h"
#include "clock.h"
#include "sysTick.h"




/**********************************************************
 * Constants
 **********************************************************/
#define BUF_SIZE 10


//*****************************************************************************
// Global variables
//*****************************************************************************


static circBuf_t g_inBuffer_x;
static circBuf_t g_inBuffer_y;
static circBuf_t g_inBuffer_z;                                                  // Buffer of size BUF_SIZE integers (sample values)

uint8_t toggle = 0;                                                             //toggles between steps and distance
uint8_t toggle_units = 0;                                                       // toggles between km and miles
uint32_t steps = 0;
uint32_t distance = 0;
uint32_t hold_count = 0;




//*****************************************************************************
// initial all that needed to be initialized
//*****************************************************************************
void
initialize(void)
{
    initClock ();
    initAccl ();
    initDisplay ();
    initButtons ();
    initSwitches ();
    initSysTick ();
    initCircBuf (&g_inBuffer_x, BUF_SIZE);
    initCircBuf (&g_inBuffer_y, BUF_SIZE);
    initCircBuf (&g_inBuffer_z, BUF_SIZE);
}



/********************************************************
main function
 ********************************************************/
int
main (void)
{
    vector3_t acceleration_raw;
    uint16_t units_raw_to_g = 256;                  //value needed to convert raw acc data to g
    uint32_t start_step_threshold = 1050;           //value found to work quite well with my tiva board.
    uint32_t end_step_threshold = 1001;             //step finished when drops acceleration drops below this value
    uint16_t buffer_position;

    // sum of acceleration circular buffers

    int32_t sum_x = 0;
    int32_t sum_y = 0;
    int32_t sum_z = 0;

    // mean of acceleration circular buffers

    int32_t mean_x = 0;
    int32_t mean_y = 0;
    int32_t mean_z = 0;

    uint16_t new_step = 1;                          //1 when not currently taking a step, 0 during step to stop multiple counts
    int32_t mag_acceleration_vector = 0;

    //initialize the system

    initialize();

    //draw the first line of OLED display

    OLEDStringDraw ("Fitness Tracker", 0, 0);

    while (1)
    {
        //get data from accolermeter and write into the circular buffers
        acceleration_raw = getAcclData();
        writeCircBuf (&g_inBuffer_x, acceleration_raw.x);
        writeCircBuf (&g_inBuffer_y, acceleration_raw.y);
        writeCircBuf (&g_inBuffer_z, acceleration_raw.z);



        sum_x = 0;
        sum_y = 0;
        sum_z = 0;


        // Calculate the sum of the buffer contents
        for (buffer_position = 0; buffer_position < BUF_SIZE; buffer_position++){
            sum_x = sum_x + readCircBuf (&g_inBuffer_x);
            sum_y = sum_y + readCircBuf (&g_inBuffer_y);
            sum_z = sum_z + readCircBuf (&g_inBuffer_z);
        }
        // Calculate the rounded mean of the buffer contents
        mean_x = ((2 * sum_x + BUF_SIZE) / 2 / BUF_SIZE);
        mean_y = ((2 * sum_y + BUF_SIZE) / 2 / BUF_SIZE);
        mean_z = ((2 * sum_z + BUF_SIZE) / 2 / BUF_SIZE);

        //calculate magnitude of acceleration vector
        mag_acceleration_vector = sqrt((mean_x * mean_x) + (mean_y * mean_y) + (mean_z * mean_z));

        //determine if start of new step, continuation of step or, no step.
        if (mag_acceleration_vector > ((start_step_threshold * units_raw_to_g)/1000)) {//(start_step_threshold * units_raw_to_g)/1000
            if (new_step == 1){
                steps++;
            }
            new_step = 0;
        }

       if (mag_acceleration_vector < ((end_step_threshold * units_raw_to_g)/1000)) {//(end_step_threshold * units_raw_to_g)/1000
            new_step = 1;
        }


       //display on the OLED of the results
       display_unit(toggle, toggle_units, steps, distance);

       //delay the while loop to slow it down
       SysCtlDelay (SysCtlClockGet () / 150);
    }
}
