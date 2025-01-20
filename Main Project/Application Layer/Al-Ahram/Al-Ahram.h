/*
 * Al-Ahram.h
 *
 * Created: 05/07/2024 23:21:38
 *  Author: Mohammed Khalaf
 */ 


#ifndef AL_AHRAM_H_
#define AL_AHRAM_H_

#include "stdTypes.h"

#define  	HOLD_BUTTON  			PINB11
#define  	STABLE_LED				PINC14
#define		BUTTON_GENERAL_RESULT	PINB0
#define 	BUTTON_PAGE_1			PINB1
#define 	BUTTON_PAGE_2			PINB10


void Al_Ahram_setup(void);
void Al_Ahram_Runnable(void);
u16 normalCountSpecies(f32 currentWeight);
//void update_normalCounts(f32 currentWeight);
//u16 detectStrangeSpecies(f32 currentWeight);
u16 detectSpecies(f32 currentWeight , u16 *pStrangeCount);
//u16 detectSpecies(f32 *pAccumulatedWeight, f32 currentWeight, u16 *pStrangeCount, u16 *pAccumulatedConuts);
//f32 getStableWeight(f32 currentWeight , u16 *pStableCounts , f32 *pStableWeights);
f32 getStableWeight(f32 currentWeight , u16 *pAccumulatedCounts , f32 *pAccumulatedWeight /*, u16 *pTotalStaticCounts*/, f32 avgWeight);
void transmitDataToESP32(u16 Normal , u16 Strange , u16 TotalCounts , u8* Buffer1, u8* Buffer2, u8* Buffer3);
void sendDataToESP32(u16 Normal, u16 Strange, u16 TotalCounts , u16 Static_Total, u16 avgSpecies);
void GLCD_Display_Result(f32 weight , u16 staticCounts, u16 normal_Counts , u16 strange_Counts , u16 total_Counts , u16 AccumulatedWeight);
void 	 DisplayPage1();
void	 DisplayPage2();
/* ----------------------------------------------------- Private App function prototypes -----------------------------------------------*/
void Al_Ahram_SystemClock_Config(void);
static void Al_Ahram_MX_TIM1_Init(void);
void Al_Ahram_Error_Handler(void);
#endif /* AL_AHRAM_H_ */
