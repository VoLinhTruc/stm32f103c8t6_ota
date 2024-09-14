/*
 * dcm.c
 *
 *  Created on: Jul 3, 2024
 *      Author: nda9hc
 */

#include "mcal/uds/server/uds_server.h"
#include "stm32f1xx_hal.h"
#include "ota/ota.h"


void DCM_Proc_Init() {
  UDS_Srv_Init();
}

resp_code_t ECU_reset_Handler()
{
	HAL_NVIC_SystemReset();
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
