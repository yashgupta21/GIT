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
        char *value;	/* address of data bytes to write/read in FPGA */
        u_int8_t value_8;
        u_int16_t value_16;
        u_int32_t value_32;
        u_int16_t size;	/* Size of data bytes to write/read in FPGA */
}dataStruct;
u_int8_t ret=0;
u_int8_t value_8=200;
u_int16_t value_16=20000;
u_int32_t value_32=2000000;
dataStruct writeData;
#define IOCTL_WR_FPGA_REGISTER _IOW('a','a',dataStruct*)
#define IOCTL_RD_FPGA_REGISTER _IOR('a','b',dataStruct*)
int set_8_bitData(u_int8_t fd,u_int8_t value)
{
	u_int8_t ret=0;
	writeData.value_8 =value_8;
	writeData.size = 1;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;	
	}
	return 0;
}
int get_8_bitData(u_int8_t fd,u_int8_t value)
{
	u_int8_t ret=0;
	writeData.value_8 =value_8;
	//writeData.size = 1;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
	return 0;
}
int set_16_bitData(u_int8_t fd,u_int16_t value)
{
	u_int8_t ret=0;
	writeData.value_16 = value_16;
	writeData.size = 2;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}
int get_16_bitData(u_int8_t fd,u_int16_t value)
{
	u_int8_t ret=0;
	writeData.value_16 =value_16;
	//writeData.size = 2;
        printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                exit(-1);
        }
	return 0;
}
int set_32_bitData(u_int8_t fd,u_int32_t value)
{
	u_int8_t ret=0;
	writeData.value_32 =value_32;
	writeData.size = 4;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}
int get_32_bitData(u_int8_t fd,u_int32_t value)
{
	u_int8_t ret=0;
	writeData.value_32 =value_32;
	//writeData.size = 4;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
	return 0;
}
int set_16_byteData(u_int8_t fd,char *value)
{
	u_int8_t ret=0;
	writeData.value =value;
	writeData.size = 16;
	printf("Writing To Driver\n");
	ret = ioctl(fd, IOCTL_WR_FPGA_REGISTER,&writeData);
	if(ret<0)
	{
		return -1;
	}
	return 0;
}
int get_16_byteData(u_int8_t fd, char *value)
{
	u_int8_t ret=0;
	writeData.value =value;
	//writeData.size = 16;
	printf("Reading From Driver!\n");
	ret = ioctl(fd, IOCTL_RD_FPGA_REGISTER,&writeData);
        if(ret<0)
        {
                return -1;
        }
	return 0;
}
#if 0
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
#endif

int main()
{
	char value[16];
        u_int8_t fd=0,new=10;
        int size,choice;
	for(int i=1;i<=16;i++)
	{
		value[i-1]=new++;
	}
while(1){
        printf("\nOpening Driver\n");
        fd = open("/dev/my_device", O_RDWR);
        if(fd < 0)
	{
                printf("Cannot open device file...\n");
                return 0;
        }
        /*scanf("%d",&size);
	if(size==4){
        set_16_byteData(fd,value);
        for(int i=0;i<16;i++)
        {
               printf("Value = %d\n",(*(u_int8_t*)writeData.value));
               writeData.value++;
        }
        get_16_byteData(fd,value);
        for(int i=0;i<16;i++)
        {
               printf("Value = %d\n",(*(u_int8_t*)writeData.value));
               writeData.value++;
        }
}*/
	//setTriggerPeriod(fd,value);
	//getTriggerPeriod(fd,value);
	printf("Enter 1 for Write and 2 for Read\n");
	scanf("%d",&choice);
	printf("Enter :\n1 for 1 Byte Data\n2 for 2 Byte Data\n3 for 4 Byte Data\n4 for 16 Byte Data\n");
	scanf("%d",&size);

	switch(choice){
	
			case 1:
				if(size==1)
				{
					set_8_bitData(fd,value_8);
					//get_8_bitData(fd,value_8);
					//printf("Value = %d\n",writeData.value_8);
					
					
				}
			   	else if(size==2)
				{
					set_16_bitData(fd,value_16);
					//get_8_bitData(fd,value_16);
					//printf("Value = %d\n",writeData.value_16);
					
					
					
				}
				else if(size==3)
				{
					set_32_bitData(fd,value_32);
					//get_32_bitData(fd,value_32);
					//printf("Value = %d\n",writeData.value_32);
					
					
				}
				else if(size==4)
				{
					set_16_byteData(fd,value);
					/*get_16_byteData(fd,value);
					for(int i=0;i<16;i++)
       				{
               				printf("Value = %d\n",(*(u_int8_t*)writeData.value));
               				writeData.value++;
        				}*/
					
						
				}
				break;
			/*printf("For Read\n");
			printf("Enter :\n1 for 1 Byte Data\n2 for 2 Byte Data\n3 for 4 Byte Data\n4 for 16 Byte Data\n");
			scanf("%d",&choice);*/
			case 2:
				if(size==1)
				{
					
					get_8_bitData(fd,value_8);
					printf("Value = %d\n",writeData.value_8);
					
				}
			   	else if(size==2)
				{
					
					get_16_bitData(fd,value_16);
					printf("Value = %d\n",writeData.value_16);
					
				}
				else if(size==3)
				{
					
					get_32_bitData(fd,value_32);
					printf("Value = %d\n",writeData.value_32);
					
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
				break;
				
	}
	printf("Closing Driver\n");
      	close(fd);
	}
}
