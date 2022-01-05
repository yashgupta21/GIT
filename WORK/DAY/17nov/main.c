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
u_int8_t ret=0;
dataStruct writeData;
#define IOCTL_WR_FPGA_REGISTER _IOW('a','a',dataStruct*)
#define IOCTL_RD_FPGA_REGISTER _IOR('a','b',dataStruct*)

int setTriggerPeriod(u_int8_t fd,char *value)
{
	writeData.offset = 300;
	writeData.value = value;
	writeData.size = 16;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		exit(-1);
	}
	return 0;
}

int getTriggerPeriod(u_int8_t fd,char *value)
{
	writeData.value = value;
        writeData.size = 16;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
        printf("The offset is %d\n",writeData.offset);
        //printf("The value is %d\n",(*(u_int16_t *)writeData.value));
        printf("The size is %d\n",writeData.size);
	for(int i=0;i<16;i++)
        {
                printf("Value = %d\n",(*(u_int8_t*)writeData.value));
                writeData.value++;
        }

	return 0;


}

int main()
{
	char value[16];
        u_int8_t fd=0,new=10;
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
       	setTriggerPeriod(fd,value);
	getTriggerPeriod(fd,value);
       	printf("Closing Driver\n");
      	close(fd);
	
}
