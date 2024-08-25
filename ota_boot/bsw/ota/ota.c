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
uint32_t goto_app_timer = GOTO_APP_TIMER; // 5000ms
static uint32_t addr_index = 0;
FLASH_EraseInitTypeDef EraseInitStruct;
uint32_t PageError;
extern UART_HandleTypeDef huart2;
extern CAN_HandleTypeDef hcan;


void goto_application( void );

void ota_polling()
{
	goto_app_timer--;
	if (goto_app_timer < 1)
	{
		goto_app_timer = GOTO_APP_TIMER;
		HAL_UART_Transmit(&huart2, "Boot End\r\n", sizeof("Boot End\r\n"), 1000);
		HAL_Delay(100);
		goto_application();
//		HAL_NVIC_SystemReset();
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

	goto_app_timer = GOTO_APP_TIMER;
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
	goto_app_timer = GOTO_APP_TIMER;
}


void ota_flashing_end(void)
{
	HAL_FLASH_Lock();
	ota_flashing_state = FLASHING_IDLE;
	HAL_NVIC_SystemReset();
}


void goto_application(void)
{
//  __set_MSP(*(volatile uint32_t*) APPPLICATION_START_ADDR);

  /* Jump to application */
  void (*app_reset_handler)(void) = (void*)(*((volatile uint32_t*) (APPPLICATION_RESET_HANDLE_VECTOR_ADDR)));
  app_reset_handler();    //call the app reset handler
}

