
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

#define POOL_SIZE 1024 * 1024


// Pool size is in bytes.
char pool[POOL_SIZE];

int
main(void){
  int *ptr[100];
  int i, free_mem;
  
  free_mem = init_memory_pool(POOL_SIZE, pool);
  printf("Total free memory= %d\n", free_mem);
  for (i=0; i< 100; i++)
    if (!(ptr[i]=malloc_ex(1024, pool))){
      printf("Error\n");
      exit(-1);
    }
  for (i=0; i< 100; i++)
    free_ex(ptr[i], pool);
 
  destroy_memory_pool(pool);
  printf("Test OK\n");
  exit(0);
}

    
	
