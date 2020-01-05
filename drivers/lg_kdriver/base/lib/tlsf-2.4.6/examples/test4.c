
/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tlsf.h"

int main(void){ 
  int *ptr[100];
  int i;

  for (i=0; i< 100; i++)
    if (!(ptr[i]=tlsf_malloc(1024))){
      printf("Error\n");
      exit(-1);
    }

  for (i=0; i< 100; i++)
    tlsf_free(ptr[i]);

  printf("Test OK\n");

  exit(0);
}

    
	
