#ifndef UDS_DEF_H
# define UDS_DEF_H

#include <stdint.h>

typedef uint8_t sid_t;
#define DIAG_SESS_CTL_SID 0x10
#define ECU_RESET_SID 0x11
#define ROUTINE_CTL_SID 0x31
#define REQUEST_DOWNLOAD_SID 0x34
#define TRANSFER_DATA_SID 0x36
#define TRANSFER_EXIT_SID 0x37
#define POSITIVE_RESPONE_SID(SID) ((SID) + 0x40)

typedef uint8_t diag_sess_t;
#define DIAG_DEFAULT_SESS 0x01
#define DIAG_PROGRAM_SESS 0x02 // Reset require
#define DIAG_UPDATE_SESS 0x60 // No Reset require

typedef uint8_t resp_code_t;
#define RESPONE_TIMEDOUT 0xFF
#define NEGATIVE_RESPONE 0x7F
#define POSITIVE_RESPONE 0x00



uint32_t uds_milis();

#endif