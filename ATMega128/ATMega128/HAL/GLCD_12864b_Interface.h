

#ifndef __GLCD_12864B_INTERFACE_H_
#define __GLCD_12864B_INTERFACE_H_


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#define MODE_8BIT       8  // 8-bit mode
#define MODE_4BIT       4  // 4-bit mode
#define MODE_SERIAL     1  // Serial mode

// Set the interface mode
#define GLCD_INTERFACE   MODE_4BIT

// Port and pin definitions
#define GLCD_SID_PORT     PORTB  // SID=RW
#define GLCD_SID_PIN      0
#define GLCD_SCLK_PORT    PORTB  // SCLK=E
#define GLCD_SCLK_PIN     1

// 8-bit data
#define GLCD_DATA_DDR     DDRB
#define GLCD_DATA_PIN     PINB
#define GLCD_DATA_PORT    PORTB

// 8/4-bit control
#define GLCD_RS_PORT      PORTD
#define GLCD_RS_PIN       2
#define GLCD_EN_PORT      PORTD
#define GLCD_EN_PIN       0
#define GLCD_RW_PORT      PORTD
#define GLCD_RW_PIN       1

// Data port bits for 4-bit mode
#define GLCD_DATA_PORT_D7 GLCD_DATA_PORT
#define GLCD_DATA_PORT_D6 GLCD_DATA_PORT
#define GLCD_DATA_PORT_D5 GLCD_DATA_PORT
#define GLCD_DATA_PORT_D4 GLCD_DATA_PORT

#define GLCD_DATA_PIN_D7  3
#define GLCD_DATA_PIN_D6  2
#define GLCD_DATA_PIN_D5  1
#define GLCD_DATA_PIN_D4  0

// Control macros
#define GLCD_EN_HIGH()      GLCD_EN_PORT |= (1<<GLCD_EN_PIN)
#define GLCD_EN_LOW()       GLCD_EN_PORT &=~(1<<GLCD_EN_PIN)

#define GLCD_CMD_MODE()     GLCD_RS_PORT &=~(1<<GLCD_RS_PIN)
#define GLCD_DATA_MODE()    GLCD_RS_PORT |= (1<<GLCD_RS_PIN)

#define GLCD_RW_HIGH()      GLCD_RW_PORT |= (1<<GLCD_RW_PIN)
#define GLCD_RW_LOW()       GLCD_RW_PORT &=~(1<<GLCD_RW_PIN)

#define GLCD_DATA_DDR_OUTPUT()  GLCD_DATA_DDR = 0xff
#define GLCD_DATA_DDR_INPUT()   GLCD_DATA_DDR = 0x00

// Function prototypes
void GLCD(void);
void GLCD_init(void);
void GLCD_write_command(u8 command);
void GLCD_write_data(u8 data);
void GLCD_write_byte(u8 byte);
void GLCD_write_half_byte(u8 half_byte);
void GLCD2_spi_write_byte(u8 data);
void GLCD2_spi_write_byte_standard(u8 data);
u8 GLCD_read_data(void);
u8 GLCD_read_status(void);
u8 GLCD_read_byte(void);
void GLCD_startGraphic(void);
void GLCD_endGraphic(void);
void GLCD_Inverse_16X16(u16 rowCol, u8 charNum, u8 reverse);
u16 GLCD_rowCol_to_inter_Xy(u16 rowCol);
void GLCD_set_text_address(u16 rowCol);
void GLCD_set_graphic_address(u8 x, u8 y);
void GLCD_write_char(u16 rowCol, u16 code);
void GLCD_write_string(u16 rowCol, const char * p);
void GLCD_write_number(u16 rowCol, s16 CopyNumber);

#if GLCD_INTERFACE != MODE_SERIAL
void GLCD_write_dot(u8 x, u8 y);
#endif


// Row/column addressing
#define ROW_COL(r, c) (((r) << 8) | (c & 0xff))

#endif