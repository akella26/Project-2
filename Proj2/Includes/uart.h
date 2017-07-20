<<<<<<< HEAD
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

#define BIT0 0X00

CB_t *tx_buf ,*rx_buf;

void UART_configure();
uint8_t UART_send(uint8_t *character);
uint8_t UART_send_n(uint8_t *data , uint8_t length);
uint8_t UART_receive(uint8_t *receivedchar);
uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length);



#endif /* SOURCES_UART_H_ */



=======
/*@file -uart.h
 *@brief - header file for uart.c
 *contains all functions defined in uart.c
 *@author : Sreela , Sowmya
 *@date : Jul 19 , 2017
 */



#ifndef __UART_H_
#define __UART_H_

#define baud 115200
#define OSR 15
#define baudset  (SystemCoreClock/(baud*(OSR+1)))
#define BIT0 0X00
#define BUFFER_LEN 500
#define buffh 0
#define buffl 11
#include<stdio.h>
#include<stdint.h>
#include "circbuf.h"

/*@brief : sets all the registers required for UART
 *@ param : no
 *@ return : no return
 */

void UART_configure();

/*@brief : send a byte in uart
 *@ param : pointer to send item
 *@ return :  0 for fail , 1 for pass
 */

uint8_t UART_send(uint8_t *character);

/*@brief : send a string in uart
 *@ param : pointer to string , length of string
 *@ return :  0 for fail , 1 for pass
 */
uint8_t UART_send_n(uint8_t *data , uint8_t length);

/*@brief : receive a byte in uart
 *@ param : pointer to receive item
 *@ return :  0 for fail , 1 for pass
 */
uint8_t UART_receive(uint8_t *receivedchar);

/*@brief : receive a string in uart
 *@ param : pointer to receive string , length of string
 *@ return :  0 for fail , 1 for pass
 */
uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length);
CB_t *tx_buf ,*rx_buf; // pointers to receive and transmission buffers


/*@brief : send items into transmission buffer
 *@ param : no
 *@ return :no
*/
void send_buffer();

/*@brief : receive items from receive buffer
 *@ param : no
 *@ return :no
*/
void receive_buffer();

#endif /* __UART_H_ */
>>>>>>> 5bc61fb079fdb4efca6271be83f994c64f81cc65
