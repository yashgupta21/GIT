/***************************************************************************//**
*  \file       main.c
*
*  \details    Userspace application to test the Device driver
*
*  \author     Yash Gupta
*
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "header.h"
int main()
{
	char value[16];
	u_int8_t value_8=20;
 	u_int16_t value_16=200;
	u_int32_t value_32=2000;	
	u_int8_t fd=0,new=10;
        int size,choice;
	for(u_int8_t i=1;i<=16;i++)
	{
		value[i-1]=new++;
	}
        while(1)
	{
        	printf("\nOpening Driver\n");
        	fd = open("/dev/my_device", O_RDWR);
        	if(fd < 0)
		{
                	printf("Cannot open device file...\n");
                	return 0;
        	}
		printf("Enter 1 for Write and 2 for Read\n");
		scanf("%d",&choice);
		printf("Enter :\n1 for 1 Byte Data\n2 for 2 Byte Data\n3 for 4 Byte Data\n4 for 16 Byte Data\n");
		scanf("%d",&size);
		switch(choice)
		{
	
			case 1:
				if(size==1)
				{
					set_8_bitData(fd,value_8);				
				}
			   	else if(size==2)
				{
					set_16_bitData(fd,value_16);
				}
				else if(size==3)
				{
					set_32_bitData(fd,value_32);
				}
				else if(size==4)
				{
					set_16_byteData(fd,value);
				}
				break;
			case 2:
				if(size==1)
				{
					get_8_bitData(fd,value_8);
					printf("Value = %d\n",*((u_int8_t *)writeData.value));
				}
			   	else if(size==2)
				{
					get_16_bitData(fd,value_16);
					printf("Value = %d\n",(*(u_int16_t*)writeData.value));
				}
				else if(size==3)
				{
					get_32_bitData(fd,value_32);
					printf("Value = %d\n",(*(u_int32_t*)writeData.value));
				}
				else if(size==4)
				{
					get_16_byteData(fd,value);
					for(int i=0;i<16;i++)
       					{
               					printf("Value = %d\n",(*(u_int8_t*)writeData.value));
               					writeData.value++;
        				}
				}
				break;
			default :
				printf("Wrong Choice\n");
				break;
				
		}
		printf("Closing Driver\n");
		close(fd);
	}
}

