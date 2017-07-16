
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "memory.h"

/*Checking that big to little function doesn't return invalid pointer status*/
void memmove_tests(void **state)
{
  uint8_t i;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;

  uint8_t status;  

  /* 2 -  Testing for non overlap */
  set = (uint8_t*) reserve_words( MEM_SET_SIZE_W );
  if (! set ) 
      status = INVALID_POINTER;
  assert_int_not_equal(status,INVALID_POINTER);

  ptra = &set[0];
  ptrb = &set[16];
  status = my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH); /*  Testing for invalid pointer */
  assert_int_not_equal(status,INVALID_POINTER);
  for(i = 0; i < MEM_SET_SIZE_B; i++)                   
  {
    set[i] = i;    /* Initialize the set to test values */
  }
  status = my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  assert_int_not_equal(status,INVALID_POINTER);
  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
    assert_int_equal(set[i + 16],i);
  }
  free_words((uint32_t*)set);

  /*3. Testing for overlap of SRC in DST Overlap*/
  set = (uint8_t*) reserve_words(MEM_SET_SIZE_W);       
  if (! set )
      status = INVALID_POINTER;
  assert_int_not_equal(status,INVALID_POINTER);

  ptra = &set[0];
  ptrb = &set[8];   
  status = my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH); /*   Testing for invalid pointer */
  assert_int_not_equal(status,INVALID_POINTER);
  for( i = 0; i < MEM_SET_SIZE_B; i++) {
    set[i] = i;                                      
  }
  status = my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  assert_int_not_equal(status,INVALID_POINTER);
  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
    assert_int_equal(set[i + 8],i);
  }
  free_words( (uint32_t*)set );

/* 4 -  Testing for DST in SRC region Overlap*/
  set = (uint8_t*)reserve_words( MEM_SET_SIZE_W);    
  if (! set ) 
  {
    status = INVALID_POINTER;
  }
  assert_int_not_equal(status,INVALID_POINTER);
  ptra = &set[8];
  ptrb = &set[0];
  status = my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH); /* 1-  Testing for invalid pointer */
  assert_int_not_equal(status,INVALID_POINTER);
  for( i = 0; i < MEM_SET_SIZE_B; i++)
  {
    set[i] = i;
  }
  status = my_memmove(ptra, ptrb, TEST_MEMMOVE_LENGTH);
  assert_int_not_equal(status,INVALID_POINTER);
  for (i = 0; i < TEST_MEMMOVE_LENGTH; i++)
  {
    assert_int_equal(set[i],(i + 8));
  }
  free_words( (uint32_t*)set );
}

/*Checking that little to big function doesn't return invalid pointer status*/
void memset_tests(void **state)
{
  uint8_t i;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;
  int8_t status;
  set = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (! set ) 
  {
    status = INVALID_POINTER;
  }
  assert_int_not_equal(status,INVALID_POINTER);
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++) 
  {
    set[i] = i;
  }
  status = my_memset(ptra, MEM_SET_SIZE_B, 0xFF);
  assert_int_not_equal(status,INVALID_POINTER);
  /* Validate Set & Zero Functionality */
  for (i = 0; i < MEM_ZERO_LENGTH; i++)
  {
    assert_int_equal(set[i],0xFF);
  }

  free_words( (uint32_t*)set );  
}

void memzero_tests(void **state)
{
  uint8_t i;
  uint8_t * set;
  uint8_t * ptra;
  uint8_t * ptrb;
  int8_t status;

  set = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (! set ) 
  {
    status = INVALID_POINTER;
  }
  assert_int_not_equal(status,INVALID_POINTER);
  ptra = &set[0];
  ptrb = &set[16];

  /* Initialize the set to test values */
  for( i = 0; i < MEM_SET_SIZE_B; i++) 
  {
    set[i] = i;
  }
  status = my_memzero(ptrb, MEM_ZERO_LENGTH);
  assert_int_not_equal(status,INVALID_POINTER); 

 /* Validate Set & Zero Functionality */
  for (i = 0; i < MEM_ZERO_LENGTH; i++)
  {
    assert_int_equal(set[16 + i],0);
  }
  free_words( (uint32_t*)set );  
}

void reverse_tests(void **state)
{
  uint8_t i;
  int8_t status;
  uint8_t * copy;

  /*1 - Odd length test */
  uint8_t set1[MEM_SET_SIZE_B] = {0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26,
                                 0x48, 0x63, 0x20, 0x66, 0x6F, 0x00, 0x20, 0x33,
                                 0x72, 0x75, 0x74, 0x78, 0x21, 0x4D, 0x20, 0x40,
                                 0x20, 0x24, 0x7C, 0x20, 0x24, 0x69, 0x68, 0x54
                               };
  copy = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (copy == NULL)
  {
    status = INVALID_POINTER;
  }
  assert_int_not_equal(status,INVALID_POINTER);
  
  status = my_memcpy(set1, copy, MEM_SET_SIZE_B);
  assert_int_not_equal(status,INVALID_POINTER); 
  
  status = my_reverse(set1, MEM_SET_SIZE_B);
  assert_int_not_equal(status,INVALID_POINTER); 

  for (i = 0; i < MEM_SET_SIZE_B; i++)
  {
    assert_int_equal(set1[i],copy[MEM_SET_SIZE_B - i - 1]);
  }
  free_words( (uint32_t*)copy );

  /*2 - Even length test */
  uint8_t set2[(MEM_SET_SIZE_B-1)] = {0x3F, 0x73, 0x72, 0x33, 0x54, 0x43, 0x72, 0x26,
                            0x48, 0x63, 0x20, 0x66, 0x6F, 0x00, 0x20, 0x33,
                            0x72, 0x75, 0x74, 0x78, 0x21, 0x4D, 0x20, 0x40,
                            0x20, 0x24, 0x7C, 0x20, 0x24, 0x69, 0x68 
                          };
  copy = (uint8_t*)reserve_words(MEM_SET_SIZE_W);
  if (copy == NULL)
  {
    status = INVALID_POINTER;
  }
  assert_int_not_equal(status,INVALID_POINTER);
  
  status = my_memcpy(set2, copy, (MEM_SET_SIZE_B-1));
  assert_int_not_equal(status,INVALID_POINTER); 
  
  status = my_reverse(set2, (MEM_SET_SIZE_B-1));
  assert_int_not_equal(status,INVALID_POINTER); 

  for (i = 0; i < (MEM_SET_SIZE_B-1); i++)
  {
    assert_int_equal(set2[i],copy[(MEM_SET_SIZE_B-1) - i - 1]);
  }
  free_words( (uint32_t*)copy );  
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(memmove_tests),
    cmocka_unit_test(memset_tests),
    cmocka_unit_test(memzero_tests),
    cmocka_unit_test(reverse_tests),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}