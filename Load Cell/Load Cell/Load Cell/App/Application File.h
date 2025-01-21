/*
 * Application_File.h
 *
 * Created: 05/07/2024 23:21:38
 *  Author: Mohammed Khalaf
 */ 


#ifndef APPLICATION FILE_H_
#define APPLICATION FILE_H_

#include "stdTypes.h"

void setup(void);
void systemRunnable();
u16 normalCountSpecies(f32 currentWeight);
void update_normalCounts(f32 currentWeight);
u16 detectStrangeSpecies(f32 currentWeight);


#endif /* APPLICATION FILE_H_ */