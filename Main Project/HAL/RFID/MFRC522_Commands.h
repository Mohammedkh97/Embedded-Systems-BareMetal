/*
 * MFRC522_Commands.h
 *
 * Created: 7/18/2024 4:54:48 PM
 * Author: Mohammed Khalaf
 */ 


#ifndef MFRC522_COMMANDS_H_
#define MFRC522_COMMANDS_H_


/* MFRC522 Commands */
#define MFRC522_IDLE                        0x00	// NO action; Cancel the current command
#define MFRC522_Mem							0x01	// stores 25 bytes into the internal buffer
#define MFRC522_AUTHENT                     0x0E    // Authentication Key
#define MFRC522_RECEIVE                     0x08   //  Receive Data
#define MFRC522_TRANSMIT                    0x04   //  Transmit data
#define MFRC522_TRANSCEIVE                  0x0C   //  Transmit and receive data,
#define MFRC522_RESETPHASE                  0x0F   //  Reset
#define MFRC522_CALCCRC                     0x03   //  CRC Calculate

/* Mifare_One card command word */
#define PICC_REQIDL							0x26   // find the antenna area does not enter hibernation
#define PICC_REQALL							0x52   // find all the cards antenna area
#define PICC_ANTICOLL_CL1					0x93   // anti-collision CL1
#define PICC_ANTICOLL_CL2					0x95   // anti-collision CL2
#define PICC_ANTICOLL_CL3					0x97   // anti-collision CL3
#define PICC_SElECTTAG						0x93   // election card
#define PICC_AUTHENT1A						0x60   // authentication key A
#define PICC_AUTHENT1B						0x61   // authentication key B
#define PICC_READ							0x30   // Read Block
#define PICC_WRITE							0xA0   // write block
#define PICC_DECREMENT						0xC0   // debit
#define PICC_INCREMENT						0xC1   // recharge
#define PICC_RESTORE						0xC2   // transfer block data to the buffer
#define PICC_TRANSFER						0xB0   // save the data in the buffer
#define PICC_HALT							0x50   // Sleep


#endif /* MFRC522_COMMANDS_H_ */
