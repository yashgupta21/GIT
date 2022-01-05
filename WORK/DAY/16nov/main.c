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
typedef struct 
{
        u_int16_t offset;	/* FPGA BAR memory offset */
        char *value;		/* address of data bytes to write/read in FPGA */
        u_int16_t size;		/* Size of data bytes to write/read in FPGA */
}dataStruct;
#define IOCTL_WR_FPGA_REGISTER _IOW('a','a',dataStruct*)
#define IOCTL_RD_FPGA_REGISTER _IOR('a','b',dataStruct*)

int set_trigger_period(u_int8_t fd, u_int16_t triggerPeriod)
{
	u_int8_t ret=0;
	/*dataStruct *writeData=(dataStruct *)malloc(sizeof(dataStruct));	
	if(writeData==NULL)
	{
		printf("Memory Allocation Error!\n");
	}*/
	dataStruct writeData;
	writeData.offset = 300;
	//writeData.value =0;
	writeData.value =(char*)&triggerPeriod;
	//memcpy(writeData.value,&triggerPeriod,sizeof(triggerPeriod));
	writeData.size = sizeof(triggerPeriod);
	printf("Writing Value to Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		exit(-1);
	}
	printf("Reading Value from Driver\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
	printf("The offset is %d\n",writeData.offset);
	printf("The value is %d\n",(*(u_int16_t *)writeData.value));
	printf("The size is %d\n",writeData.size);
	return ret;
}

int main()
{
        u_int8_t fd;
	u_int16_t triggerPeriod=200;
        printf("\nOpening Driver\n");
        fd = open("/dev/my_device", O_RDWR);
        if(fd < 0)
	{
                printf("Cannot open device file...\n");
                return 0;
        }
       	set_trigger_period(fd,triggerPeriod);				
	printf("Closing Driver\n");
      	close(fd);
	
}
