/*
 * flash_handling.c
 *
 *  Created on: Aug 24, 2024
 *      Author: VOR5HC
 */

#include "flash_handling.h"
#include "stm32f1xx_hal.h"


uint32_t get_data_from_address(uint32_t address)
{
	return (uint32_t)(*((volatile uint32_t*) (address)));
}


uint32_t set_data_to_address(uint32_t address, uint32_t data)
{
//	HAL_FLASH_Unlock();
//
//	FLASH_EraseInitTypeDef EraseInitStruct;
//	uint32_t PageError;
//
//	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
//	EraseInitStruct.Banks 		= FLASH_BANK_1;
//	EraseInitStruct.PageAddress	= address;
//	EraseInitStruct.NbPages		= 1;
//
//	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, INFO_DATA_START_ADDR, counter);
//
//	HAL_FLASH_Lock();
}
