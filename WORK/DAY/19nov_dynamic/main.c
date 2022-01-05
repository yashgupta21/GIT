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
        u_int8_t fd=0,new=10;
        int size;
	for(int i=1;i<=16;i++)
	{
		value[i-1]=new++;
	}
        printf("\nOpening Driver\n");
        fd = open("/dev/my_device", O_RDWR);
        if(fd < 0)
	{
                printf("Cannot open device file...\n");
                return 0;
        }
        printf("Enter:\n1 for 1 Byte Data\n2 for 2 Byte Data\n3 for 4 Byte Data\n4 for 16 Byte Data\n");
        scanf("%d",&size);
        if(size==1)
        {
        	set_8_bitData(fd,value);
        	get_8_bitData(fd,value);
       	printf("Closing Driver\n");
        }
   	else if(size==2)
        {
        	set_16_bitData(fd,value);
        	get_16_bitData(fd,value);
       	printf("Closing Driver\n");
        }
        else if(size==3)
        {
        	set_32_bitData(fd,value);
        	get_32_bitData(fd,value);
       	printf("Closing Driver\n");
        }
        else if(size==4)
        {
        	set_16_byteData(fd,value);
        	get_16_byteData(fd,value);
       	printf("Closing Driver\n");
        }
      	close(fd);
}	

