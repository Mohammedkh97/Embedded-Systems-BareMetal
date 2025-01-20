/***************************************************************/
/* Author		: Ahmed Hssein                                 */
/* Date         : 1 Jan. 2025    							   */
/* Version		: V01										   */
/***************************************************************/

#ifndef TFT_PRIVATE_H
#define TFT_PRIVATE_H

extern const u8 font8x16[][16];
extern const u16 font16x32[][64];


/* Mode color option: 1. RGB
                      2. BGR      */
#define RGB         0
#define BGR         1

/* Font size option: 1. font8*16  =  FONT8_16
                     2. font16*32 =  FONT16_32*/
#define FONT8_16    0
#define FONT16_32   1

#endif
