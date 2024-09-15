/*
 * ota.c
 *
 *  Created on: Aug 24, 2024
 *      Author: VOR5HC
 */
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "ota.h"
#include "mcal/uart2/mcal_uart2.h"

Ota_Flashing_State ota_flashing_state = FLASHING_IDLE;
static uint32_t addr_index = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;
static uint32_t PageError;
extern UART_HandleTypeDef huart2;
extern CAN_HandleTypeDef hcan;
uint8_t app_firmware_valid = 0;
uint32_t app_firmware_len_recieve_from_can = 0;
uint32_t app_firmware_crc_recieve_from_can = 0;

static uint16_t boot_time = 0;


uint32_t calculate_crc(uint32_t app_firmware_addr, uint32_t length)
{
    uint32_t crc = 0xFFFFFFFF;  // Initial CRC value
    for (uint32_t i = 0; i < length; i+=4) {
        uint32_t word = ((uint32_t)(*((volatile uint32_t*) (app_firmware_addr + i))));
        crc ^= word;
        for (int j = 0; j < 32; j++) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^ CRC_POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc ^ 0xFFFFFFFF;  // Final XOR value
}


int verify_firmware(uint32_t  expected_crc)
{
	uint8_t ret = 0;
	uint32_t app_firmware_size = GET_APP_FIRMWARE_SIZE();
	if ((app_firmware_size != 0xFFFFFFFF) && (app_firmware_size != 0))
	{
		uint32_t calculated_crc = calculate_crc(APPPLICATION_START_ADDR, GET_APP_FIRMWARE_SIZE());
		ret = (calculated_crc == expected_crc);

		uint32_t app_firmware_size = GET_APP_FIRMWARE_SIZE();
		uint32_t expected_app_firmware_crc = GET_EXPECTED_APP_FIRMWARE_CRC();
		HAL_FLASH_Unlock();
		EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.Banks 		= FLASH_BANK_1;
		EraseInitStruct.PageAddress	= CALCULATED_APP_FIRMWARE_CRC_ADDR;
		EraseInitStruct.NbPages		= 1;
		HAL_FLASHEx_Erase( &EraseInitStruct, &PageError );
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, APP_FIRMWARE_SIZE_ADDR, app_firmware_size);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, EXPECTED_APP_FIRMWARE_CRC_ADDR, expected_app_firmware_crc);
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, CALCULATED_APP_FIRMWARE_CRC_ADDR, calculated_crc);
		HAL_FLASH_Lock();
	}

    return ret;
}


void ota_init()
{
	uint32_t expected_app_firmware_crc = GET_EXPECTED_APP_FIRMWARE_CRC();
	app_firmware_valid = verify_firmware(expected_app_firmware_crc);

//	char mess[40] = {0};
//	sprintf(mess, "mess: %x\r\n", GET_APP_FIRMWARE_SIZE());
//	HAL_UART_Transmit(&huart2, mess, sizeof(mess), 1000);
//
//	char expected_app_firmware_crc_mess[40] = {0};
//	sprintf(expected_app_firmware_crc_mess, "expected_app_firmware_crc: %x\r\n", expected_app_firmware_crc);
//	HAL_UART_Transmit(&huart2, expected_app_firmware_crc_mess, sizeof(expected_app_firmware_crc_mess), 1000);
//
	char app_firmware_valid_mess[40] = {0};
	sprintf(app_firmware_valid_mess, "app_firmware_valid: %d\r\n", app_firmware_valid);
	HAL_UART_Transmit(&huart2, app_firmware_valid_mess, sizeof(app_firmware_valid_mess), 1000);

	if (app_firmware_valid)
	{
		HAL_UART_Transmit(&huart2, "Boot End\r\n", sizeof("Boot End\r\n"), 1000);
		HAL_Delay(100);
		goto_application();
	}
}

void ota_polling()
{
	if (boot_time++ == BOOT_TIME_OUT_VALUE)
	{
		ota_init();
		boot_time = 0;
	}

	static uint16_t count = 0;
	count++;
	if ((count % 250) == 0)
	{
		char mess[40] = {0};
		sprintf(mess, "Boot time (ms):  %d\r\n", count);
		HAL_UART_Transmit(&huart2, mess, sizeof(mess), 1000);
	}
}

void ota_flashing_begin(void)
{
	ota_flashing_state = FLASHING_REQUESTED;

	HAL_FLASH_Unlock();
	EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks 		= FLASH_BANK_1;
	EraseInitStruct.PageAddress	= APPPLICATION_START_ADDR;
	EraseInitStruct.NbPages		= APPPLICATION_SIZE / 1024;
	HAL_FLASHEx_Erase( &EraseInitStruct, &PageError );

	boot_time = 0;
}


void ota_flashing_inprogress(uint32_t data)
{
	if (ota_flashing_state == FLASHING_REQUESTED)
	{
		ota_flashing_state = FLASHING_INPROGRESS;
	}

	if (ota_flashing_state == FLASHING_INPROGRESS)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, APPPLICATION_START_ADDR + addr_index, data);
		addr_index += 4;

		static uint32_t counter = 0;
		counter++;
		uint8_t uart_data[30] = {0};
		sprintf((char*)uart_data, "SID 0x36 %02x %02x %02x %02x\r\n", (data>>24)&255, (data>>16)&255, (data>>8)&255, (data>>0)&255);
		HAL_UART_Transmit(&huart2, uart_data, sizeof(uart_data), 1000);
	}

	boot_time = 0;
}


void ota_flashing_end(void)
{
	HAL_FLASH_Lock();
	ota_flashing_state = FLASHING_IDLE;

	boot_time = 0;

	HAL_NVIC_SystemReset();
}


void goto_application(void)
{
//  __set_MSP(*(volatile uint32_t*) APPPLICATION_START_ADDR);

  /* Jump to application */
  void (*app_reset_handler)(void) = (void*)(*((volatile uint32_t*) (APPPLICATION_RESET_HANDLE_VECTOR_ADDR)));
  app_reset_handler();    //call the app reset handler
}


