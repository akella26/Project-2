#include <uart.h>
#include "MKL25Z4.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circbuf.h"

volatile uint8_t ritem=0;
char c = 'r';

/*@brief : sets all the registers required for UART
 *@ param : no
 *@ return : no return
 */
void UART_configure()
{
	/* we are going to use UART0 because it has DMA interface function which can be used in project3 */

	/*enabling clocks*/
	__disable_irq();
	SIM_SCGC4|=SIM_SCGC4_UART0(1); // Clock enabled for UART
	SIM_SOPT2|=SIM_SOPT2_UART0SRC(1); // MCGFLLCLK clock selected for UART0
	SIM_SCGC5|=SIM_SCGC5_PORTA_MASK; // clock enabled for PORTA

	/*UART0 configuration*/
	PORTA_PCR1|=PORT_PCR_MUX(2); //TX of UART0 functionality is used
	PORTA_PCR2|=PORT_PCR_MUX(2); //RX of UART0 functionality is used
	UART0_C2 = BIT0; //Disabling interrupts for Rx and Tx,Tx and Rx disabled
	UART0_C1 = BIT0; //not checking parity and enabling 8 bit data
    UART0_BDH|=UART0_BDH_SBNS(0);// one stop bit selected
    // UART0_BDH =((baudset>>8)&UART_BDH_SBR_MASK);  // baud rate register high
    //UART0_BDL =(baudset& UART_BDL_SBR_MASK);      // baud rate register low
    UART0_BDH = buffh; //baud rate  high register
    UART0_BDL = buffl; //baud rate low register
    UART0_C4_OSR(15); // setting over sampling ratio for baud rate modulo divisor calculations
  /*Done with setting so enabling interrupts*/
    UART0_C2|=UART_C2_RIE_MASK; //enable UART receive interrupt only in config
    UART0_C2|=UART_C2_TE_MASK|UART_C2_RE_MASK; // enable RX and Tx));
//    status = CB_init(rx_buf,BUF_LEN);
    NVIC_EnableIRQ(UART0_IRQn);
	__enable_irq();
}


/*@brief : send a byte in uart
 *@ param : pointer to send item
 *@ return :  0 for fail , 1 for pass
 */

uint8_t UART_send(uint8_t *character)
{
	if(character==NULL)
	{
		return 0;
	}
	while(!(UART0_S1 & UART0_S1_TDRE_MASK))
	{
		// block transmission until Transmit buffer is empty
	}
	UART0_D = *character; /*TDRE cleared(tx buff full) on writing to D register*/
	return 1;
}

/*@brief : send a string in uart
 *@ param : pointer to string , length of string
 *@ return :  0 for fail , 1 for pass
 */

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


/*@brief : receive a byte in uart
 *@ param : pointer to receive item
 *@ return :  0 for fail , 1 for pass
 */

uint8_t UART_receive(uint8_t *receivedchar)
{
	if(receivedchar == NULL)
	{
		return 0;
	}
	while(!(UART0_S1 & UART0_S1_RDRF_MASK))
	{

	}
	*receivedchar= UART0_D;
	return 1;
}

/*@brief : receive a string in uart
 *@ param : pointer to receive string , length of string
 *@ return :  0 for fail , 1 for pass
 */

uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length)
{
	uint8_t counter=0;
	if(receivedata == NULL || length <= 0)
	{
		return 0;
	}
	for(counter=0;counter<length;counter++) //receive blocking is done in UART_receive
	{
		UART_receive(receivedata+counter);
	}
	return 1;
}


/*@brief : Checking Tx and Rx flags
 * circular buffer integration
 *@ param : no
 *@ return : 1 or 0
*/
bool checkReceive()
{
	return (UART0_S1 & UART_S1_RDRF_MASK);
}

bool checkTransmit()
{
	return (UART0_S1 & UART_S1_TDRE_MASK);
}


/*@brief : interrupt handler
 * circular buffer integration
 *@ param : no
 *@ return :no
*/
void UART0_IRQHandler()
{
	__disable_irq();
	CB_status flag1,flag2;
	flag1 = CB_is_empty(tx_buf);

	if(checkTransmit() && (flag1 == buf_notempty))
	{
	    uint8_t tm=0;
	    CB_buffer_remove_item(tx_buf,&tm);
	    UART_send(&tm);
	}
	else if (flag1 == buf_empty)
	{
		//Disable Transmit interrupt
	   UART0_C2 &= ~UART0_C2_TIE_MASK;
	}

    flag2 = CB_is_full(rx_buf);
    if(checkReceive() && (flag2 == buf_notfull))
    {
    	// Buffer got space and receiving character
    	uint8_t rc=0;
    	UART_receive(&rc);
    	CB_buffer_add_item(rx_buf,rc);
    	//UART_send(&rc);
    	c = c + 1;
    }
    else if (flag2 == buf_full)
    {
    	// ignore character
    }
	__enable_irq();
}






