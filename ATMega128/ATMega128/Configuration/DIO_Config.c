/*
 * DIO_Config.c
 *
 * Created: 5/20/2023 6:51:03 AM
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "DIO_interface.h"


const DIO_PinStatus_t DIO_PinsStatusArr[TOTAL_PINS]={
	
	OUTPUT,      /* Port A Pin 0	*/
	OUTPUT,      /* Port A Pin 1	*/
	OUTPUT,      /* Port A Pin 2	*/
	OUTPUT,      /* Port A Pin 3	*/
	OUTPUT,      /* Port A Pin 4	*/
	OUTPUT,      /* Port A Pin 5	*/
	OUTPUT,      /* Port A Pin 6	*/
	OUTPUT,      /* Port A Pin 7	*/
	
	OUTPUT,      /* Port B Pin 0		SS */
	OUTPUT,      /* Port B Pin 1		SCK*/
	OUTPUT,		 /* Port B Pin 2		MOSI*/
	INFREE,		 /* Port B Pin 3		MISO*/
	OUTPUT,		 /* Port B Pin 4		OC0 */
	OUTPUT,		 /* Port B Pin 5		OC1A*/
	INFREE,		 /* Port B Pin 6		OC1B*/
	OUTPUT,		 /* Port B Pin 7		OC2 / OC1C*/
	
	OUTPUT,		 /* Port C Pin 0 */
	OUTPUT,		 /* Port C Pin 1 */
	OUTPUT,		 /* Port C Pin 2 */
	OUTPUT,		 /* Port C Pin 3 */
	OUTPUT,		 /* Port C Pin 4 */
	OUTPUT,		 /* Port C Pin 5 */
	OUTPUT,		 /* Port C Pin 6 */
	OUTPUT,		 /* Port C Pin 7 */
	
	OUTPUT,		 /* Port D Pin 0	INT0	*/
	OUTPUT,		 /* Port D Pin 1	INT1	*/
    OUTPUT,      /* Port D Pin 2 	INT2	*/
	OUTPUT,      /* Port D Pin 3 	INT3	*/
	OUTPUT,		 /* Port D Pin 4	ICP		*/
	OUTPUT,		 /* Port D Pin 5	XCK		*/
	OUTPUT,		 /* Port D Pin 6    T1		*/
	OUTPUT,		 /* Port D Pin 7	T2		*/
	
	OUTPUT,		 /* Port E Pin 0 */
	OUTPUT,		 /* Port E Pin 1 */
	INPULL,      /* Port E Pin 2 */
	INPULL,      /* Port E Pin 3  */
	OUTPUT,		 /* Port E Pin 4 */
	OUTPUT,		 /* Port E Pin 5 */
	INFREE,		 /* Port E Pin 6  */
	OUTPUT,		 /* Port E Pin 7 */
	
	INFREE,		 /* Port F Pin 0 		ADC0*/
	INFREE,		 /* Port F Pin 1 		ADC1*/
	INFREE,      /* Port F Pin 2 		ADC2*/
	INPULL,      /* Port F Pin 3 		ADC3*/
	OUTPUT,		 /* Port F Pin 4 		ADC4*/
	OUTPUT,		 /* Port F Pin 5 		ADC5*/
	INFREE,		 /* Port F Pin 6 		ADC6*/
	OUTPUT,		 /* Port F Pin 7 		ADC7*/

	OUTPUT,		 /* Port G Pin 0 */
	OUTPUT,		 /* Port G Pin 1 */
	
 };	 