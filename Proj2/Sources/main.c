
/*@file -main.c
 *@brief - compile time switch
 *@author : Sreela , Sowmya
 *@date : Jul 19 , 2017
 */

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
