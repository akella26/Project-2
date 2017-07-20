
/**
 * @file memory.c 
 * @brief This file contains memory manipulation function definitions
 * This file contains memory manipulations implementations such as moving memory from one location to another with or without overlap.
 * my_memcopy() corrupts memory if the memory locations overlap, my_memmove() makes sure data isn't corrupted when memories overlap.
 * my_memset() and my_memzero() sets memory to a particular value or zero respectively, reserve_words() dynamically allocates memory blocks, free_words() releases memory
 * @author Sowmya Akella
 * @date June 25, 2017
 *
 */

#include "memory.h"
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
   
    int i;                     /*Temp variable to store source contents*/
    // printf("\n  src is %s\n",src);
    if(src == NULL || dst == NULL) 
    {
        return NULL;
    }
    else 
    {    
        bool overlap = (abs(dst-src)>(length*sizeof(uint8_t))) || (src-dst>0);
        if(overlap)         /* Check for condition where forward copy is acceptable*/
        {
            for(i = 0;i<length;i++)
            {
                *(dst+i) = *(src+i);

            } 
        }        
        else         /*Carry out copy from reverse during overlapping source and destinations*/
        {
            for(i = length-1;i>=0;i--)
            {
                *(dst+i) = *(src+i);

            }
        }
    }
    return dst;
}


uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length)
{
	uint8_t i;
	if(src == NULL || dst == NULL) 
    {
        return NULL;
    }
 	else           /*This does not check for overlap conditions*/
 	{
    	for(i = 0;i<length;i++)
 		{
 			*(dst+i) = *(src+i);
 		}
 	}
 	return dst; 
}

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value)
{ 
	uint8_t i;
	if(src == NULL) 
    {
        return NULL;
    }
 	for(i = 0;i<length;i++)   
 	{
 		*(src+i) = value;
 	}
    return src;
}

uint8_t * my_memzero(uint8_t * src, size_t length)
{
    if(src == NULL) 
    {
        return NULL;
    }
    src = my_memset(src, length, 0);
    return src;
}

uint8_t * my_reverse(uint8_t * src, size_t length)
{
	uint8_t i;
    if(src == NULL) 
    {
        return NULL;
    }
    for(i = 0;i<(length/2);i++)  /*Reverse copy*/
    { 
  		swap((src+i),(src+(length-i)-1));
    }
    return src;
}

void swap(uint8_t*a, uint8_t*b) 
{
	uint8_t temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

uint32_t * reserve_words(size_t length)
{
	uint32_t *ptr = (uint32_t*) malloc(length * sizeof(uint32_t));  //memory allocated using malloc
    if(ptr == NULL)                     
    {
        printf("Error! memory not allocated.");
        return NULL;
    }
    else
    	return ptr;
}

void free_words(uint32_t * src)
{
    if(src == NULL)
    {
        printf("src pointer doesn't point to anything..exiting\n");
        exit(1);
    }
	free(src);
}


