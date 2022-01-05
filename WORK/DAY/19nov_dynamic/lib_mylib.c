#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "header.h"
u_int8_t ret=0;
dataStruct writeData;
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
