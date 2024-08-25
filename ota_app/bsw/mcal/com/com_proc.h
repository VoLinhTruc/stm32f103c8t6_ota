/*
 * com_proc.h
 *
 *  Created on: Jul 3, 2024
 *      Author: nda9hc
 */

#ifndef MCAL_COM_COM_PROC_H_
#define MCAL_COM_COM_PROC_H_

#include "mcal/can/mcal_can.h"
#include "mcal/tp/isotp.h"

typedef void (*recv_handler_t)(const can_rx_msg_t* frame);

static recv_handler_t recv_handler[] = {
  isotp_can_recv
};

void COM_Proc_Init();
void COM_Proc_1ms();

#endif /* MCAL_COM_COM_PROC_H_ */
