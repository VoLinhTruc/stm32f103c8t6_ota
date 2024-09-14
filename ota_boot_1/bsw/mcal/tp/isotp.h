/**
 * @file isotp.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-16
 * 
 * @copyright Copyright (c) 2024
 * 
 * This file take ref from https://www.csselectronics.com/pages/uds-protocol-tutorial-unified-diagnostic-services#can-iso-tp
 * 
 * Implementation cover
 * + single frame
 * + first frame
 * + consecutive frame
 * 
 * Fault frame handling
 * + Can only process single frame type as one time
 * + If frame drop due to some reason, completion of reassembly will not happened (seq mis-match -> total and received never match)
 * + In between of reassembly if new first frame detected, it will start with new multi frame
 * 
 * Send of multiframe will be blocked until complete payload is sent
 */

#ifndef __ISOTP__H__
#define __ISOTP__H__

#include <stdint.h>

#include "mcal/can/mcal_can.h"

typedef void (*isotp_recv_handler_t)(uint32_t id, const uint8_t* data, uint16_t len);
typedef struct {
  uint32_t rx_addr;
  uint32_t tx_addr;
  uint8_t *rx_buff;
  uint32_t recv_byte;
  uint32_t total_byte;
  uint8_t seq_num;
  isotp_recv_handler_t recv_cb;
} isotp_link_t;

void set_isotp_link(isotp_link_t* tplink);
void send_isotp(const uint8_t* data, uint32_t len);
void isotp_can_recv(const can_rx_msg_t* frame);

#endif  //!__ISOTP__H__
