
/**
 * @file project2.c 
 * @brief This file is to be used to project 2.
 *
 * @author Sowmya
 * @date July 15, 2017
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
#include "debug.h"
#include "project2.h"

void project2(void) 
{
	uint8_t str[BUF_LEN],item_removed;
	uint32_t len = 0,i=0;
	uint8_t count_alpha = 0, count_punc = 0, count_misc = 0, count_num = 0;

  	CB_t *rxbuf;
  	rxbuf = (CB_t*)malloc(sizeof(CB_t));
  	status = CB_init(rxbuf,BUF_LEN);
  	
  	if(rxbuf == NULL)
    	status = null_error_circbuff;  
	
    while(1)
    {
    	count_alpha = 0;
    	count_punc = 0;
    	count_misc = 0;
    	count_num = 0;
		printf("\n enter a string num:\n");
		scanf("%s",str);
		i = 0;
		while (*(str+i) != '\0' && i <= USERDEF_RXBUF_FULL) 
		{
	        status = CB_buffer_add_item(rxbuf, *(str+i));
	        printf("\n char added is : %x\n",*(str+i));
	        i++;
	    }
        len = i;
       	for(i = 0 ; i<(len) ; i++)
    	{
    		status = CB_buffer_remove_item(rxbuf, &item_removed);
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
    	printf("\nNumber of alpha %d\n",count_alpha);
    	printf("Number of punctuation %d \n",count_punc);
    	printf("Number of misc %d \n",count_misc);
    	printf("Number of numbers %d \n",count_num); 	
    }
}

    
