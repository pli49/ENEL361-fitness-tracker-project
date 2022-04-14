#ifndef READACC_H_
#define READACC_H_

// *******************************************************
// ENEL361 Fitness Monitor Project
//
// * Written by:
// *  - Pengcheng Liu  49791816
// *  - Scott Parkin   82581593
// *  - Thomas wang    65193909
//Example code which reads acceleration in three dimensions
// readAcc.c
//
// Part of code from Ciaran Moore
//
// *******************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/*********************************************************
 *Define type vector3_t
 *********************************************************/
typedef struct{
    int16_t x;
    int16_t y;
    int16_t z;
} vector3_t;


/*********************************************************
 *Function to initialize accelerometer
 *********************************************************/
void
initAccl (void);


/********************************************************
 * Function to read accelerometer
 ********************************************************/
vector3_t
getAcclData (void);



#endif /* READACC_H_ */
