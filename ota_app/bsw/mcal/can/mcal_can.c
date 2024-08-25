#include "mcal_can.h"
#include "mcal_can_conf.h"
#include "utils/circular_buffer.h"

static circular_buff_t can_rx_fifo;
static can_rx_msg_t can_rx_msg_buff[CAN_RX_BUFFER_SIZE];

extern CAN_HandleTypeDef hcan;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  if (hcan->Instance == CAN1)
  {
    can_rx_msg_t rx_it;
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_it.header, rx_it.data);
    buffer_push(&can_rx_fifo, &rx_it, sizeof(can_rx_msg_t));
	HAL_GPIO_TogglePin(PCB_LED_GPIO_Port, PCB_LED_Pin);
  }
}

void can_polling(void)
{
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);

	uint8_t fifo0;
	fifo0 = HAL_CAN_GetRxFifoFillLevel(&hcan, 0);
	uint8_t fifo1;
	fifo1 = HAL_CAN_GetRxFifoFillLevel(&hcan, 1);

	can_rx_msg_t rx_it;
	if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rx_it.header, rx_it.data) == HAL_OK)
	{
		buffer_push(&can_rx_fifo, &rx_it, sizeof(can_rx_msg_t));
		HAL_GPIO_TogglePin(PCB_LED_GPIO_Port, PCB_LED_Pin);
	}
}

void can_start(void)
{
  init_buffer(&can_rx_fifo, can_rx_msg_buff, CAN_RX_BUFFER_SIZE);
  // TODO: filter now accept for everything
  CAN_FilterTypeDef sFilterConfig = {0};
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.FilterIdHigh = 0;
  sFilterConfig.FilterIdLow = 0;
  sFilterConfig.FilterMaskIdHigh = 0;
  sFilterConfig.FilterMaskIdLow = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterActivation = ENABLE;
  HAL_CAN_ConfigFilter(&hcan,&sFilterConfig);
  // start can and interrupt here
  HAL_CAN_Start(&hcan);
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void can_stop(void)
{
  HAL_CAN_DeactivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
  HAL_CAN_Stop(&hcan);
}

void can_send(const can_tx_msg_t *msg)
{
  uint32_t TxMailbox;
  HAL_CAN_AddTxMessage(&hcan, &msg->header, msg->data, &TxMailbox);
}

const can_rx_msg_t *can_receive(void)
{
  return buffer_front(&can_rx_fifo, sizeof(can_rx_msg_t));
}

int32_t can_rx_available(void) {
  return buffer_available(&can_rx_fifo);
}

void can_process_next(void) {
  buffer_pop(&can_rx_fifo);
}
