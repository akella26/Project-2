/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include<stdio.h>
#include<stdint.h>

uint32_t baud=115200;
uint16_t sbrate=0;
uint32_t MCGfreq=48000000;
void UART_configure()
{
	/* we are going to use UART0 because it has DMA interface function which can be used in project3 */
	/*first port E should be intialized*/
	SIM_SCGC5|=SIM_SCGC5_PORTE_MASK; // clock enabled for PORTE
	PORTE_PCR20|=PORT_PCR_MUX(4); //TX of UART0 functionality is used
	PORTE_PCR21|=PORT_PCR_MUX(4); //RX of UART0 functionality is used
	/*UART0 configuration*/
	SIM_SCGC4|=SIM_SCGC4_UART0(1); // Clock enabled for UART
	SIM_SOPT2|=SIM_SOPT2_UART0SRC(1); // MCGFLLCLK clock selected for UART0
    sbrate=MCGfreq/(baud*16); //sbr
    UART0_BDH|=UART0_BDH_SBR(sbrate);  // baud rate register high (not getting set)
    UART0_BDL|=UART0_BDL_SBR(sbrate);      // baud rate register low (not getting set)
}

uint8_t UART_send(uint8_t *character)
{
	if(character==NULL)
	{
		return 0;
	}
	if(*character=='\0')
	{
		return 0;
	}
	while(UART0_S1 &UART0_S1_TDRE_MASK==0) // block transmission
	{
	UART0_D=*character;
	}
	return 1;
}

uint8_t UART_send_n(uint8_t *data , uint8_t length)
{
	uint8_t counter=0;
	if(data==NULL)
	{
		return 0;
	}
	if(*data=='\0')
	{
		return 0;
	}
	if(length==0)
	{
		return 0;
	}
	for(counter=0;counter<length;counter--) //transmission blocking is done in UART_send
	{
		UART_send(data+counter);
	}
	return 1;
}

uint8_t UART_receive(uint8_t *receivedchar)
{
	if(receiveddata=NULL)
	{
		return 0;
	}
	if(*receiveddata='\0')
	{
		return 0;
	}
	while(UART0_S1 &UART0_S1_RDRF_MASK==0)
	{
		*receivedchar= UART0_D;
	}
	return 1;
}

uint8_t UART_receive_n(uint8_t *receivedata , uint8_t length)
{
	uint8_t counter=0;
	if(receivedata==NULL)
	{
		return 0;
	}
	if(*receivedata=='\0')
	{
		return 0;
	}
	if(length==0)
	{
		return 0;
	}
	for(counter=0;counter<length;counter--) //transmission blocking is done in UART_send
	{
		UART_receive(receivedata+counter);
	}
	return 1;
}


int main(void)
{
	static int i = 0;
    UART_configure();
    /* Write your code here */

    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {
        i++;
    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
