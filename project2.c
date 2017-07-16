/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file project1_test.c 
 * @brief This file is to be used to project 1.
 *
 * @author Alex Fosdick
 * @date April 2, 2017
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "circbuf.h"
#include "debug.h"
#include "project2.h"

void project2(void) 
{
  printf("\nHello\n");
}

// void basic_test1()
// {
//  uint8_t i,length,item_removed,peek_item; 
//   CB_t circ_buf;
//   CB_t *buf_pointer1 = &circ_buf;
//   length = BUF_SIZE;
//   status = CB_init(buf_pointer1,length);
//   status = CB_buffer_add_item(buf_pointer1,10);
//   status = CB_buffer_add_item(buf_pointer1,20);
//   status = CB_buffer_add_item(buf_pointer1,30);
//   status = CB_buffer_add_item(buf_pointer1,40);
//   status = CB_buffer_add_item(buf_pointer1,50);
//   status = CB_buffer_add_item(buf_pointer1,60);
//   status = CB_buffer_remove_item(buf_pointer1,&item_removed);
//   printf("Item removed is = %d \n",item_removed);
//   status = CB_buffer_remove_item(buf_pointer1,&item_removed);
//   printf("Item removed is = %d \n",item_removed);
//   status = CB_peek(buf_pointer1,4,&peek_item);
//   printf("Item peeked is  = %d \n",peek_item);
//   printf("Count = %d \n",buf_pointer1->count);
//   printf("Head index = %d \n",buf_pointer1->head);
//   printf("Tail index = %d \n",buf_pointer1->tail);
//   printf("\nFinal Elements of the buffer:\n");
//   for(i=0;i<length;i++)
//     printf("\n %d,",buf_pointer1->buffer[i]);
//     printf("\n");
//   status = CB_destroy(buf_pointer1);
//   switch (status)
//   {
//     case buf_full: printf("\nBuffer is full, try again later\n"); 
//                     // exit(1);
//                      break;
//     case buf_empty: printf("\nBuffer is empty, no action happened\n");
//                  break;
//     case success: printf("\nBuffer action success\n"); 
//              break;
//     case null_error:printf("\nNull pointer detected. Exiting\n");
//              break;
//     case free_success:printf("\nFreeing is a success\n");
//              break;
//   }
//   return; 
// }
