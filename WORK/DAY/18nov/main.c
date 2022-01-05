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
int set_8_bitData(u_int8_t fd,char *value)
{
	writeData.value = value;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		exit(-1);
	}
	return 0;
}
int get_8_bitData(u_int8_t fd,char *value)
{
	writeData.value = value;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
	for(int i=0;i<1;i++)
        {
                printf("Value = %d\n",(*(u_int8_t*)writeData.value));
                writeData.value++;
        }
	return 0;
}
int set_16_bitData(u_int8_t fd,char *value)
{
	writeData.value = value;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		exit(-1);
	}
	return 0;
}
int get_16_bitData(u_int8_t fd,char *value)
{
	writeData.value = value;
        printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
	for(int i=0;i<2;i++)
        {
                printf("Value = %d\n",(*(u_int8_t*)writeData.value));
                writeData.value++;
        }
	return 0;
}
int set_32_bitData(u_int8_t fd,char *value)
{
	writeData.value = value;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		exit(-1);
	}
	return 0;
}
int get_32_bitData(u_int8_t fd,char *value)
{
	writeData.value = value;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
	for(int i=0;i<4;i++)
        {
                printf("Value = %d\n",(*(u_int8_t*)writeData.value));
                writeData.value++;
        }
	return 0;
}
int set_16_byteData(u_int8_t fd,char *value)
{
	writeData.value = value;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		exit(-1);
	}
	return 0;
}
int get_16_byteData(u_int8_t fd,char *value)
{
	writeData.value = value;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
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

