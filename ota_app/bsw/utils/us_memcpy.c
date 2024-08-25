/*
 * us_memcpy.c
 *
 *  Created on: May 29, 2024
 *      Author: nda9hc
 */

#include "us_memcpy.h"

void us_memcpy(void *dst, const void *src, uint32_t size)
{
  // Copy longwords, taking advantage of STM ability to read/write unaligned data
  while (size >= 4)
  {
    *(uint32_t *)dst = *(
        const uint32_t *)src;
    dst = (uint8_t *)dst + 4;
    src = (const uint8_t *)src + 4;
    size -= 4;
  }
  // Copy the couple of leftover bytes
  while (size--)
  {
    *(uint8_t *)dst = *(
        const uint8_t *)src;
    dst = (uint8_t *)dst + 1;
    src = (const uint8_t *)src + 1;
  }
}
