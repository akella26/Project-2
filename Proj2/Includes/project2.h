/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file project2.h 
 * @brief This file is to be used to project 1.
 *
 * @author Sowmya , Pavani
 * @date July 16, 2017
 *
 */
#ifndef __PROJECT2_H__
#define __PROJECT2_H__

#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"

/**
 * @brief function to run project2 materials
 * 
 * This function calls some various simple tests that you can run to test 
 * your code for the project 2. The contents of these functions
 * have been provided. 
 *
 * @return void
 */
void project2();

/*****************************************************************************
* ALPHA_COUNT
* Function prints the number of alphabets in the given input buffer.
* @param start : Source location pointer
* @param length: length of bytes
*
*****************************************************************************/
void alpha_count(int8_t * src, int32_t length);

/*****************************************************************************
* PUNCTUATIONS_COUNT
* Function prints the number of punctuation characters in the given input buffer.
* @param start : Source location pointer
* @param length: length of bytes
*
*****************************************************************************/
void punct_count(int8_t * src, int32_t length);

/*****************************************************************************
* MISCELLANEOUS_COUNT
* Function prints the number of miscellaneous characters in the given input buffer.
* @param start : Source location pointer
* @param length: length of bytes
*
*****************************************************************************/
void misc_count(int8_t * src, int32_t length);

/*****************************************************************************
* NUMERIC_COUNT
* Function prints the number of integers in the given input buffer.
* @param start : Source location pointer
* @param length: length of bytes
*
*****************************************************************************/
void num_count(int8_t * src, int32_t length);

#endif /* __PROJECT2_H__ */
