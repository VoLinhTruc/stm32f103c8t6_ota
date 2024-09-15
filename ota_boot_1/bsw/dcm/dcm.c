/*
 * dcm.c
 *
 *  Created on: Jul 3, 2024
 *      Author: nda9hc
 */

#include "mcal/uds/server/uds_server.h"
#include "stm32f1xx_hal.h"
#include "ota/ota.h"

extern UART_HandleTypeDef huart2;
static FLASH_EraseInitTypeDef EraseInitStruct;
static uint32_t PageError;

void DCM_Proc_Init() {
  UDS_Srv_Init();
}

resp_code_t ECU_reset_Handler()
{
	HAL_NVIC_SystemReset();
	return POSITIVE_RESPONE;
}

resp_code_t Write_Data_By_ID_Handler(uint16_t did, const uint8_t* data, uint32_t block_size)
{
//	char mess[40] = {0};
//	sprintf(mess, "WDBI: %x %d\r\n", did, *(uint32_t*)data);
//	HAL_UART_Transmit(&huart2, mess, sizeof(mess), 1000);

	uint32_t app_firmware_size = GET_APP_FIRMWARE_SIZE();
	uint32_t expected_app_firmware_crc = GET_EXPECTED_APP_FIRMWARE_CRC();
	uint32_t calculated_app_firmware_crc = GET_CALCULATED_APP_FIRMWARE_CRC();

	if (did == 0x1001)
	{
		app_firmware_size = *(uint32_t*)data;
	}
	if (did == 0x1002)
	{
		expected_app_firmware_crc = *(uint32_t*)data;
	}

	HAL_FLASH_Unlock();
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks 		= FLASH_BANK_1;
	EraseInitStruct.PageAddress	= CALCULATED_APP_FIRMWARE_CRC_ADDR;
	EraseInitStruct.NbPages		= 1;
	HAL_FLASHEx_Erase( &EraseInitStruct, &PageError );
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, APP_FIRMWARE_SIZE_ADDR, app_firmware_size);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EXPECTED_APP_FIRMWARE_CRC_ADDR, expected_app_firmware_crc);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CALCULATED_APP_FIRMWARE_CRC_ADDR, calculated_app_firmware_crc);
	HAL_FLASH_Lock();

	return POSITIVE_RESPONE;
}

// To jump to programing or application
resp_code_t DiagSess_Ctl_Handler(diag_sess_t session) { return POSITIVE_RESPONE;}

// Preparation for download new SW
resp_code_t Request_Download_Handler(uint32_t mem_addr, uint32_t mem_size, uint32_t* block_len)
{
	ota_flashing_begin();

	return POSITIVE_RESPONE;
}

// Transfer data
resp_code_t Transfer_Data_Handler(uint8_t seq_cnt, const uint8_t* data, uint32_t block_size)
{
	uint32_t data_u32 = *((uint32_t*)data);
	ota_flashing_inprogress(data_u32);

	return POSITIVE_RESPONE;
}

// Complete transfer
resp_code_t Transfer_Exit_Handler()
{
	ota_flashing_end();

	return POSITIVE_RESPONE;
}


// Complete transfer
resp_code_t Check_Memory_Handler(uint32_t* crc) { return POSITIVE_RESPONE;}
