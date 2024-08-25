/**
 * circular buffer for light weight queue
 * Support bare metal and RTOS
 * Single Provider/Single Consumer
 */

#ifndef __CIRCULAR_BUFFER__H__
#define __CIRCULAR_BUFFER__H__

#include <stdint.h>

typedef struct circular_buff_t
{
  void *buff;
  uint16_t head;
  uint16_t tail;
  uint16_t buff_size;
} circular_buff_t;

typedef circular_buff_t *buff_handler_t;
typedef void *message_t;

/**
 * @brief initialize circular buffer (FIFO)
 * 
 * @param handler pointer to circular buffer object
 * @param buff actual underlying data buffer
 * @param size size of underlying buffer
 */
void init_buffer(buff_handler_t handler, void *buff, uint16_t size);

/**
 * @brief check if data in buffer is available for read
 * 
 * @param handler pointer to circular buffer object
 * @return 0 data is available for read
 * @return -1 buffer is empty
 */
int32_t buffer_available(const buff_handler_t handler);

/**
 * @brief push one msg (data) into buffer, this action will deep-copy msg to buffer 
 * 
 * @param handler pointer to circular buffer object
 * @param msg pointer to msg
 * @param msg_size size of msg
 * @return 0 success to push
 * @return -1 false to push - buffer full
 */
int32_t buffer_push(buff_handler_t handler, message_t msg, uint16_t msg_size);

/**
 * @brief pop front msg out of buffer
 * 
 * @param handler pointer to circular buffer object
 * @return 0 pop success
 * @return -1 nothing to pop
 */
int32_t buffer_pop(buff_handler_t handler);

/**
 * @brief get front msg of buffer
 * 
 * @param handler pointer to circular buffer object
 * @param msg_size size of msg
 * @return message_t pointer to msg data, if no msg to be get, NULL is returned
 */
message_t buffer_front(buff_handler_t handler, uint16_t msg_size);

#endif //!__CIRCULAR_BUFFER__H__
