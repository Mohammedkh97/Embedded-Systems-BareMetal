/*
 * DIO_Config.c
 *
 * Created: 10/20/2023 6:51:03 AM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "DIO_interface.h"


const DIO_PinStatus_t DIO_PinsStatusArr[TOTAL_PINS]={
	INFREE,      /* Port A Pin 0 ADC0*/
	OUTPUT,      /* Port A Pin 1 ADC1*/
	OUTPUT,      /* Port A Pin 2 */
	OUTPUT,      /* Port A Pin 3 */
	OUTPUT,      /* Port A Pin 4 */
	OUTPUT,      /* Port A Pin 5 */
	OUTPUT,      /* Port A Pin 6 */
	INFREE,      /* Port A Pin 7 ADC7*/
	
	INPULL,      /* Port B Pin 0   / */
	OUTPUT,      /* Port B Pin 1   /*/
	OUTPUT,		 /* Port B Pin 2 / INT2*/
	OUTPUT,		 /* Port B Pin 3   /OC0*/
	OUTPUT,		 /* Port B Pin 4 /ss*/
	OUTPUT,		 /* Port B Pin 5 //MOSI*/
	OUTPUT,		 /* Port B Pin 6 /MISO*/
	OUTPUT,		 /* Port B Pin 7 Clk*/
	
	INPULL,		 /* Port C Pin 0 */
	INPULL,		 /* Port C Pin 1 */
	INPULL,		 /* Port C Pin 2 */
	INPULL,		 /* Port C Pin 3 */
	
	OUTPUT,		 /* Port C Pin 4 */
	OUTPUT,		 /* Port C Pin 5 */
	OUTPUT,		 /* Port C Pin 6 */
	OUTPUT,		 /* Port C Pin 7 */
	
	INFREE,		 /* Port D Pin 0 RX*/
	OUTPUT,		 /* Port D Pin 1 TX*/
    INPULL,      /* Port D Pin 2 /INT0*/
	INPULL,      /* Port D Pin 3 / INT1 */
	OUTPUT,		 /* Port D Pin 4  OC1B*/
	OUTPUT,		 /* Port D Pin 5 OC1A*/
	INFREE,		 /* Port D Pin 6 /   ICP*/
	OUTPUT		 /* Port D Pin 7 */
 };	 