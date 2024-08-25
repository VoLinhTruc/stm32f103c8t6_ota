#ifndef UDS_SERVER_H
# define UDS_SERVER_H

#include "mcal/uds/conf/uds_def.h"

void UDS_Srv_Init();

// Soft reset ecu
resp_code_t ECU_reset_Handler();

// To jump to programing or application
resp_code_t DiagSess_Ctl_Handler(diag_sess_t session);

// Preparation for download new SW
resp_code_t Request_Download_Handler(uint32_t mem_addr, uint32_t mem_size, uint32_t* block_len);

// Transfer data
resp_code_t Transfer_Data_Handler(uint8_t seq_cnt, const uint8_t* data, uint32_t block_size);

// Complete transfer
resp_code_t Transfer_Exit_Handler();

// Complete transfer
resp_code_t Check_Memory_Handler(uint32_t* crc);

#endif
