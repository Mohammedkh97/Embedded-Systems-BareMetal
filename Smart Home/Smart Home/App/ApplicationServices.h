/*
 * ApplicationServices.h
 *
 * Created: 1/23/2024 2:00:22 AM
 *  Author: Mohammed Khalaf
 */ 

/*******************************************************************************************/                                                                   
/********************************* Header File Guard ***************************************/
#ifndef APPLICATIONSERVICES_H_
#define APPLICATIONSERVICES_H_

/************************************************************************/
/************************************* Inclusions *********************************/

/*Files Service headers  */
#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"


typedef enum
{
	NOT_MATCHED,
	MATCHED
}status_t;

u8 string_Number_Split(u8 *requested_Function_Name , u8 *splittedString);
status_t stringCompare(u8 *requested_Function_Name , u8 *given_Function_Name);
void LCD_Draw_Character(u8* shape);
#endif /* APPLICATIONSERVICES_H_ */