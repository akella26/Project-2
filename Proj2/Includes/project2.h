
/**
 * @file project2.h 
 * @brief This file is to be used to project 2.
 *
 * @author Sowmya , Pavani
 * @date July 16, 2017
 *
 */
#ifndef __PROJECT2_H__
#define __PROJECT2_H__

#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"

#define BUF_LEN 255
#define USERDEF_RXBUF_MAX 10

void dump_statistics(int32_t count_a, int32_t count_p, int32_t count_m, int32_t count_n);
void my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

#endif /* __PROJECT2_H__ */
