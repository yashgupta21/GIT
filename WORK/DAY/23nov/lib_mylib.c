#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "header.h"
int set_8_bitData(u_int8_t fd,u_int8_t *value_8)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value =(u_int8_t*)value_8;
	writeData.size = 1;
	printf("Writing To Driver\n\n");
	ret = ioctl(fd,IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;	
	}
	return 0;
}
int get_8_bitData(u_int8_t fd,u_int8_t *value_8)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value =(u_int8_t*)value_8;
	writeData.size = 1;
	printf("Reading From Driver!\n\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
	return 0;
}
int set_16_bitData(u_int8_t fd,u_int16_t *value_16)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value =(u_int8_t*)value_16;
	writeData.size = 2;
	printf("Writing To Driver\n\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}
int get_16_bitData(u_int8_t fd,u_int16_t *value_16)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value =(u_int8_t *)value_16;
	writeData.size = 2;
        printf("Reading From Driver!\n\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
	return 0;
}
int set_32_bitData(u_int8_t fd,u_int32_t *value_32)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value =(u_int8_t*)value_32;
	writeData.size = 4;
	printf("Writing To Driver\n\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}
int get_32_bitData(u_int8_t fd,u_int32_t *value_32)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value =(u_int8_t *)value_32;
	writeData.size = 4;
	printf("Reading From Driver!\n\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
	return 0;
}
int set_16_byteData(u_int8_t fd,u_int8_t *value)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value =(u_int8_t *)value;
	writeData.size = 16;
	printf("Writing To Driver\n\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}
int get_16_byteData(u_int8_t fd, u_int8_t *value)
{
	u_int8_t ret=0;
	dataStruct writeData;
	writeData.value = (u_int8_t *)value;
	writeData.size = 16;
	printf("Reading From Driver!\n\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
	return 0;
}
