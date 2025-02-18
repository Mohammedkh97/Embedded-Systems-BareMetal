
#include "stdTypes.h"
#include "MemoryMap.h"
#include "UART.h"
#include "Utils.h"
#include "UART_Services.h"
#include "UART_Config.h"


/* synch function */
void UART_TransmitString(u8*str , u8 terminator , UART_Channel_t uart)
{
	u8 i;
	for (i = 0 ; str[i] ; i++)
	{
		UART_Transmit(str[i] , uart);
	}
	UART_Transmit(terminator , uart);
}

void UART_ReceiveString(u8 *str, u16 max_length , UART_Channel_t uart) {
	u16 i = 0;
	u8 received_char;

	// Receive first character
	received_char = UART_ReceiveData(uart);

	// Continue receiving characters until Enter is received or buffer is full
	while (received_char != 0x0d && i < (max_length - 1)) { // '\r' is carriage return (Enter key)
		str[i++] = received_char;
		received_char = UART_ReceiveData(uart);
	}

	// Null-terminate the received string
	str[i] = '\0';
}

void UART_ReceiveString_DockLight(u8*str , UART_Channel_t uart)   // Using DockLight
{
	u8 i=0;
	str[i]=UART_ReceiveData(uart);
	while (str[i] != 0x0D && str[i + 1] != 0x0A)  // 0x0d0a Enter char
	{
		i++;
		str[i]=UART_ReceiveData(uart);
	}
	str[i]=0;

}

void UART_SendNumber(u32 num , UART_Channel_t uart)
{
	UART_Transmit((u8)num       , uart);
	UART_Transmit((u8)(num>>8)  , uart);
	UART_Transmit((u8)(num>>16) , uart);
	UART_Transmit((u8)(num>>24) , uart);
	
	/*u8*p=&num;
	UART_Transmit(p[0]);
	UART_Transmit(p[1]);
	UART_Transmit(p[2]);
	UART_Transmit(p[3]);
	*/
}


u32 UART_ReceiveNumber1(UART_Channel_t uart)
{
	u32 num=0;
	u8 b1=UART_ReceiveData(uart);
	u8 b2=UART_ReceiveData(uart);
	u8 b3=UART_ReceiveData(uart);
	u8 b4=UART_ReceiveData(uart);
	
	
	num=(u32)b1|(u32)b2<<8|(u32)b3<<16|(u32)b4<<24;
	return num;
}

/*
void UART_ReceiveNumber2(u32*pnum , UART_Channel_t uart)
{
u8*p=&num;
p[0]=UART_ReceiveData(uart);
p[1]=UART_ReceiveData(uart);
p[2]=UART_ReceiveData(uart);
p[3]=UART_ReceiveData(uart);


}*/


endian_t Endian_Check(void)
{
	u32 x=1;
	u8*p= (u8*)&x;
	if (*p==1)
	{
		return LITTLE;
	}
	else
	{
		return BIG;
	}
}

u32 endian_convert(u32 num)
{
	return  (num<<24)|(num>>24)|((num>>8)&(0x0000ff00))|((num<<8)&(0x00ff0000));
	
	/*
	u8 *p = &num;
	u8 temp;
	temp = p[0];
	p[0] = p[3];
	p[3] = temp;
	
	temp = p[1];
	p[1] = p[2];
	p[2] = temp;
	
	return num;
	*/
}
u16 endian_convert_16(u16 num)
{
	return  (num<<8)|(num>>8);
}


void diagCallOut(u8*data)
{
	
	
}

void UART_SendStringCheckSum(u8 *str, UART_Channel_t uart) {
	u8 len = 0;
	u16 sum = 0;

	// Calculate length of string
	for (len = 0; str[len]; len++);

	// Send length of string
	UART_Transmit(len, uart);

	// Send each character and calculate checksum
	for (len = 0; str[len]; len++) {
		UART_Transmit(str[len], uart);
		sum += str[len];
	}

	// Send low byte of checksum
	UART_Transmit((u8)sum, uart);

	// Send high byte of checksum
	UART_Transmit((u8)(sum >> 8), uart);
}

u8 UART_ReceiveStringCheckSum(u8 *str, UART_Channel_t uart) {
	u8 i, len;
	u16 calculated_sum = 0;
	u16 received_sum = 0;
	
	// The two bytes of received sum:
	u8 byte1 = 0, byte2 = 0;
	
	// For Example: Str = "mohamed"
	// len = 7     sum = 731
	
	len = UART_ReceiveData(uart); // Receive length of string

	// Receive characters and calculate checksum
	for (i = 0; i < len; i++) {
		str[i] = UART_ReceiveData(uart);
		calculated_sum += str[i];
	}
	str[i] = 0;

	// Receive low and high byte of received checksum
	byte1 = UART_ReceiveData(uart);
	byte2 = UART_ReceiveData(uart);
	received_sum = (u16)byte1 | ((u16)(byte2) << 8);      // 0000 0010 1101 1011

	// Compare received checksum with calculated checksum
	if (received_sum == calculated_sum) 
	{
		return 1; // Checksum matched
		} 
	else 
	{
		return 0; // Checksum mismatch
	}
}

static u8 *TX_Str;
static u8 *RX_Str;
static u8 flag=1;
//static u8 i=0;
static u8 tx_index = 0;

void Tx_Function_Asynchronous(UART_Channel_t uart) {
	if (TX_Str[tx_index] != 0) {
		UART_SendData_NO_BLOCK(TX_Str[tx_index], uart);
		tx_index++;
		} else {
		tx_index = 0;
	}
}

void UART_SendStringAsynchronous(u8 *str, UART_Channel_t uart) { 
	UART_TX_SetCallback(Tx_Function_Asynchronous,uart); // Set callback function
	UART_TX_Interrupt_Enable(uart); // Enable TX interrupt
	UART_SendData_NO_BLOCK(str[0], uart); // Start transmission
	TX_Str = str; // Save string pointer
}

void UART_SendStringAsynchronous_NO_BLOCK(u8 *str, UART_Channel_t uart) {  // It considered Asynchronous Function due to not complete the task immediately once you pass the string
	if (flag == 1) {
		if (str[tx_index] != 0) {
			UART_SendData_NO_BLOCK(str[tx_index], uart);
			tx_index++;
		}
		flag = 0;
	}
}
/*
void UART_Basic_Communication_Module_Init(void)
{
	UART_TX_SetCallback(Tx_Function_Asynchronous);
	UART_TX_Interrupt_Enable();
}

void UART_Basic_Communication_Module_SendString(u8* str)
{
	TX_Str = str;
}

void UART_Basic_Communication_Module_Runnable(void)
{
	static u8 i = 0;
	if (flag == 1)
	{
		if (TX_Str[i] !=0)
		{
			UART_SendData_NO_BLOCK(TX_Str[i]);
			i++;
		}
		flag = 0;
	}
}

void Rx_Function_Asynchronous()
{
	static u8 i = 0;
	
	RX_Str[i] = UART_ReceiveData_NO_BLOCK();
	i++;
	if (i>20)
	{
		i = 0;
	}
	
}

void UART_Receive_Asynchronous(u8* str)
{
	UART_RX_Interrupt_Enable();
	UART_RX_SetCallback(Rx_Function_Asynchronous);
	RX_Str = str;
}
*/
/*

static u8*TX_Str[10];
static u8 flag=1;
static u8 i=0;
void Tx_Function_Asynchronous(void)
{
static u8 j=1;
static u8 i=0;
if (TX_Str[i][j])
{
UART_SendData_NO_BLOCK(TX_Str[i][j]);
j++;
}
else
{
j=1;
i++;
}
}


void UART_SendStringAshync(u8*str)
{
static u8 i=0;
UART_TX_SetCallback(Tx_Function_Asynchronous);
UART_TX_Interrupt_Enable();
UART_SendData_NO_BLOCK(str[0]);
TX_Str[i]=str;

i++;
}
*/



/*
void func_tx2(void)
{
flag=1;
}

void UART_SendStringInit(void)
{
UART_TX_SetCallBack(func_tx2);
UART_TX_InterruptEnable();
}

void UART_SendStringRunnable(void)
{
static u8 j=0;
static u8 i=0;
if (flag==1)
{
if (TX_Str[i][j])
{
UART_SendNoBlock(TX_Str[i][j]);
j++;
}
else
{
j=0;
i++;
}
flag=0;
}

}

void UART_SendStringSetter(u8*str)
{
TX_Str[i]=str;
i++;
}

u8* RXStr;
u8 changeflag;
static void func_Rx(void)
{
static u8 i=0;
if (changeflag==1)
{
i=0;
changeflag=0;
}
RXStr[i]=UART_ReceiveNoBlock();
i++;
}
void UART_ReceiveStringAshync(u8*str)
{
UART_RX_SetCallBack(func_Rx);

UART_RX_InterruptEnable();
if (str!=RXStr)
{
changeflag=1;
}
RXStr=str;
}


u8 RX_Buffer1[8];
u8 RX_Buffer2[8];
static u8 Bufferflag=0;
u8 readyflag=0;
static void func_Rx2(void)
{
static u8 i=0;

if (Bufferflag==0)
{
RX_Buffer1[i]=UART_ReceiveNoBlock();
}
else
{
RX_Buffer2[i]=UART_ReceiveNoBlock();
}
i++;
if (i==8)
{
i=0;
readyflag=1;
Bufferflag^=1;
}

}

void UART_BufferInit(void)
{
UART_RX_SetCallBack(func_Rx2);

UART_RX_InterruptEnable();
}

u8 UART_BufferGetter(u8*str)
{
u8 i;
if (readyflag==0)
{
return 0;
}
for (i=0;i<8;i++)
{
if (Bufferflag==0)
{
str[i]=RX_Buffer2[i];
}
else
{
str[i]=RX_Buffer1[i];
}
}
readyflag=0;
return 1;
}

*/

u16 UART_SendFrame_SW(u8 data)
{
	u16 Frame=0;
	u8 Parityflag = 0, stop_bits = Stop_Bits;
	Frame = data << 1; // Start bit
	// Parity Check Bit:
	if (countSetBits(data) == EVEN && (GET_BIT(UCSR0C , UPM00) == 0 && GET_BIT(UCSR0C , UPM01) == 1))  // the Second part can be deleted as you can set config file .h and .c
	{
		// Frame = 00000101 0
		Frame = Frame | (EVEN << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else if (countSetBits(data) == ODD && (GET_BIT(UCSR0C , UPM00) == 1 && GET_BIT(UCSR0C , UPM01) == 1)) // the Second part can be deleted as you can set config file .h and .c
	{
		Frame = Frame | (ODD << (Data_Length + Start_Bit)) ;
		Parityflag = 1;
	}
	else
	{
		Parityflag = 0;
		Frame = Frame;
	}
	// Stop Bit:
	if (stop_bits == 2 && (GET_BIT(UCSR0C , USBS0)))
	{
		if (Parityflag == 1)
		{
			Frame = Frame | (3 << (1 + Data_Length + Start_Bit)) ;
		}
		else if (Parityflag == 0)
		{
			Frame = Frame | (3 << (0 + Data_Length + Start_Bit)) ;
		}
		
	}
	else if (stop_bits == 1 && (!GET_BIT(UCSR0C , USBS0)))  // the Second part can be deleted as you can set config file .h and .c
	{
		if (Parityflag == 1)
		{
			Frame = Frame | (1 << (1 + Data_Length + Start_Bit)) ;
		}
		else if (Parityflag == 0)
		{
			Frame = Frame | (1 << (0 + Data_Length + Start_Bit)) ;
		}
	}
	return Frame;
}


// Function to count the number of set bits  (ONES)
u8 countSetBits(u16 num)
{
	u8 count = 0;
	while (num) {
		count += num & 1;  // Add the last bit to the count if it is 1
		num >>= 1;         // Right shift the number to remove the processed bit
	}
	
	if (count % 2 == 0)
	{
		return EvenParity;
	}
	else
	return OddParity;
}

Parity_t UART_CheckParity(u8 data)
{
	if (GET_BIT(UCSR0C , UPM00) == 1 && GET_BIT(UCSR0C , UPM01) == 1)
	{
		return ODD;
	}
	else if (GET_BIT(UCSR0C , UPM00) == 0 && GET_BIT(UCSR0C , UPM01) == 1)
	{
		return EVEN;
	}
}
