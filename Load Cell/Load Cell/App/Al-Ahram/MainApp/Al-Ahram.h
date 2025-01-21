/*
 * Al-Ahram.h
 *
 * Created: 05/07/2024 23:21:38
 *  Author: Mohammed Khalaf
 */ 


#ifndef AL_AHRAM_H_
#define AL_AHRAM_H_

#include "stdTypes.h"

#define  Toggle_LED  PINA0



void setup(void);
void systemRunnable();
u16 normalCountSpecies(f32 currentWeight);
//void update_normalCounts(f32 currentWeight);
//u16 detectStrangeSpecies(f32 currentWeight);
u16 detectSpecies(f32 currentWeight , u16 *pStrangeCount);
f32 getStableWeight(f32 currentWeight , u16 *pStaticCounts);
void transmitDataToESP32(u16 Normal , u16 Strange , u16 TotalCounts , u8* Buffer1, u8* Buffer2, u8* Buffer3);
void sendDataToESP32(u16 Normal , u16 Strange , u16 TotalCounts);
void GLCD_printApp(f32 weight , u16 normal_Counts , u16 strange_Counts , u16 total_Counts);
#endif /* AL_AHRAM_H_ */