#include "MKL25Z4.h"
#include "uart.h"
#include <stdio.h>
#include <stdint.h>

#define PROJECT2

int main(void)
{
#ifdef PROJECT2
	project2();
#endif
	return 0;
}
