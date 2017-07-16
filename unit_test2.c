
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "conversion.h"

/*Checking that big to little function doesn't return invalid pointer status*/
void big_to_little(void **state)
{
  uint32_t data[BTOL_TEST_SIZE] = {0x51,0x24,0x25};
  int8_t status;
  status = big_to_little32(data, BTOL_TEST_SIZE);
  assert_int_not_equal(status,INVALID_POINTER);
  
  assert_int_equal(data[0],0x25);
  assert_int_equal(data[1],0x24);
  assert_int_equal(data[2],0x51);
}

/*Checking that little to big function doesn't return invalid pointer status*/
void little_to_big(void **state)
{
  uint32_t data[LTOB_TEST_SIZE] = {0x51,0x24,0x25};
  int8_t status;
  status = little_to_big32(data,LTOB_TEST_SIZE);
  assert_int_not_equal(status,INVALID_POINTER);

  assert_int_equal(data[0],0x25);
  assert_int_equal(data[1],0x24);
  assert_int_equal(data[2],0x51);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(big_to_little),
    cmocka_unit_test(little_to_big),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}