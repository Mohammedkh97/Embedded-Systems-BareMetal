/*
 * MFRC522_Registers.h
 *
 * Created: 7/18/2024 4:55:58 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef MFRC522_REGISTERS_H_
#define MFRC522_REGISTERS_H_

/* MFRC522 Registers */

typedef enum {
	Reserved00       = 0x00,
	CommandReg       = 0x01,
	ComIEnReg        = 0x02,
	DivIEnReg        = 0x03,
	ComIrqReg        = 0x04,
	DivIrqReg        = 0x05,
	ErrorReg         = 0x06,
	Status1Reg       = 0x07,
	Status2Reg       = 0x08,
	FIFODataReg      = 0x09,
	FIFOLevelReg     = 0x0A,
	ControlReg       = 0x0C,
	BitFramingReg    = 0x0D,
	CollReg          = 0x0E,

	// Page 1: Command
	Reserved10       = 0x10,
	ModeReg          = 0x11,
	TxModeReg        = 0x12,
	RxModeReg        = 0x13,
	TxControlReg     = 0x14,
	TxASKReg         = 0x15,
	TxSelReg         = 0x16,
	RxSelReg         = 0x17,
	RxThresholdReg   = 0x18,
	DemodReg         = 0x19,
	Reserved11       = 0x1A,
	Reserved12       = 0x1B,
	MifareReg        = 0x1C,
	Reserved13       = 0x1D,
	Reserved14       = 0x1E,
	SerialSpeedReg   = 0x1F,

	// Page 2: CFG
	Reserved20       = 0x20,
	CRCResultRegH    = 0x21,
	CRCResultRegL    = 0x22,
	Reserved21       = 0x23,
	ModWidthReg      = 0x24,
	Reserved22       = 0x25,
	RFCfgReg         = 0x26,
	GsNReg           = 0x27,
	CWGsPReg         = 0x28,
	ModGsPReg        = 0x29,
	TModeReg         = 0x2A,
	TPrescalerReg    = 0x2B,
	TReloadRegH      = 0x2C,
	TReloadRegL      = 0x2D,
	TCounterValueRegH= 0x2E,
	TCounterValueRegL= 0x2F,

	// Page 3: TestRegister
	Reserved30       = 0x30,
	TestSel1Reg      = 0x31,
	TestSel2Reg      = 0x32,
	TestPinEnReg     = 0x33,
	TestPinValueReg  = 0x34,
	TestBusReg       = 0x35,
	AutoTestReg      = 0x36,
	VersionReg       = 0x37,
	AnalogTestReg    = 0x38,
	TestDAC1Reg      = 0x39,
	TestDAC2Reg      = 0x3A,
	TestADCReg       = 0x3B,
	Reserved31       = 0x3C,
	Reserved32       = 0x3D,
	Reserved33       = 0x3E,
	Reserved34       = 0x3F
} MFRC522_Register_t;

/* Mifare_One card command word */
#define PICC_REQIDL				  0x26   // find the antenna area does not enter hibernation
#define PICC_REQALL				  0x52   // find all the cards antenna area
#define PICC_ANTICOLL_CL1		  0x93   // anti-collision CL1
#define PICC_ANTICOLL_CL2  		  0x95   // anti-collision CL2
#define PICC_ANTICOLL_CL3  		  0x97   // anti-collision CL3
#define PICC_SElECTTAG			  0x93   // election card
#define PICC_AUTHENT1A			  0x60   // authentication key A
#define PICC_AUTHENT1B			  0x61   // authentication key B
#define PICC_READ				  0x30   // Read Block
#define PICC_WRITE				  0xA0   // write block
#define PICC_DECREMENT			  0xC0   // debit
#define PICC_INCREMENT			  0xC1   // recharge
#define PICC_RESTORE			  0xC2   // transfer block data to the buffer
#define PICC_TRANSFER			  0xB0   // save the data in the buffer
#define PICC_HALT				  0x50   // Sleep


#endif /* MFRC522_REGISTERS_H_ */