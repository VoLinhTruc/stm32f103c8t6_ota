#include "uds_server.h"

#include "mcal/uds/conf/uds_conf.h"

#include "mcal/tp/isotp.h"

#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static uint8_t srv_payload[64];
static isotp_link_t srv_link;

extern UART_HandleTypeDef huart2;

void tp_recv_handler(uint32_t id, const uint8_t *data, uint16_t len)
{
  uint8_t ret;
  uint32_t resp;
  uint32_t resp_len = 0;

  switch (data[0])
  {
  case ECU_RESET_SID:
    ret = ECU_reset_Handler();
    if (ret == POSITIVE_RESPONE) {
    	srv_payload[0] = ECU_RESET_SID + 0x40;
    	srv_payload[1] = 0x01;
      resp_len = 2;
    } else {
    	srv_payload[0] = NEGATIVE_RESPONE;
      resp_len = 1;
    }
    break;
  case DIAG_SESS_CTL_SID:
    ret = DiagSess_Ctl_Handler(data[1]);
    if (ret == POSITIVE_RESPONE) {
    	srv_payload[0] = DIAG_SESS_CTL_SID + 0x40;
    	srv_payload[1] = data[1];
      resp_len = 2;
    } else {
    	srv_payload[0] = NEGATIVE_RESPONE;
      resp_len = 1;
    }
    break;

  case WRITE_DATA_BY_ID_SID:
	  uint16_t did = ((uint16_t)data[1] << 8) | data[2];
	  ret = Write_Data_By_ID_Handler(did, &data[3], len - 3);
		if (ret == POSITIVE_RESPONE) {
			srv_payload[0] = DIAG_SESS_CTL_SID + 0x40;
			srv_payload[1] = data[1];
			srv_payload[2] = data[2];
		  resp_len = 3;
		} else {
			srv_payload[0] = NEGATIVE_RESPONE;
		  resp_len = 1;
		}
    break;

  case ROUTINE_CTL_SID:
    if (data[1] == 0xFE && data[2] == 0xF2) {
      ret = Check_Memory_Handler(&resp);
      if (ret == POSITIVE_RESPONE) {
    	  srv_payload[0] = ROUTINE_CTL_SID + 0x40;
        srv_payload[1] = 0xFE;
        srv_payload[2] = 0xF2;
        srv_payload[3] = (resp >> 24) & 0xFF;
        srv_payload[4] = (resp >> 16) & 0xFF;
        srv_payload[5] = (resp >> 8) & 0xFF;
        srv_payload[6] = resp & 0xFF;
        resp_len = 7;
      } else {
    	  srv_payload[0] = NEGATIVE_RESPONE;
        resp_len = 1;
      }
    } else {
    	srv_payload[0] = NEGATIVE_RESPONE;
      resp_len = 1;
    }
    break;
  case REQUEST_DOWNLOAD_SID:

    ret = Request_Download_Handler(
      ((uint32_t)data[3] << 24 | (uint32_t)data[4] << 16) | (uint32_t)data[5] << 8 | (uint32_t)data[6],
      ((uint32_t)data[7] << 24 | (uint32_t)data[8] << 16) | (uint32_t)data[9] << 8 | (uint32_t)data[10],
      &resp);
    if (ret == POSITIVE_RESPONE) {
    	srv_payload[0] = REQUEST_DOWNLOAD_SID + 0x40;
      srv_payload[1] = (resp >> 8) & 0xFF;
      srv_payload[2] = resp & 0xFF;
      resp_len = 3;
    } else {
    	srv_payload[0] = NEGATIVE_RESPONE;
      resp_len = 1;
    }

    break;
  case TRANSFER_DATA_SID:
    ret = Transfer_Data_Handler(data[1], data + 2, len - 2);
    if (ret == POSITIVE_RESPONE) {
    	srv_payload[0] = TRANSFER_DATA_SID + 0x40;
      srv_payload[1] = data[1];
      resp_len = 2;
    } else {
    	srv_payload[0] = NEGATIVE_RESPONE;
      resp_len = 1;
    }

    break;
  case TRANSFER_EXIT_SID:
    ret = Transfer_Exit_Handler();
    if (ret == POSITIVE_RESPONE) {
    	srv_payload[0] = TRANSFER_EXIT_SID + 0x40;
      resp_len = 1;
    } else {
    	srv_payload[0] = NEGATIVE_RESPONE;
      resp_len = 1;
    }
    break;
  default:
	  srv_payload[0] = NEGATIVE_RESPONE;
    resp_len = 1;
  }
  send_isotp(srv_payload, resp_len);
}

void UDS_Srv_Init() {
  srv_link.recv_cb = tp_recv_handler;
  srv_link.rx_buff = srv_payload;
  srv_link.rx_addr = UDS_SOURCE_ADDR;
  srv_link.tx_addr = UDS_TARGET_ADDR;
  set_isotp_link(&srv_link);
}
