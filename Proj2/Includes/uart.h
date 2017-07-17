/*
 * uart.h
 *
 *  Created on: Jul 16, 2017
 *      Author: Sreela Pavani
 */

#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

#include <stdio.h>
#include <stdint.h>
#include "circbuf.h"

#define baudrate 115200
#define osr 16

#define TXBUF_LENGTH 400
#define RXBUF_LENGTH 16

CB_t *tx_buf,*rx_buf;
void UART_configure();
uint8_t UART_send(uint8_t *character);
uint8_t UART_send_n(uint8_t *data , uint8_t length);
uint8_t UART_receive(uint8_t *receivedchar);
uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length);
void UART0_IRQHandler();


#endif /* SOURCES_UART_H_ */
