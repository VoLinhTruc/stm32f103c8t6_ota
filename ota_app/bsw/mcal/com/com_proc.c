/*
 * com_proc.c
 *
 *  Created on: Jul 3, 2024
 *      Author: nda9hc
 */


#include "com_proc.h"

extern void can_polling(void);

void COM_Proc_Init() {
  can_start();
}

void COM_Proc_1ms() {

//	can_polling();

  if (can_rx_available() == CAN_SUCCESS) {
    const can_rx_msg_t*	rx_msg = can_receive();
    for (int i = 0; i < sizeof(recv_handler)/sizeof(recv_handler_t); ++i) {
      recv_handler[i](rx_msg);
    }
    can_process_next();
  }
}
