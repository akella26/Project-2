/*@file -project2.c
 *@brief - file which ties all the other modules together , used to testing uart
 *@author : Sreela , Sowmya
 *@date : Jul 19 , 2017
 */

#include "MKL25Z4.h"
#include "uart.h"
#include<stdio.h>
#include<stdint.h>
#include "project2.h"

void project2()
{
	uint8_t i = 0,m=0;
	UART_configure();
	//uint8_t tx_test1= {0x01,0x02,0x03,0x04,0x05};
	uint8_t receive_test=0;
	uint8_t data = 0x00;
	//    while(m<3)
	//    {
	i = UART_receive(&data);
	while(1);
}



