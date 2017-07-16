#ifndef __UART_H__
#define __UART_H__
#define BIT0 0X00
uint32_t baud=115200;
uint16_t sbrate=0;
uint32_t MCGfreq=48000000;

void UART_configure();
uint8_t UART_send(uint8_t *character);
uint8_t UART_send_n(uint8_t *data , uint8_t length);
uint8_t UART_receive(uint8_t *receivedchar);
uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length);

#endif /*__UART_H__*/
