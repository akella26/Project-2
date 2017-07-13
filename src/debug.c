/**
 * @file debug.c 
 * @brief This file is to be used to debug project 1
   This file is used to test the outputs of Project 1 by displaying hex output what array that is passed into the function
 *
 * @author Sowmya Akella
 * @date June 25, 2017
 *
 */

# include "debug.h"

void print_memory(uint8_t * start, uint32_t length)
{
#ifdef VERBOSE	
	uint8_t i;
	if(start == NULL) 
    {
        printf("\nNothing is assigned to start pointer..exiting\n");
        exit(1);
    }
	printf("The hex output of the bytes are :\n");
	for(i=0;i<length;i++)
	{
		printf("%x   ",*(start+i));
	}
	printf("\n");
	
#else
    return;
#endif
}