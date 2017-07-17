/**
 * @file circbuf.h
 * @brief This file contains function declarations of circbug.c
 *
 * @author Sowmya Akella
 * @date July 1, 2017
 *
 */

#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdint.h>

#define BUF_TEST_SIZE 3

typedef struct {
	uint8_t *buffer;
	uint8_t head;
	uint8_t tail;
	uint8_t count;
	uint8_t length;
}CB_t;

typedef enum {
	buf_full,
	buf_empty,
	success,
	null_error_databuff,
	null_error_circbuff,
	free_success
}CB_status;

CB_status status;

CB_status CB_init(CB_t * buf_pointer,uint8_t length);
CB_status CB_buffer_add_item(CB_t * buf_pointer,uint8_t new_item);
CB_status CB_buffer_remove_item(CB_t * buf_pointer,uint8_t * item_removed);
CB_status CB_is_full(CB_t * buf_pointer);
CB_status CB_is_empty(CB_t * buf_pointer);
CB_status CB_peek(CB_t * buf_pointer, uint8_t peek_position,uint8_t * peek_item);
CB_status CB_destroy(CB_t * buf_pointer);

#endif /* __CIRCBUF_H__ */
