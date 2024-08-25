#ifndef UDS_CLIENT_H
# define UDS_CLIENT_H

#include "conf/uds_def.h"

void UDS_Cli_Init();

// Soft reset ecu
resp_code_t ECU_reset();

// To jump to programing or application
resp_code_t DiagSess_Ctl(diag_sess_t session);

// Preparation for download new SW
resp_code_t Request_Download(uint32_t mem_addr, uint32_t mem_size, uint32_t* block_len);

// Transfer data
resp_code_t Transfer_Data(uint8_t seq_cnt, const uint8_t* data, uint32_t block_size);

// Complete transfer
resp_code_t Transfer_Exit();

// Complete transfer
resp_code_t Check_Memory(uint32_t* crc);

#endif