/*
 * uart.h
 *
 *  Created on: Jul 16, 2017
 *      Author: AnnSneha
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

#define BIT0 0X00
#include<stdio.h>
#include<stdint.h>
void UART_configure();
uint8_t UART_send(uint8_t *character);
uint8_t UART_send_n(uint8_t *data , uint8_t length);
uint8_t UART_receive(uint8_t *receivedchar);
uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length);



#endif /* SOURCES_UART_H_ */
