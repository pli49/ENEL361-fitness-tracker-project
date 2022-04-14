#ifndef DISPLAY_H_
#define DISPLAY_H_

/*******************************************************
 *
 * display.h
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
#include <stdint.h>
#include <string.h>

/*******************************************************
 *Clear all displaying on the OLED
*******************************************************/
void
Clear(void);

/*******************************************************
 *Initialize OLED display
*******************************************************/
void
initDisplay (void);

/*******************************************************
 *Update the display by given inputs
*******************************************************/
void
displayUpdate (char *str1, char *str2, int16_t num, uint8_t charLine);

/********************************************************
 *determines it steps or distance is displayed and the units of distance.
 ********************************************************/
void
display_unit (uint8_t toggle, uint8_t toggle_units, uint32_t steps, uint32_t distance);

#endif /* DISPLAY_H_ */
