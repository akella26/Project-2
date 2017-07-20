/*******************************************************************************
 * @file conversion.c 
 * @brief This file is contains four functions : itoa,atoi ,big endian to little endian and little endian to big endian.
 *
 * @author Sreela Pavani Bhogaraju
 * @date Jun 25,2017
 *
 *
 *****************************************************************************/
#include "conversion.h"
/*
 * @brief - itoa converts integer to a string of ASCII characters and returns the size of the string including the minus and the null          *  terminator 
   Long : Signed integer is converted into the given base and this data is again converted into ASCII and is stored in a string .Then the   *size of the string is returned  
 * @param - 1st argument :the integer which needs to be converted to ASCII , 
 *          2nd argument :the pointer to the ASCII string,
 *          3rd argument :base , the number system into which the given signed integer should be converted into and then converted to ASCII 
 * @return - length of the string including the minus and null terminator
 *
 */

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
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
   return(stringsize+sign+1);
}

/*
 * @brief - atoi converts an ASCII string into a signed integer and returns it  
   Long :   A pointer to an ASCII string is given along with the base and length of the string , the set of ASCII characters are converted     *  back into the signed integer using the base given   
 * @param - 1st argument :the pointer to the ASCII string , 
 *          2nd argument :length of the string,
 *          3rd argument :base , the number system into which the given ASCII string should be converted to a signed integer
 * @return - the signed integer
 *
 */

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
{
 uint8_t i=0,j=0,n=0;
 uint8_t sign=0;
 uint32_t b=1;
 int32_t number=0;
   if(*ptr==45)
   {
   ptr++;
   sign=1;
   digits--;
   }
   for(i=digits-1;i!=0;i--)
   {
     b=1;
     if(*ptr>=65)
      {
      n=*ptr-55;  // n is between A to F
      }
     else
      {
      n=*ptr-48; // n is between 0 to 9   
      } 
     for(j=i-1;j!=0;j--)
     {
     b=b*base;
     }
    number=(n*b)+number;
    digits--;
    ptr++;
   }
   if(sign==1)
   {
   number=-number;
   }
  return(number);
}

/*
 * @brief - big_to_little converts array of data from big endian to little endian representation and returns a non zero value if the           *  conversion fails  
 * @param - 1st argument :pointer to array of data in big endian representation , 
 *          2nd argument :length of the data array,
 * @return - 0 for successful conversion , 1 for NULL pointer and 2 for an empty array 
 */
 
int8_t big_to_little32(uint32_t * data, uint32_t length)
{
int8_t i=length-1;
uint32_t t;
 if(data==NULL)
 {
  return 1;
 }
 if(*data=='\0')
 {
  return 2;
 }
 else
 {
  while(i>0)
  {
   t=*(data+i);
   *(data+i)=*data;
   *data =t;
   data++;
   i=i-2;
  }
 return 0;
 }
}

/*
 * @brief - little_to_big32 converts array of data from little endian to big endian representation and returns a non zero value if *the        conversion fails  
 * @param - 1st argument :pointer to array of data in little endian representation , 
 *          2nd argument :length of the data array,
 * @return - 0 for successful conversion , 1 for NULL pointer and 2 for an empty array 
 */

int8_t little_to_big32(uint32_t * data, uint32_t length)
{
int8_t i=length-1;
uint32_t t;
 if(data==NULL)
 {
  return 1;
 }
 if(*data=='\0')
 {
  return 2;
 }
 else
 {
  while(i>0)
  {
   t=*(data+i);
   *(data+i)=*data;
   *data =t;
   data++;
   i=i-2;
  }
  return 0;
 }
}
