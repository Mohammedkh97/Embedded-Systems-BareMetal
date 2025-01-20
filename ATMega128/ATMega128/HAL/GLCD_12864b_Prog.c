//ST7920 LCD ??
#include "stdTypes.h"
#include "Utils.h"
#include "GLCD_12864b_Interface.h"

// GLCD code
void GLCD_init(void)
{
	GLCD_DATA_DDR_OUTPUT();

	_delay_ms(50);
	GLCD_write_command(0x33); //_GLCD_8BIT_MODE_BASSIC_INSTRUCTION_COMMAND1
	_delay_ms(1);
	GLCD_write_command(0x32);  //_GLCD_8BIT_MODE_BASSIC_INSTRUCTION_COMMAND2
	_delay_ms(1);
	#if GLCD_INTERFACE == MODE_4BIT
	GLCD_write_command(0x28); //_GLCD_4BIT_MODE_BASIC_INSTRUCTION_COMMAND1
	_delay_ms(1);
	GLCD_write_command(0x28); //_GLCD_4BIT_MODE_BASIC_INSTRUCTION_COMMAND2
	_delay_ms(1);
	#endif
	GLCD_write_command(0x08);  //_GLCD_DISPLAY_OFF_CURSOR_OFF???
	_delay_ms(1);             //??100uS?????
	GLCD_write_command(0x10);  //_GLCD_CURSOR_MOVE_SHIFT_LEFT????
	_delay_ms(1);             //??100uS?????
	GLCD_write_command(0x0C);  //_GLCD_DISPLAY_ON_CURSOR_OFF_BLINKING_OFF???
	_delay_ms(1);             //??100uS?????
	GLCD_write_command(0x01);  //_GLCD_CLEAR Display Clear
	_delay_ms(10);            //??10mS?????
	GLCD_write_command(0x06);  //_GLCD_ENTRY_MODE_INC_SHIFT_OFF???????1???
	_delay_ms(10);            //??10mS?????
}

//???
void GLCD_write_command(u8 command)
{
	#if GLCD_INTERFACE == MODE_SERIAL
	CLEAR_BIT(GLCD_SCLK_PORT, GLCD_SCLK_PIN);
	GLCD2_spi_write_byte(0xf8);
	asm("nop");
	GLCD2_spi_write_byte_standard(command);
	#else
	GLCD_CMD_MODE();   /*RS=0*/
	GLCD_write_byte(command);
	_delay_ms(1);
	#endif
}

//???
void GLCD_write_data(u8 data)
{
	#if GLCD_INTERFACE == MODE_SERIAL
	CLEAR_BIT(GLCD_SCLK_PORT, GLCD_SCLK_PIN);
	GLCD2_spi_write_byte(0xfa);
	asm("nop");
	GLCD2_spi_write_byte_standard(data);
	#else
	GLCD_DATA_MODE();    //RS=1
	GLCD_write_byte(data);
	#endif
}

//?????????????
void GLCD_write_byte(u8 data)
{
	#if GLCD_INTERFACE == MODE_4BIT
	GLCD_write_half_byte(data);
	data <<= 4;
	GLCD_write_half_byte(data);
	#else
	GLCD_DATA_PORT = data;
	GLCD_RW_LOW();
	GLCD_EN_HIGH();     //EN???????????????LCD
	_delay_us(10);
	GLCD_EN_LOW();      //EN???????????????LCD
	_delay_us(10);
	GLCD_RW_HIGH();
	#endif
}

//4???????????4??
void GLCD_write_half_byte(u8 half_byte)
{
	if (half_byte & 0x80)
	SET_BIT(GLCD_DATA_PORT_D7, GLCD_DATA_PIN_D7);
	else
	CLEAR_BIT(GLCD_DATA_PORT_D7, GLCD_DATA_PIN_D7);
	
	if (half_byte & 0x40)
	SET_BIT(GLCD_DATA_PORT_D6, GLCD_DATA_PIN_D6);
	else
	CLEAR_BIT(GLCD_DATA_PORT_D6, GLCD_DATA_PIN_D6);
	
	if (half_byte & 0x20)
	SET_BIT(GLCD_DATA_PORT_D5, GLCD_DATA_PIN_D5);
	else
	CLEAR_BIT(GLCD_DATA_PORT_D5, GLCD_DATA_PIN_D5);
	
	if (half_byte & 0x10)
	SET_BIT(GLCD_DATA_PORT_D4, GLCD_DATA_PIN_D4);
	else
	CLEAR_BIT(GLCD_DATA_PORT_D4, GLCD_DATA_PIN_D4);
	
	GLCD_RW_LOW();
	GLCD_EN_HIGH();         //EN???????????????LCD
	_delay_us(10);
	GLCD_EN_LOW();          //EN???????????????LCD
	_delay_us(10);
	GLCD_RW_HIGH();
}

//??????????
void GLCD2_spi_write_byte(u8 data)
{
	u8 i;
	for(i=0; i<8; i++)
	{
		if (data & 0x80)
		SET_BIT(GLCD_SID_PORT, GLCD_SID_PIN);
		else
		CLEAR_BIT(GLCD_SID_PORT, GLCD_SID_PIN);

		asm("nop");
		asm("nop");
		CLEAR_BIT(GLCD_SCLK_PORT, GLCD_SCLK_PIN);
		asm("nop");
		SET_BIT(GLCD_SCLK_PORT, GLCD_SCLK_PIN);
		data <<= 1;
	}
}

//??????????????????
void GLCD2_spi_write_byte_standard(u8 data)
{
	GLCD2_spi_write_byte(data & 0xf0);
	GLCD2_spi_write_byte((data << 4) & 0xf0);
}

//????????
u8 GLCD_read_data(void)
{
	u8 data;

	GLCD_DATA_MODE();
	data = GLCD_read_byte();

	#if GLCD_INTERFACE == MODE_4BIT
	data = (data & 0xf0) | ((GLCD_read_byte() >> 4) & 0x0f);
	#endif
	return data;
}

//????????
u8 GLCD_read_status(void)
{
	u8 data;
	GLCD_CMD_MODE();
	data = GLCD_read_byte();
	#if GLCD_INTERFACE == MODE_4BIT
	data = (data & 0xf0) | ((GLCD_read_byte() >> 4) & 0x0f);
	#endif
	return data;
}

//??????????????4bit???????4?????
u8 GLCD_read_byte(void)
{
	u8 data;
	GLCD_DATA_DDR_INPUT();
	GLCD_RW_HIGH();
	
	GLCD_EN_LOW();         //EN???????ST7920??????
	_delay_us(10);
	GLCD_EN_HIGH();
	_delay_us(10);

	data = GLCD_DATA_PIN;
	GLCD_EN_LOW();
	GLCD_DATA_DDR_OUTPUT();
	return data;
}

//?????????
//???????0x80
//???????0x80+0x10 (0x90)
//???????0x80+0x08 (0x88)
//???????0x80+0x10+0x08 (0x98)
void GLCD_set_text_address(u16 rowCol)
{
	u8 start = 0x80;
	u8 row = (rowCol >> 8) & 0xff;
	u8 col = rowCol & 0xff;

	if (row == 1) {
		start = 0x90;
	}
	if (row == 2) {
		start = 0x88;
	}
	if (row == 3) {
		start = 0x98;
	}
	GLCD_write_command(start + col);
}

//???????????????XY??????????X?????Y
//row (HIGH_BYTE(rowCol)): ???0-3
//col (LOW_BYTE(rowCol)): ???0-7
u16 GLCD_rowCol_to_inter_Xy(u16 rowCol)
{
	u8 row = (rowCol >> 8) & 0x03;
	u8 col = rowCol & 0x07;
	u8 x = col + 8 * (u8)(row / 2);
	u8 y = (row * 16) & 0x1f;
	return (x << 8) | y;
}

//?????????
//x: 0-127 (??x???16????)
//y:0-63
void GLCD_set_graphic_address(u8 x, u8 y)
{
	u8 xWord, downPage, yInter;

	x &= 0x7f;
	y &= 0x3f;
	xWord = x / 16;           //??X????????16?
	downPage = y / 32;        //0:??? 1:???
	yInter = y & 0x1f;        //??Y??
	
	GLCD_write_command(0x80 + yInter); //???Y??
	GLCD_write_command(0x80 + xWord + 8 * downPage);
}

//??????
void GLCD_clear(void)
{
	u8 x, y;
	GLCD_write_command(0x08);  //??????????????
	_delay_us(100);
	GLCD_write_command(0x01);  //?DDRAM

	//?GDRAM,12864??????GDRAM??????
	//?????????GDRAM??????GDRAM??????????
	GLCD_startGraphic();
	for (y = 0; y < 32; y++)
	{
		GLCD_write_command(0x80 + y); //y
		GLCD_write_command(0x80 + 0); //x
		for (x = 0; x < 16; x++)
		{
			GLCD_write_data(0x00);
			GLCD_write_data(0x00);
		}
	}
	GLCD_endGraphic();

	GLCD_write_command(0x0C);  //???
	_delay_ms(10);
}

//???????????
void GLCD_startGraphic(void)
{
	#if GLCD_INTERFACE == MODE_4BIT
	GLCD_write_command(0x24);          //?????
	GLCD_write_command(0x26);          //?????
	GLCD_write_command(0x24);          //?????
	GLCD_write_command(0x26);          //?????
	#else
	GLCD_write_command(0x36);          //?????
	GLCD_write_command(0x30);          //?????
	#endif
}

//???????????
void GLCD_endGraphic(void)
{
	#if GLCD_INTERFACE == MODE_4BIT
	GLCD_write_command(0x20);          //?????
	GLCD_write_command(0x22);          //?????
	GLCD_write_command(0x20);          //?????
	GLCD_write_command(0x22);          //?????
	#else
	GLCD_write_command(0x36);          //?????
	GLCD_write_command(0x30);          //?????
	#endif
}

//?????????16X16???????????
//row (HIGH_BYTE(rowCol)): ???0-3
//col (LOW_BYTE(rowCol)): ???0-7
//charNum: ?????????????????
//ST7920???????????????????????????????????
//?????????????????????????0xff????????
void GLCD_Inverse_16X16(u16 rowCol, u8 charNum, u8 reverse)
{
	u8 i, ch;
	u16 xy = GLCD_rowCol_to_inter_Xy(rowCol);
	u8 x = (xy >> 8) & 0xff;
	u8 y = xy & 0x3f;

	GLCD_startGraphic();
	for (i = 0; i < 16; i++) //??????GDRAM????0xff????????
	{
		GLCD_write_command(0x80 + y + i);   //??????y
		GLCD_write_command(0x80 + x);       //x
		for (ch = 0; ch < charNum; ch++)
		{
			GLCD_write_data(reverse ? 0xff : 0x00);
			GLCD_write_data(reverse ? 0xff : 0x00);
		}
	}
	GLCD_endGraphic();
}

//???????12864????4????8??????16???
//col: ???0-15
//row: ???0-3
//???????0x80??ASCII?????????????????
void GLCD_write_char(u16 rowCol, u16 code)
{
	u8 high = (code >> 8) & 0xff;
	u8 low = code & 0xff;
	GLCD_set_text_address(rowCol);
	if (code > 0x80)
	{
		GLCD_write_data(high);
	}
	GLCD_write_data(low);
}

void GLCD_write_number(u16 rowCol, s16 CopyNumber)
{
	s8 Local_Counter = 0;
	u8 Local_Arr[10] = {0};

	GLCD_set_text_address(rowCol);

	if (CopyNumber < 0)
	{
		CopyNumber = CopyNumber * -1;
		GLCD_write_data('-');
	}

	do
	{
		Local_Arr[Local_Counter] = CopyNumber % 10;
		CopyNumber = CopyNumber / 10;
		Local_Counter++;
	} while (CopyNumber != 0);

	while (Local_Counter > 0)
	{
		GLCD_write_data(Local_Arr[--Local_Counter] + 48); /* 48 for ascii code */
	}
}

//????????????????????8????16????
//rowCol: ?8???(0-3)??8???(0-15)
void GLCD_write_string(u16 rowCol, const char *p)
{
	GLCD_set_text_address(rowCol);
	while (*p != 0)
	{
		GLCD_write_data(*p);
		p++;
	}
}

//????????ST7920?????????????????RAM???
#if GLCD_INTERFACE != MODE_SERIAL
//???X/Y???????
void GLCD_write_dot(u8 x, u8 y)
{
	u8 xBit, high, low;

	xBit = x & 0x0f;
	GLCD_startGraphic();
	GLCD_set_graphic_address(x, y);
	GLCD_read_data();    //?????????????????????????

	high = GLCD_read_data();
	low = GLCD_read_data();

	//??
	GLCD_set_graphic_address(x, y);
	if (xBit < 8)   //?8?
	{
		GLCD_write_data(high | (0x01 << (7 - xBit)));
		GLCD_write_data(low);
	}
	else
	{
		GLCD_write_data(high);
		GLCD_write_data(low | (0x01 << (15 - xBit)));
	}
	GLCD_endGraphic();
}
#endif
