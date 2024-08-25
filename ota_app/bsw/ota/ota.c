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

void ota_ini_after_reset()
{

}


void ota_flashing_begin(void)
{
	HAL_NVIC_SystemReset();
}


void ota_flashing_inprogress(uint32_t data)
{

}


void ota_flashing_end(void)
{

}


