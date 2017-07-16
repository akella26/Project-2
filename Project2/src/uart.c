#include<uart.h>

void UART_configure()
{
	/* we are going to use UART0 because it has DMA interface function which can be used in project3 */
	/*enabling clocks*/
	SIM_SCGC4|=SIM_SCGC4_UART0(1); // Clock enabled for UART
	SIM_SOPT2|=SIM_SOPT2_UART0SRC(1); // MCGFLLCLK clock selected for UART0
	SIM_SCGC5|=SIM_SCGC5_PORTE_MASK; // clock enabled for PORTE
	/*UART0 configuration*/
	PORTE_PCR20|=PORT_PCR_MUX(4); //TX of UART0 functionality is used
	PORTE_PCR21|=PORT_PCR_MUX(4); //RX of UART0 functionality is used
	UART0_C2 = BIT0; //diable rx, tx
    UART0_BDH|=UART0_BDH_SBNS(0);// one stop bit selected
    sbrate=MCGfreq/(baud*16); //sbr
    UART0_BDH =((sbrate>>8)&UART_BDH_SBR_MASK);  // baud rate register high
    UART0_BDL =(sbrate & UART_BDL_SBR_MASK);      // baud rate register low
    UART0_C2|=UART_C2_RIE_MASK; //enable interrupts
    UART0_C2|=UART_C2_TE_MASK|UART_C2_RE_MASK; // enable interrupts
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
	while(UART0_S1 & UART0_S1_TDRE_MASK==0) // block transmission
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
	if(receivedchar=NULL)
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
