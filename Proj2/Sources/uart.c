#include "uart.h"
#include "MKL25Z4.h"
#include <stdint.h>
#include <stdio.h>

uint16_t sbrate=0;

void UART_configure()
{
	__disable_irq();
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;          /* Enabling clock for PORTA module */
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;			/* Enabling clock gate for UART0 */

	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);	/* Selecting clock src for UART0 either MCGFLLCLK clock or MCGPLLCLK/2 clock */

	PORTA_PCR1 = PORT_PCR_MUX(2);	/* Setting MUX to Alternative 2 to enable UART0 */
	PORTA_PCR2 = PORT_PCR_MUX(2);

	UART0_C1 = 0;	    	/* Setting 8 bit data and disabling parity for UART0 */
	UART0_C2 = 0;			/* Setting 8 bit data and disabling parity for UART0 */

	sbrate = DEFAULT_SYSTEM_CLOCK/(baudrate*osr);    //baud
	UART0_BDH |= ((sbrate>>8) & UART_BDH_SBR_MASK);  // baud rate register high
	UART0_BDL =(sbrate & UART_BDL_SBR_MASK);         // baud rate register low

	UART0_C2 = (UART_C2_RIE_MASK | UART0_C2_RE_MASK | UART0_C2_TE_MASK);  /* Enabling Tx and Rx interrupt */
	/* transmit buffer */
	tx_buf = (CB_t*)malloc(sizeof(CB_t));
	CB_init(&tx_buf, TXBUF_LENGTH);

	/* receive buffer */
	rx_buf = (CB_t*)malloc(sizeof(CB_t));
	CB_init(&rx_buf, RXBUF_LENGTH);
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn,2);								/* Setting priority of UART0 */
	__enable_irq();
}

uint8_t UART_send(uint8_t *character)
{
	if(character==NULL)
	{
		return 0;
	}
	while(!(UART0_S1 & UART_S1_TDRE_MASK)); // block transmission
	UART0_D=*character;

	return 1;
}

uint8_t UART_send_n(uint8_t *data , uint8_t length)
{
	uint8_t counter=0;
	if(data==NULL)
	{
		return 0;
	}
	if(length==0)
	{
		return 0;
	}
	for(counter=0;counter<length;counter++) //transmission blocking is done in UART_send
	{
		UART_send(data+counter);
	}
	return 1;
}

uint8_t UART_receive(uint8_t *receivedchar)
{
	if(receivedchar=NULL)
	{
		return 0;
	}
	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	*receivedchar = UART0_D;
	return 1;
}

uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length)
{
	uint8_t counter=0;
	if(receivedata==NULL)
	{
		return 0;
	}
	if(length==0)
	{
		return 0;
	}
	for(counter=0;counter<length;counter++) //transmission blocking is done in UART_send
	{
		UART_receive(receivedata+counter);
	}
	return 1;
}


extern void UART0_IRQHandler()
{
	NVIC_DisableIRQ(UART0_IRQn);

	uint8_t stat = UART0_S1;
	CB_status flag = CB_is_empty(tx_buf);

	if((UART0_S1 & UART_S1_TDRE_MASK) && (flag == !(buf_empty)))
	{
		uint8_t string_1[32];
		uint8_t *temp;
		temp = string_1;
		CB_buffer_remove_item(tx_buf,temp);
		UART_send(*temp);
	}
	else
	{
		UART0_C2 &= ~UART0_C2_TIE_MASK;	 /* If tx buffer empty disable the tx interrupt */
	}

	flag = CB_is_empty(rx_buf);

	if((stat & UART0_S1_RDRF_MASK) && (flag == !(buf_full)))
	{									 /* If buffer is not full and RDRF flag is set then recieve the character from UARTD0 */
		uint8_t temp2;
		UART_receive(&temp2);
		//UART_send(temp2);
		CB_buffer_add_item(rx_buf, temp2);
	}
	else
	{
		UART0_C2 &= ~UART0_C2_RIE_MASK; /* If rx buffer is full then disable the rx interrupt */
	}

	// Turn interrupts back on
	NVIC_EnableIRQ(UART0_IRQn);

}
