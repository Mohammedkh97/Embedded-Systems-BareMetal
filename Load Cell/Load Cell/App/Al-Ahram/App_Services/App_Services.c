/*
 * App_Services.c
 *
 * Created: 05/09/2024 16:04:31
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "App_Services.h"

f32 get_AbsoluteValue(f32 value) 
{
	return (value < 0) ? -value : value;
}