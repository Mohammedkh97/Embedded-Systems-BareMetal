/*
 * Utils.h
 *
 * Created: 10/10/2023 4:36:43 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define   GET_BIT(REG, bit)				((REG >> bit) &1)
#define   SET_BIT(REG, bit)				(REG = REG|(1 << bit))
#define   CLEAR_BIT(REG, bit)			(REG = REG & ~(1 << bit))
#define   TOGGLE_BIT(REG, bit)			(REG = REG^(1 << bit))
/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#endif /* UTILS_H_ */