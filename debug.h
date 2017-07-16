
/**
 * @file debug.h 
 * @brief This is the header file required to execute the debug.c file
 * This file contains the standard libraries and function definition of print_memory() required for the debugging
 *
 * @author Sowmya Akella
 * @date June 25, 2017
 *
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

/*
Prints the contents of the memory used for debugging purpose
Input - Array start address and length
Returns - None
*/
void print_memory(uint8_t * start, uint32_t length);

#endif /* __DEBUG_H__ */