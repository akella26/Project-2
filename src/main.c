/**
 * @file main.c 
 * @brief This file is to be used to call Project1 from main
 * This file contains the main() function which is thefirst function to be executed and from here the required project file can be entered
 *
 * @author Sowmya Akella
 * @date June 25, 2017
 *
 */

//#include "project1.h"
#include "project2.h"
#include <stdio.h>

int main()
{
//#ifdef PROJECT1
//	project1();
	printf("\nEntered main\n");
#ifdef PROJECT2
	printf("\nEntered ifdef condition\n");
	project2();
#endif
	return 0;
}
