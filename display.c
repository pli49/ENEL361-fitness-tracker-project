/*******************************************************
 *
 * display.c
 *
 * Module to display on the OLED and to decide what to print on the OLED
 *
 * Written by:
 *  - Pengcheng Liu  49791816
 *  - Scott Parkin   82581593
 *  - Thomas wang    65193909
 * Partly from C.P. Moore
 * Last modified:  24/02/2020
 *
*******************************************************/

#include <stdlib.h>
#include "clock.h"
#include "display.h"
#include "utils/ustdlib.h"
#include "OrbitOLED/OrbitOLEDInterface.h"




/*******************************************************
 *Clear all displaying on the OLED
*******************************************************/
void Clear(void)
{
    OLEDStringDraw("                ", 0, 0);
    OLEDStringDraw("                ", 0, 1);
    OLEDStringDraw("                ", 0, 2);
    OLEDStringDraw("                ", 0, 3);
}

/*******************************************************
 *Update the display by given inputs
*******************************************************/
void
displayUpdate (char *str1, char *str2, int16_t num, uint8_t charLine)
{
    char text_buffer[17];           //Display fits 16 characters wide.

    // "Undraw" the previous contents of the line to be updated.
    OLEDStringDraw ("                ", 0, charLine);
    // Form a new string for the line.  The maximum width specified for the
    //  number field ensures it is displayed right justified.
    usnprintf(text_buffer, sizeof(text_buffer), "%s %s %4d", str1, str2, num);
    // Update line on display.
    OLEDStringDraw (text_buffer, 0, charLine);
}


/********************************************************
 *determines it steps or distance is displayed and the units of distance.
 ********************************************************/
void
display_unit (uint8_t toggle, uint8_t toggle_units, uint32_t steps, uint32_t distance)
{
    if (toggle == 0) {
        displayUpdate ("Steps", ":", steps, 2);
    } else if (toggle == 1) {
        if (toggle_units == 0){
            distance = 0.9 * steps;
            displayUpdate ("Dist. Km", ":", distance, 2);
        }else{
            distance = 0.9 * steps * 0.62;
            displayUpdate ("Dist. mi", ":", distance, 2);
        }
    }
    OrbitOledUpdate();

}

/*******************************************************
 *Initialize OLED display
*******************************************************/
void
initDisplay (void)
{
    // Initialize the Orbit OLED display
    OLEDInitialise ();
    Clear();
}
