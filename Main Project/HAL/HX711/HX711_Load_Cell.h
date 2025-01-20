/*
 * HX711_Load_Cell.h
 *
 * Created: 05/06/2024 10:38:07 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef HX711_LOAD_CELL_H_
#define HX711_LOAD_CELL_H_


u32 HX711_Read(void);
void HX711_Calibrate(void);
f32 HX711_WeightRead();

#endif /* HX711_LOAD_CELL.C_H_ */