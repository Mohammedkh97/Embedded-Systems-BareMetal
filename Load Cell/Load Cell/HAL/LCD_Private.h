/*
 * LCD_Private.h
 *
 * Created: 10/26/2023 1:46:01 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

u8 string_len(u8* str);
void reverseString(u8* str);
void intoString(s32 num, u8 *str);
void floatToString(f32 num, u8 *buffer, u16 decimalPlaces);
void Dec_Bin(s32 num);
void customChar(u8* man , u8 address);
void appendChar(u8 *str, u8 c, u16 str_size);

void stringConcat(u8* str1, const u8* str2, u16 str1_size);

#endif /* LCD_PRIVATE_H_ */