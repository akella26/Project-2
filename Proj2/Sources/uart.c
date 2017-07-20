/*@file -uart.c
 *@brief - contains configurations and other function definitions related to uart
 *@author : Sreela , Sowmya
 *@date : Jul 19 , 2017
 */


#include "uart.h"
#include "MKL25Z4.h"
#include<stdint.h>
#include<stdio.h>
#include "circbuf.h"

/*@brief : sets all the registers required for UART
 *@ param : no
 *@ return : no return
 */

void UART_configure()
{
	/* we are going to use UART0 because it has DMA interface function which can be used in project3 */
	/*enabling clocks*/
	SIM_SCGC4|=SIM_SCGC4_UART0(1); // Clock enabled for UART
	SIM_SOPT2|=SIM_SOPT2_UART0SRC(1); // MCGFLLCLK clock selected for UART0
	SIM_SCGC5|=SIM_SCGC5_PORTA_MASK; // clock enabled for PORTA
	/*UART0 configuration*/
	PORTA_PCR1|=PORT_PCR_MUX(2); //TX of UART0 functionality is used
	PORTA_PCR2|=PORT_PCR_MUX(2); //RX of UART0 functionality is used
	UART0_C2 = BIT0; // transmitter , receiver disabled
	UART0_C1 = BIT0; // 8-bit data mode , no parity
//	UART0_C1|=UART0_C1_LOOPS_MASK; //loop back mode (set to see if data received is same , not needed)
	/* baud setting*/
    UART0_BDH|=UART0_BDH_SBNS(0);// one stop bit selected
   // UART0_BDH =((baudset>>8)&UART_BDH_SBR_MASK);  // baud rate register high
    //UART0_BDL =(baudset& UART_BDL_SBR_MASK);      // baud rate register low
    UART0_BDH = buffh; //baud rate  high register
    UART0_BDL = buffl; //baud rate low register
    UART0_C4_OSR(15); // setting over sampling ratio for baud rate modulo divisor calculations
    //UART0_C2|=UART_C2_RIE_MASK; //receive interrupt enable
    UART0_C2|=UART_C2_TE_MASK|UART_C2_RE_MASK; // transmit receive enable

    /* transmit buffer */
    tx_buf = (CB_t*)malloc(sizeof(CB_t));
    CB_init(&tx_buf,BUFFER_LEN);

    /* receive buffer */
    rx_buf = (CB_t*)malloc(sizeof(CB_t));
    CB_init(&rx_buf,BUFFER_LEN);
    //__enable_irq();          //
    NVIC_EnableIRQ(UART0_IRQn); // set nvic

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
		// block transmission (wait for send)
	}
	UART0_D=*character;
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
                    // receive blocking (wait till receive data)
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
	if(receivedata==NULL)
	{
		return 0;
	}
	if(length==0)
	{
		return 0;
	}
	for(counter=0;counter<length;counter++) //receive blocking is done in UART_receive
	{
		UART_receive(receivedata+counter);
	}
	return 1;
}

/*@brief : interrupt handler
 * circular buffer integration
 *@ param : no
 *@ return :no
*/

void UART0_IRQHandler()
{
	NVIC_DisableIRQ(UART0_IRQn);// interrupt within interrupt should not be allowed (critical section)
    CB_status flag= CB_is_empty(&tx_buf);
    if((UART0_S1 & UART_S1_TDRE_MASK)&& (flag==!(buf_empty))) //if transmission buffer is not empty & TDRE flag is set
    {
               send_buffer();
    }
    else if (flag==buf_empty)
    {
    	UART0_C2&= ~UART0_C2_TIE_MASK; // disable  transmission interrupt enable if TDRE is 0
    }
    flag = CB_is_empty(&rx_buf);
    if((UART0_S1 & UART_S1_RDRF_MASK)&& (flag==!(buf_full))) // if buffer not full and RDRF is set
    {
               receive_buffer();
    }
    else if(flag==buf_full)
    {
    	UART0_C2 &= ~UART0_C2_RIE_MASK; // disable receive interrupt enable if RDRF is 0
    }
}

/*@brief : send items into transmission buffer
 *@ param : no
 *@ return :no
*/

void send_buffer()
{
	uint8_t removestring[20];
	uint8_t *removeitem;
	removeitem=removestring;
	UART0_D =  CB_buffer_remove_item(&tx_buf,removeitem);
}

/*@brief : receive items from receive buffer
 *@ param : no
 *@ return :no
*/

void receive_buffer()
{
	volatile uint8_t ritem=0;
		ritem = UART0_D;
		CB_buffer_add_item(&rx_buf,ritem);
}







