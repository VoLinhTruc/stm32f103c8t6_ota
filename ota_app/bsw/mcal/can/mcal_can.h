/**
 * @file mcal_can.h
 * @author nguyen thanh dat <datnguyen0203@gmail.com>
 * @brief can layer provide api to application
 * @version 0.1
 * @date 2024-05-27
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef MCAL_CAN_H
#define MCAL_CAN_H

#include <stdint.h>

#include "main.h"

#define CAN_SUCCESS 0
#define CAN_FAILED -1

typedef CAN_RxHeaderTypeDef can_rx_header_t;
typedef CAN_TxHeaderTypeDef can_tx_header_t;

typedef struct {
  can_rx_header_t header;
  uint8_t data[8];
} can_rx_msg_t;

typedef struct {
  can_tx_header_t header;
  uint8_t data[8];
} can_tx_msg_t;


void can_start(void);
void can_stop(void);
void can_polling(void);

void can_send(const can_tx_msg_t* msg);
const can_rx_msg_t* can_receive(void);
int32_t can_rx_available(void);
void can_process_next(void);

#endif
