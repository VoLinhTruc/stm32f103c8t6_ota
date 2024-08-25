/*
 * ota.h
 *
 *  Created on: Aug 24, 2024
 *      Author: VOR5HC
 */

#ifndef OTA_OTA_H_
#define OTA_OTA_H_

#define BOOTLOADER_START_ADDR			0x08000000
#define BOOTLOADER_SIZE					0x4000 // 16K Bytes

#define BK_APPPLICATION_START_ADDR		BOOTLOADER_START_ADDR + BOOTLOADER_SIZE // 0x08004000
#define BK_APPPLICATION_SIZE			0x1C00 // 7168 bytes

#define INFO_DATA_START_ADDR			BK_APPPLICATION_START_ADDR + BK_APPPLICATION_SIZE // 0x08005C00
#define INFO_DATA_START_SIZE			0x400 // 1024 bytes = 1K = 1 Page

#define APPPLICATION_START_ADDR			INFO_DATA_START_ADDR + INFO_DATA_START_SIZE // 0x08006000
#define APPPLICATION_SIZE				0xA000 // 40960 Bytes = 40K = 40 Pages
#define END_OFF_FLASH					APPPLICATION_START_ADDR + APPPLICATION_SIZE // <end of flash>

#define APPPLICATION_RESET_HANDLE_VECTOR_ADDR	APPPLICATION_START_ADDR + 4

#define GET_FLASHING_REQUEST_FLAG		(uint32_t)(*((volatile uint32_t*) (INFO_DATA_START_ADDR)));


typedef enum
{
	FLASHING_IDLE = 0,
	FLASHING_REQUESTED = 1,
	FLASHING_INPROGRESS = 2
} Ota_Flashing_State;


extern Ota_Flashing_State ota_flashing_state;


void ota_ini_after_reset();
void ota_flashing_begin(void);
void ota_flashing_inprogress(uint32_t data);
void ota_flashing_end(void);


#endif /* OTA_OTA_H_ */
