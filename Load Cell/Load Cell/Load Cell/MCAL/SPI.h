/*
 * SPI.h
 *
 * Created: 1/12/2024 1:03:11 AM
 *  Author: MohamMed Khalaf
 */ 


#ifndef SPI_H_
#define SPI_H_

/************************************************************************/
/*						SPI PINS CONFIGURATIONS                         */
/************************************************************************/

#define SPI_SS						PINB0
#define SPI_SCK						PINB1
#define SPI_MOSI					PINB2
#define SPI_MISO					PINB3

#define SPI_DEFAULT_DATA_VALUE		0x00
/*#define MASTER 0
#define SLAVE  1

#define SPI_MODE     MASTER*/


typedef enum
{
	MASTER,
	SLAVE
	
}SPI_Mode_t;

typedef enum
{
	Fosc_4,
	Fosc_16,
	Fosc_128,
	Fosc_2,
	Fosc_8,
	Fosc_32,
	Fosc_64
}SCK_Frequency_t;

void SPI_init(SPI_Mode_t mode , SCK_Frequency_t frequency);
u8 SPI_Send_Receive(u8 data);
void SPI_Send_No_Block(u8 data);
u8 SPI_Send_Receive_With_runtime_out(u8 data , u8* pData , u16 set_Time);

void SPI_initMaster(void); 

/*
 * Description :
 * Initialize the SPI device as Slave.
 */
void SPI_initSlave(void);

/*
 * Description :
 * Send the required data through SPI to the other SPI device.
 * In the same time data will be received from the other device.
 */
u8 SPI_sendReceiveByte(u8 data);

/*
 * Description :
 * Send the required string through SPI to the other SPI device.
 */
void SPI_sendString(const u8 *str);

/*
 * Description :
 * Receive the required string until the '#' symbol through SPI from the other SPI device.
 */
void SPI_receiveString(u8 *str);

#endif /* SPI_H_ */