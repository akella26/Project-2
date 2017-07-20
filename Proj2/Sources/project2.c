


/**
 * @file project2.c
 * @brief This file is to be used to project 2.
 *
 * @author Sowmya , Pavani
 * @date July 16 2017
 *
 */
#include "MKL25Z4.h"
#include <stdio.h>
#include <stdint.h>
#include "circbuf.h"
#include "debug.h"
#include "project2.h"
#include "uart.h"

/*@brief : Project 2 main function with the infinite loop
 *
 *@ param : no
 *@ return :no
*/
void project2(void)
{
  UART_configure();
  /* transmit buffer */
  tx_buf = (CB_t*)malloc(sizeof(CB_t));
  status = CB_init(tx_buf,BUF_LEN);

  /* receive buffer */
  rx_buf = (CB_t*)malloc(sizeof(CB_t));
  status = CB_init(rx_buf,BUF_LEN);
  uint8_t rxbuf_len_check,i=0;

  uint8_t item_removed;
  int32_t count_alpha = 0, count_punc = 0, count_misc = 0, count_num = 0; //

      while(1)
      {
    	  if(rx_buf->count == USERDEF_RXBUF_MAX)
    	  {
    		for(i=0;i<USERDEF_RXBUF_MAX;i++)
    		{
    						status = CB_buffer_remove_item(rx_buf, &item_removed);
    						if((item_removed >= 0x61 && item_removed <= 0x7A) || (item_removed >= 0x41 && item_removed <= 0x5A))
    			      		{
    			        		count_alpha++;
    			      		}
    			      		if(item_removed >= 0x21 && item_removed <= 0x2F)
    			      		{
    			        		count_punc++;
    			      		}
    			      		if((item_removed > 0x00 && item_removed <= 0x20) || (item_removed >= 0x3A && item_removed <= 0x40) || (item_removed >= 0x5B && item_removed <= 0x60) || (item_removed >= 0x7B && item_removed <= 0x7E))
    			      		{
    			        		count_misc++;
    			      		}
    			      		if(item_removed >= 0x30 && item_removed <= 0x39)
    			      		{
    			        		count_num++;
    			      		}
    		}

    		dump_statistics(count_alpha,count_punc,count_misc,count_num);
    	  }
    	  count_alpha = 0;
    	  count_punc = 0;
    	  count_misc = 0;
    	  count_num = 0;
      }
}


/*@brief : dump_statistics into logger
 * data dumping into UART trasmit
 *@ param : count values of all types of characters
 *@ return :no
*/
void dump_statistics(int32_t count_a, int32_t count_p, int32_t count_m, int32_t count_n)
{
	uint8_t item;
	CB_buffer_add_item(tx_buf,0x63); //c
	CB_buffer_add_item(tx_buf,0x6F); //o
	CB_buffer_add_item(tx_buf,0x75); //u
	CB_buffer_add_item(tx_buf,0x6E); //n
	CB_buffer_add_item(tx_buf,0x74); //t
	CB_buffer_add_item(tx_buf,0x5F); //_
	CB_buffer_add_item(tx_buf,0x61); //a
	CB_buffer_add_item(tx_buf,0x3D); //=
	my_itoa(count_a,&item,2);
	CB_buffer_add_item(tx_buf,item); //no of alphabets
	CB_buffer_add_item(tx_buf,count_a); //no of alphabets

	CB_buffer_add_item(tx_buf,0x63); //c
	CB_buffer_add_item(tx_buf,0x6F); //o
	CB_buffer_add_item(tx_buf,0x75); //u
	CB_buffer_add_item(tx_buf,0x6E); //n
	CB_buffer_add_item(tx_buf,0x74); //t
	CB_buffer_add_item(tx_buf,0x5F); //_
	CB_buffer_add_item(tx_buf,0x70); //p
	CB_buffer_add_item(tx_buf,0x3D); //=
	my_itoa(count_p,&item,2);        //no of punctuation

	CB_buffer_add_item(tx_buf,item);
	CB_buffer_add_item(tx_buf,0x63); //c
	CB_buffer_add_item(tx_buf,0x6F); //o
	CB_buffer_add_item(tx_buf,0x75); //u
	CB_buffer_add_item(tx_buf,0x6E); //n
	CB_buffer_add_item(tx_buf,0x74); //t
	CB_buffer_add_item(tx_buf,0x5F); //_
	CB_buffer_add_item(tx_buf,0x6D); //m
	CB_buffer_add_item(tx_buf,0x3D); //=
	my_itoa(count_m,&item,2);        //no of misc

	CB_buffer_add_item(tx_buf,item);
	CB_buffer_add_item(tx_buf,0x63); //c
	CB_buffer_add_item(tx_buf,0x6F); //o
	CB_buffer_add_item(tx_buf,0x75); //u
	CB_buffer_add_item(tx_buf,0x6E); //n
	CB_buffer_add_item(tx_buf,0x74); //t
	CB_buffer_add_item(tx_buf,0x5F); //_
	CB_buffer_add_item(tx_buf,0x6E); //n
	CB_buffer_add_item(tx_buf,0x3D); //=
	my_itoa(count_n,&item,2);        //no of numbers
	CB_buffer_add_item(tx_buf,0x7C); // |

	UART0_C2 |= UART_C2_TIE_MASK; //Calling the transmit interrupt to send data

}

/*@brief : Conversion from integet to ascii
 * circular buffer integration
 *@ param : yes, data, ptr and base
 *@ return :no
*/
void my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
	uint32_t check=data; //data is copied into check to find out the length of the string without affecting data
	uint8_t stringsize=0;
	uint8_t length = 0;
	uint8_t sign=0;      // sign=0 means the given signed integer is positive and sign=1 means the given signed integer is negative
	if(data<0)
	{
		data=-data;  //data is made positive so that calculations become easier , the minus sign is added later on in the code
		sign=1;
    check = data;
	}
	while(check!=0)  //the number is divided by the base until the quotient is zero , this helps in finding out the length of the string
	{
    check=check/base;
    stringsize ++;
	}
	length = stringsize;
	ptr = ptr+stringsize+sign;
 *(ptr)='\0'; //the last byte of the string is NULL
	while(length>0)
  {
		if(data!=0)
		{
		  ptr--;
		}
		if(data%base>=10)
		{
		  *ptr=(data%base)+55;  //this moves the ASCII values of numbers between 10 and 15 into the pointer location
			data=data/base;
		}
		else
		{
		  *ptr=(data%base)+48; //this moves the ASCII values of numbers between 0 and 9 into the pointer location
			 data=data/base;
		}
  length--;
   }
  if (sign==1)
  {
	ptr = ptr-1;
  *ptr=45; //ASCII value of minus sign
  }
  // return(stringsize+sign+1);
}
