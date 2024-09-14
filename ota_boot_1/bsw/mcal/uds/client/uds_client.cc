#include "uds_client.h"

#define UDS_TARGET_ADDR 0x791
#define UDS_SOURCE_ADDR 0x719
#include "conf/uds_conf.h"

#include <string.h>
#include <stdbool.h>

#include "tp/isotp.h"

#include <inttypes.h>
#include <time.h>
#include <stdio.h>

uint32_t uds_milis()
{
  long ms;  // Milliseconds
  time_t s; // Seconds
  struct timespec spec;

  clock_gettime(CLOCK_REALTIME, &spec);

  s = spec.tv_sec;
  ms = spec.tv_nsec / 1.0e6; // Convert nanoseconds to milliseconds
  if (ms > 999)
  {
    s++;
    ms %= 1000;
  }

  return s*1000 + ms;
}

static isotp_link_t cli_link;
static bool resp_ready = false;
static uint16_t resp_len;
static uint8_t resp_buff[512];

void tp_recv_handler(uint32_t id, const uint8_t* data, uint16_t len) {
  printf("0x%x | RX | %u | ", id, len);
  for (uint16_t i = 0; i < len; ++i) {
    printf("%2x ", data[i]);
  }
  printf("\n");
  //TODO: check id before processing
  resp_len = len;
  resp_ready = true;
}

void UDS_Cli_Init() {
  cli_link.recv_cb = tp_recv_handler;
  cli_link.rx_buff = resp_buff;
  cli_link.rx_addr = UDS_SOURCE_ADDR;
  set_isotp_link(&cli_link);
}

resp_code_t DiagSess_Ctl(diag_sess_t session)
{
  printf("%s\n",__func__);
  uint8_t resp = RESPONE_TIMEDOUT;
  uint8_t payload[2] = {DIAG_SESS_CTL_SID, session}; // hard reset
  send_isotp(UDS_TARGET_ADDR, payload, sizeof(payload));

  uint32_t tick = uds_milis();
  while (uds_milis() - tick <= UDS_P2_TIMER_MS)
  {
    if (resp_ready) {
      /**
       * respone Payload expectation
       * |0x50|session_t|
       * 
       */
      if (resp_len == 2 
          && resp_buff[0] == POSITIVE_RESPONE_SID(DIAG_SESS_CTL_SID)
          && resp_buff[1] == session) {
        resp = POSITIVE_RESPONE;
      } else {
        resp = NEGATIVE_RESPONE;
      }
      resp_ready = false;
      break;
    }
  }

  return resp;
}

resp_code_t ECU_reset()
{
  printf("%s\n",__func__);
  /**
   * Request payload:
   * |0x11|0x01|
   *
   *       
   */
  uint8_t resp = RESPONE_TIMEDOUT;
  uint8_t payload[2] = {ECU_RESET_SID, 0x01}; // hard reset
  send_isotp(UDS_TARGET_ADDR, payload, sizeof(payload));

  uint32_t tick = uds_milis();
  while (uds_milis() - tick <= UDS_P2_TIMER_MS)
  {
    if (resp_ready) {
      /**
       * respone Payload expectation
       * |0x51|0x01|
       * 
       */
      if (resp_len == 2 
          && resp_buff[0] == POSITIVE_RESPONE_SID(ECU_RESET_SID)
          && resp_buff[1] == 0x01) {
        resp = POSITIVE_RESPONE;
      } else {
        resp = NEGATIVE_RESPONE;
      }
      resp_ready = false;
      break;
    }
  }

  return resp;
}

resp_code_t Request_Download(uint32_t mem_addr, uint32_t mem_size, uint32_t* block_len)
{
  printf("%s\n",__func__);

  uint8_t resp = RESPONE_TIMEDOUT;

  /**
   * Request payload:
   * |0x34|mem_addr (4 bytes)|mem_size (4 bytes)|
   *        ^-plain text
   *       
   */
  uint8_t payload[11];
  payload[0] = REQUEST_DOWNLOAD_SID;
  payload[1] = 0x00;
  payload[2] = 0x44;
  payload[3] = (mem_addr >> 24) & 0xFF;
  payload[4] = (mem_addr >> 16) & 0xFF;
  payload[5] = (mem_addr >> 8) & 0xFF;
  payload[6] = (mem_addr) & 0xFF;
  payload[7] = (mem_size >> 24) & 0xFF;
  payload[8] = (mem_size >> 16) & 0xFF;
  payload[9] = (mem_size >> 8) & 0xFF;
  payload[10] = (mem_size) & 0xFF;
  send_isotp(UDS_TARGET_ADDR, payload, sizeof(payload));

  uint32_t tick = uds_milis();
  while (uds_milis() - tick <= UDS_P2_TIMER_MS)
  {
    if (resp_ready) {
    // received payload and process
    /**
     * respone Payload expectation
     * |0x74|block_len (2 bytes)|
     * 
     */
      if (resp_len == 3
          && resp_buff[0] == POSITIVE_RESPONE_SID(REQUEST_DOWNLOAD_SID)) {
        // get block len
        *block_len = ((uint16_t)resp_buff[1] << 8) | resp_buff[2];
        resp = POSITIVE_RESPONE;
      } else {
        resp = NEGATIVE_RESPONE;
      }

      if (resp_len == 1
          && resp_buff[0] == NEGATIVE_RESPONE) {
        resp = NEGATIVE_RESPONE;
      }
      resp_ready = false;
      break;
    }
  }

  return resp;
}

resp_code_t Transfer_Data(uint8_t seq_cnt, const uint8_t* data, uint32_t block_size)
{
  printf("%s\n",__func__);

  uint8_t resp = RESPONE_TIMEDOUT;

  /**
   * Request payload: len n
   * |0x36|seq_cnt|data0|data1|....
   */
  uint8_t payload[512];
  payload[0] = TRANSFER_DATA_SID;
  payload[1] = seq_cnt;
  memcpy(payload + 2, data, block_size);
  send_isotp(UDS_TARGET_ADDR, payload, block_size + 2);

  uint32_t tick = uds_milis();
  while (uds_milis() - tick <= UDS_P2_TIMER_MS)
  {
    if (resp_ready) {
    // received payload and process
    /**
     * respone Payload expectation
     * |0x76|seq_cnt|
     * 
     */
      if (resp_len == 2 
          && resp_buff[0] == POSITIVE_RESPONE_SID(TRANSFER_DATA_SID)
          && resp_buff[1] == seq_cnt) {     
        resp = POSITIVE_RESPONE;
      } else {
        resp = NEGATIVE_RESPONE;
      }
      resp_ready = false;
      break;
    }
  };

  return resp;
}

resp_code_t Transfer_Exit()
{
  printf("%s\n",__func__);

  uint8_t resp = RESPONE_TIMEDOUT;

  /**
   * Request payload:
   * |0x37|
   */
  uint8_t payload[1] = {TRANSFER_EXIT_SID};
  send_isotp(UDS_TARGET_ADDR, payload, sizeof(payload));

  uint32_t tick = uds_milis();
  while (uds_milis() - tick <= UDS_P2_TIMER_MS)
  {
    if (resp_ready) {
    // received payload and process
    /**
     * respone Payload expectation
     * |0x77|
     * 
     */
      if (resp_len == 1
          && resp_buff[0] == POSITIVE_RESPONE_SID(TRANSFER_EXIT_SID)) {     
        resp = POSITIVE_RESPONE;
      } else {
        resp = NEGATIVE_RESPONE;
      }
      resp_ready = false;
      break;
    }
  };

  return resp;
}

// Complete transfer
resp_code_t Check_Memory(uint32_t* crc) {
  printf("%s\n",__func__);

  uint8_t resp = RESPONE_TIMEDOUT;

  /**
   * Request payload:
   * |0x31|0xFE|0xF2|
   *       
   */
  uint8_t payload[3] = {ROUTINE_CTL_SID, 0xFE, 0xF2};
  send_isotp(UDS_TARGET_ADDR, payload, sizeof(payload));

  uint32_t tick = uds_milis();
  while (uds_milis() - tick <= UDS_P2_TIMER_MS)
  {
    if (resp_ready) {
    // received payload and process
    /**
     * respone Payload expectation
     * |0x71|0xFE|0xF2|crc (4 bytes)|
     * 
     */
      if (resp_len == 7
          && resp_buff[0] == POSITIVE_RESPONE_SID(ROUTINE_CTL_SID)
          && resp_buff[1] == 0xFE
          && resp_buff[2] == 0xF2) {
        // get block len
        *crc = ((uint32_t)resp_buff[3] << 24) 
              | ((uint32_t)resp_buff[4] << 16) 
              | ((uint32_t)resp_buff[5] << 8) 
              | ((uint32_t)resp_buff[6]);
        resp = POSITIVE_RESPONE;
      } else {
        resp = NEGATIVE_RESPONE;
      }
      resp_ready = false;
      break;
    }
  }

  return resp;
}