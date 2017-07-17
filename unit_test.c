/**
 * @file unit_test.c
 * @brief This file contains unit tests for teting circular buffer
 * @author Sowmya Akella
 * @date July 16, 2017
 *
 */
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "circbuf.h"

/*
 * @brief - Checks that data buffer inside circular buffer is initialized and freed correctly  
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */

void AllocateFree(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 

  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  status = CB_init(circbuf,BUF_TEST_SIZE);
  assert_int_equal(status,success);
  status = CB_destroy(circbuf);
  assert_int_equal(status,free_success);
}

/*
 * @brief - Checking that all functions where Circular buffer is passed, the pointer is valid
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */
void InvalidPointer(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t));
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  uint8_t item, item_removed, peek_position, peek_item;
  item = 4;
  peek_position = 2;
  /* Testing for null error in functions */
  /*1*/
  status = CB_init(circbuf,BUF_TEST_SIZE);                
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,success);
  /*2*/
  status = CB_buffer_add_item(circbuf,item); 
  assert_int_not_equal(status,null_error_circbuff);
  /*3*/ 
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_not_equal(status,null_error_circbuff);
  /*4*/
  status = CB_peek(circbuf,peek_position,&peek_item); 
  assert_int_not_equal(status,null_error_circbuff); 
  /*5*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);

}

/*
 * @brief - Checking if non initialized pointers are detected
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */
void NonInitializedPointer(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  status = CB_init(circbuf,BUF_TEST_SIZE);
  assert_int_equal(status,success);        /* checking if data buffer has been allocated memory*/
  assert_int_equal(circbuf->length,BUF_TEST_SIZE); /*Checking if length is assigned correctly)*/
  assert_int_equal(circbuf->head,0);        /*Checking if 0 is initialized to indexes*/
  assert_int_equal(circbuf->tail,0);
  assert_int_equal(circbuf->count,0);

  status = CB_destroy(circbuf);
  assert_int_equal(status,free_success);
}

/*
 * @brief - Checking 3 cases for addition and deletion - add 1 del 1, add 2 del 1, add 3 del 3
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */
void AddRemove(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  uint8_t item_removed;
  uint8_t test_items[BUF_TEST_SIZE] = {4,6,7};

  status = CB_init(circbuf,BUF_TEST_SIZE);   
  assert_int_equal(status,success); 

/* 1st test - Testing for Adding 1 item and removing 1 item */          
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);
  assert_int_equal(item_removed,test_items[0]);  /*Checking items*/

/* 2nd test - Testing for Adding 2 items and removing 1 item */
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[1]); 
  assert_int_equal(status,success);
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);
  assert_int_equal(item_removed,test_items[0]);  /*Checking removed items*/

  /*Removing item to do next test*/
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);

/* 3rd test - Testing for Adding 2 more items(one from previous test) removing 1 item */
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[1]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[2]); 
  assert_int_equal(status,success);
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);
  assert_int_equal(item_removed,test_items[0]);  /*Checking items*/

/*Destroying the buffer*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);
}
/*
 * @brief - Checking if buffer full returns true - positive testing
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */
void BufferFull(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  uint8_t test_items[BUF_TEST_SIZE] = {4,6,7};

  status = CB_init(circbuf,BUF_TEST_SIZE);   
  assert_int_equal(status,success); 

/*Adding 4 items and checking buffer full for last item*/          
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[1]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[2]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[2]); /*Adding item after buffer is full*/
  assert_int_equal(status,buf_full);

  /*Destroying the buffer*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);
}

/*
 * @brief - Checking if buffer empty returns true - positive testing
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */
void BufferEmpty(void **state)
{
  CB_t *circbuf;
  uint8_t item_removed;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  status = CB_init(circbuf,BUF_TEST_SIZE);   
  assert_int_equal(status,success); 

/* Removing item from an empty initialized buffer and checking for success of buf empty test*/          
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,buf_empty);

  /*Destroying the buffer*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);
}

/*
 * @brief - Checking wrapping around circular buffer and adding is successfull
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */

void WrapAdd(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  uint8_t peek_position=0,peek_item,item_removed;
  uint8_t test_items[BUF_TEST_SIZE] = {4,6,7};

  status = CB_init(circbuf,BUF_TEST_SIZE);   
  assert_int_equal(status,success); 

/* Testing for 3 items added, 1 removed and adding again so that wrap add succeeds */
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[1]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[2]); 
  assert_int_equal(status,success);
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);
  /*Adding item again to check success of Wrap Add*/
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  /*Asserting that peeked value is value added*/
  status = CB_peek(circbuf,peek_position,&peek_item); 
  assert_int_equal(status,success);
  assert_int_equal(peek_item,test_items[0]);

/*Destroying the buffer*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);
}
/*
 * @brief - Checking wrapping around circular buffer and removing is successfull
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */

void WrapRemove(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  uint8_t peek_position=0,peek_item,item_removed;
  uint8_t test_items[BUF_TEST_SIZE] = {4,6,7};

  status = CB_init(circbuf,BUF_TEST_SIZE);   
  assert_int_equal(status,success); 

/* Testing for 3 items added, 1 removed and adding again so that wrap add succeeds */
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[1]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[2]); 
  assert_int_equal(status,success);
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);
  /*Adding item again to check success of Wrap Add*/
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);

  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);

  /*Peeking into first position before removing items after tail wrap around*/
  status = CB_peek(circbuf,peek_position,&peek_item); 
  assert_int_equal(status,success);
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success);

  /*Asserting that peeked value is value removed*/
  assert_int_equal(item_removed,peek_item);

/*Destroying the buffer*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);
}
/*
 * @brief - Checking of overfil addition of circular buffer returns failure - negative testing
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */
void OverFill(void **state)
{
  CB_t *circbuf;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  uint8_t test_items[BUF_TEST_SIZE] = {4,6,7};

  status = CB_init(circbuf,BUF_TEST_SIZE);   
  assert_int_equal(status,success); 

/*Adding 4 items and checking buffer full for last item*/          
  status = CB_buffer_add_item(circbuf,test_items[0]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[1]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[2]); 
  assert_int_equal(status,success);
  status = CB_buffer_add_item(circbuf,test_items[2]); /*Adding item after buffer is full*/
  assert_int_equal(status,success); /*Buffer should fail if too many items added*/

  /*Destroying the buffer*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);
}

/*
 * @brief - Checking of overempty deletion of circular buffer returns failure - negative testing
 * @param - arguments - cmocka state double pointer
 * @return - none 
 */
void OverEmpty(void **state)
{
  CB_t *circbuf;
  uint8_t item_removed;
  circbuf = (CB_t*)malloc(sizeof(CB_t)); 
  if(circbuf == NULL)
    status = null_error_circbuff;
  assert_int_not_equal(status,null_error_circbuff);

  status = CB_init(circbuf,BUF_TEST_SIZE);   
  assert_int_equal(status,success); 

/* Removing item from an empty initialized buffer and checking for success of buf empty test*/          
  status = CB_buffer_remove_item(circbuf,&item_removed); 
  assert_int_equal(status,success); /*Buffer should fail to remove items if empty*/

  /*Destroying the buffer*/
  status = CB_destroy(circbuf); 
  assert_int_not_equal(status,null_error_circbuff);
  assert_int_equal(status,free_success);
}

/*
 * @brief - Main with list of function pointers
 * @param - arguments argc and argv
 * @return - Test results
 */
int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(AllocateFree),
    cmocka_unit_test(InvalidPointer),
    cmocka_unit_test(NonInitializedPointer),
    cmocka_unit_test(AddRemove),
    cmocka_unit_test(BufferFull),
    cmocka_unit_test(BufferEmpty),
    cmocka_unit_test(WrapAdd),
    cmocka_unit_test(WrapRemove),
    cmocka_unit_test(OverFill),
    cmocka_unit_test(OverEmpty),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}