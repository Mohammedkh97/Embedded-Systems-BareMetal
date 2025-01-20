/*
 * Scale_Configurations.h
 *
 * Created: 8/7/2024 10:37:18 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef SCALE_CONFIGURATIONS_H_
#define SCALE_CONFIGURATIONS_H_

/************************************************************************/
/*						CALIBRATION FACTORS                             */
/************************************************************************/

#define KILOGRAM					1000.0
#define TWO_KILOGRAM				2000.0
#define TWO_KILOGRAM_LAPTOP         2050.0
#define TWEENTY_KILOGRAM			20000.0


#define CALIBRATION_FACTOR			KILOGRAM

/************************************************************************/
/*							TYPES OF SCALES                             */
/*						 Zero Calibration Mode							*/
/************************************************************************/

// this numbers are based on my calculations !!

#define LOAD_CELL_NO_1						25.27
#define RETURN_LOAD_CELL					30.0
#define QUANTITY_LOAD_CELL					6.2		// 5.44
#define NEW_LOAD_CELL						4.6

#define NONE_ZERO_CALIBRATION				0

#define SCALE_TYPE					QUANTITY_LOAD_CELL


/***********************************************************************************************************************/

#define ZERO_CALIBRATION_MODE				1
#define MANUAL_CALIBRATION_MODE				2

#define CALIBTRAION_MODE			ZERO_CALIBRATION_MODE



#endif /* SCALE_CONFIGURATIONS_H_ */
