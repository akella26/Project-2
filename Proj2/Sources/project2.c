


/**
 * @file project2.c
 * @brief This file is to be used to project 1.
 *
 * @author Sowmya , Pavani
 * @date July 16 2017
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "circbuf.h"
#include "debug.h"
#include "project2.h"

void project2(void)
{

}
/*Checking no of alphabets in the string*/
void alpha_count(int8_t * src, int32_t length)
{      /* Checking Alpha Count in the string */
  uint8_t count1 = 0;
  uint8_t i=0;
  if(length > 0)
  {
    for(i = 0; i < length; i++)
    {        /* if condition to check for Alphabetical characters */
      if((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z'))
      {
        count1++;
      }
      src++;
    }
  }

}
/*Checking number of punctuations*/
void punct_count(int8_t * src, int32_t length)
{               /* Checking Punctuations  Count in the string */
  uint8_t count2=0;
  uint8_t i;
  if(length > 0)
  {
    for(i = 0; i < length; i++)
    {
      if((int)*src > 33 && (int)*src < 48){                    /* if condition to check for punctuation characters */
        count2++;
      }
      src++;
    }
  }
}
/*Checking no of misc characters*/
void misc_count(int8_t * src, int32_t length)
{
  uint8_t count3=0;
  uint8_t i;
  if(length > 0)
  {
    for(i = 0; i < length; i++)                /* if condition to check for miscelleneous characters */
    {
      if(((int)*src > 0 && (int)*src < 33) || ((int)*src > 59 && (int)*src < 65) || ((int)*src > 90 && (int)*src < 97) || ((int)*src > 120 && (int)*src < 128)){
        count3++;
      }
      src++;
    }
  }
}
/*Checking number of numbers*/
void num_count(int8_t * src, int32_t length)
{          /* Checking Miscellaneous  Count in the string */
  uint8_t count4=0;
  uint8_t i=0;
  if(length > 0)
  {
    for(i = 0; i < length; i++)
    {     /* if condition to check for Numbers */
      if(*src >= '0' && *src <= '9')
      {
        count4++;
      }
      src++;
    }
  }

}


