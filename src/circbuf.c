# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include "circbuf.h"

/* Function to initialize the circular buffer*/
CB_status CB_init(CB_t * buf_pointer,uint8_t length)
{
	buf_pointer->length = length;
	buf_pointer->head = 0;
	buf_pointer->tail = 0;
	buf_pointer->count = 0;
	buf_pointer->buffer = (uint8_t*)calloc(length,sizeof(uint8_t));

	if(!buf_pointer)
		status = success;	
	else 
	{
		status = null_error;
		return status;
	}
	return status;
}
/*Function to add an item to the circular buffer*/
CB_status CB_buffer_add_item(CB_t * buf_pointer, uint8_t new_item)
{
	status = CB_is_full(buf_pointer);
    if(status == buf_full)
    	return status;
    else
    {
	buf_pointer->buffer[buf_pointer->head] =  new_item;
	(buf_pointer->count)++;
	status = success;
        if((buf_pointer->head+1)>(buf_pointer->length-1))
        			buf_pointer->head=0;   
        else 
        	buf_pointer->head++;
    }    
    return status;
}

/*Function to remove an item from the circular buffer*/
CB_status CB_buffer_remove_item(CB_t * buf_pointer,uint8_t * item_removed)
{
	status = CB_is_empty(buf_pointer);
	if(status == buf_empty)
		return status;
	else
	{
	*item_removed = buf_pointer->buffer[buf_pointer->tail];
	buf_pointer->buffer[buf_pointer->tail]=0;
	(buf_pointer->count)--;
	status = success;
        if((buf_pointer->tail+1)>(buf_pointer->length-1))
        			buf_pointer->tail=0;   
        else 
        	buf_pointer->tail++;
    }        
    return status;
}
/*Function to check if the circular buffer is full*/
CB_status CB_is_full(CB_t * buf_pointer)
{
	if((buf_pointer->head == buf_pointer->tail) && buf_pointer->count != 0)
	{
		status = buf_full;
		return status;
	}
	else 
	{
		status = success;
		return status;
	}

}
/*Function to check of the circular buffer is empty*/
CB_status CB_is_empty(CB_t * buf_pointer)
{
	if((buf_pointer->head == buf_pointer->tail) && buf_pointer->count == 0)
	{
		status = buf_empty;
		return status;
	}
	else 
	{
		status = success;
		return status;
	}
}
/*Function to peek into the circular buffer and check the value stored at a position*/

CB_status CB_peek(CB_t * buf_pointer, uint8_t peek_position,uint8_t * peek_item)
{
	*peek_item = buf_pointer->buffer[peek_position];
	if(peek_item == NULL)
	{
		status = null_error;
		return status;
	}
	else 
	{
		status = success;
		return status;
	}
}

/*Function to deallocate the buffer pointer*/
CB_status CB_destroy(CB_t * buf_pointer)
{
	free((void*)buf_pointer->buffer);
	status = free_success;
	return status;
}


