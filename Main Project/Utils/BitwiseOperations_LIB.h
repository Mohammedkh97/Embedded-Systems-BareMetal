/*
 * Utils.h
 *
 * Created: 10/10/2023 4:36:43 AM
 *  Author: Mohammed Khalaf
 */ 


#ifndef UTILS_H_
#define UTILS_H_


#define   	GET_BIT(REGISTER, BIT)      	((REGISTER >> BIT) &1)
#define   	SET_BIT(REGISTER, BIT)      	(REGISTER = REGISTER|(1 << BIT))
#define   	CLEAR_BIT(REGISTER, BIT)    	(REGISTER = REGISTER & ~(1 << BIT))
#define   	TOGGLE_BIT(REGISTER, BIT)   	(REGISTER = REGISTER^(1 << BIT))
#define 	BIT_WRITE(REGISTER, BIT, VAL) 	(REGISTER = ((REGISTER & (~(1<<BIT)))|(VAL << BIT)))
#define 	BIT_IS_CLEAR(REGISTER, BIT) 	(!((REGISTER) & (BIT)))
#define 	REG_WRT(REG, NUM)   ( (REG)  =  (NUM)  ) /* Sets all the bits in the register as 'NUM'  */


#endif /* UTILS_H_ */
