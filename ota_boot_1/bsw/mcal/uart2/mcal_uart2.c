/*
 * mcal_uart2.c
 *
 *  Created on: Aug 24, 2024
 *      Author: VOR5HC
 */

#include "mcal_uart2.h"

//static circular_buff_t uart2_rx_fifo;
//static can_rx_msg_t uart2_rx_msg_buff[UART2_RX_BUFFER_SIZE];
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	uint8_t received_data = 0x00;
//	HAL_UART_Receive_IT(&huart1, &received_data, (uint16_t)1);
//	buffer_push(&uart2_rx_fifo, &received_data, 1);
//	HAL_GPIO_TogglePin(PCB_LED_GPIO_Port, PCB_LED_Pin);
//}
//
//void uart_start(void)
//{
//	init_buffer(&uart2_rx_fifo, uart2_rx_msg_buff, sizeoff(uart2_rx_msg_buff));
//
//}
//
//void uart_process(void)
//{
//
//}
