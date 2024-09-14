#include "circular_buffer.h"
#include "us_memcpy.h"

#include <stddef.h>
/**
 * init:
 * head
 * tail
 * [ ] [ ] [ ] [ ]
 *
 * push: buff[tail++] = ele
 * head
 *     tail
 * [x] [ ] [ ] [ ]
 *
 * front: buff[head]
 * head
 *     tail
 * [x] [ ] [ ] [ ]
 *
 * pop: head++
 *     head
 *     tail
 * [x] [ ] [ ] [ ]
 *
 * available: head  == tail
 *     head
 *     tail
 * [ ] [ ] [ ] [ ]
 *
 * full: give one left for easier
 *     head
 * tail
 * [ ] [x] [x] [x]
 *
 */

static uint16_t buffer_rotate(uint16_t point, uint16_t max)
{
  uint16_t ret = point + 1;
  if (ret == max)
    ret = 0;
  return ret;
}

void init_buffer(buff_handler_t handler, void *buff, uint16_t size)
{
  handler->buff = buff;
  handler->buff_size = size;
  handler->head = 0u;
  handler->tail = 0u;
}

int32_t buffer_available(const buff_handler_t handler)
{
  return (handler->head == handler->tail) ? -1 : 0;
}

message_t buffer_front(buff_handler_t handler, uint16_t msg_size)
{
  message_t ret = NULL;
  if (buffer_available(handler) != -1)
  {
    ret = handler->buff + handler->head * msg_size;
  }
  return ret;
}

int32_t buffer_push(buff_handler_t handler, message_t msg, uint16_t msg_size)
{
  if (buffer_rotate(handler->tail, handler->buff_size) != handler->head)
  {
    us_memcpy(handler->buff + handler->tail * msg_size, msg, msg_size);
    handler->tail = buffer_rotate(handler->tail, handler->buff_size);
    return 0;
  }
  return -1;
}

int32_t buffer_pop(buff_handler_t handler)
{
  if (buffer_available(handler) != -1)
  {
    handler->head = buffer_rotate(handler->head, handler->buff_size);
    return 0;
  }
  return -1;
}
