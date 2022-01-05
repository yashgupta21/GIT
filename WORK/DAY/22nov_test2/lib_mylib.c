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
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t*)value_8;
	writeData->size = 1;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;	
	}
	free(writeData);
	return 0;
}
int get_8_bitData(u_int8_t fd,u_int8_t *value_8)
{
	u_int8_t ret=0;
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t*)value_8;
	writeData->size = 1;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
        printf("Value = %d\n",*((u_int8_t*)writeData->value));
        free(writeData);
	return 0;
}
int set_16_bitData(u_int8_t fd,u_int16_t *value_16)
{
	u_int8_t ret=0;
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t*)value_16;
	writeData->size = 2;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;	
	}
	free(writeData);
	return 0;
}
int get_16_bitData(u_int8_t fd,u_int16_t *value_16)
{
	u_int8_t ret=0;
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t *)value_16;
	writeData->size = 2;
        printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
        printf("Value = %d\n",*((u_int16_t*)writeData->value));
        free(writeData);
	return 0;
}
int set_32_bitData(u_int8_t fd,u_int32_t *value_32)
{
	u_int8_t ret=0;
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t*)value_32;
	writeData->size = 4;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;	
	}
	free(writeData);
	return 0;
}
int get_32_bitData(u_int8_t fd,u_int32_t *value_32)
{
	u_int8_t ret=0;
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t*)value_32;
	writeData->size = 4;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
        printf("Value = %d\n",*((u_int8_t*)writeData->value));
        free(writeData);
	return 0;
}
int set_16_byteData(u_int8_t fd,u_int8_t *value)
{
	u_int8_t ret=0;
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t*)value;
	writeData->size = 16;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;	
	}
	free(writeData);
	return 0;
}
int get_16_byteData(u_int8_t fd, u_int8_t *value)
{
	u_int8_t ret=0;
	dataStruct *writeData=NULL;
	writeData=(dataStruct*)malloc(sizeof(dataStruct));
	writeData->value =(u_int8_t*)value;
	writeData->size = 16;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
 
        for(int i=0;i<16;i++)
       	{
               	printf("Value = %d\n",(*(u_int8_t*)writeData->value));
               	writeData->value++;
        	}
        free(writeData);
	return 0;
}
