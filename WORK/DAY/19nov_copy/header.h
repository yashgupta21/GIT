typedef struct 
{
        u_int16_t offset;	/* FPGA BAR memory offset */
        char *value;		/* address of data bytes to write/read in FPGA */
        u_int16_t size;	/* Size of data bytes to write/read in FPGA */
}dataStruct;
#define IOCTL_WR_FPGA_REGISTER _IOW('a','a',dataStruct*)
#define IOCTL_RD_FPGA_REGISTER _IOR('a','b',dataStruct*)
int set_8_bitData(u_int8_t fd,u_int8_t *value);
int get_8_bitData(u_int8_t fd,u_int8_t *value);
int set_16_bitData(u_int8_t fd,u_int16_t *value);
int get_16_bitData(u_int8_t fd,u_int16_t *value);
int set_32_bitData(u_int8_t fd,u_int32_t *value);
int get_32_bitData(u_int8_t fd,u_int32_t *value);
int set_16_byteData(u_int8_t fd,char *value);
int get_16_byteData(u_int8_t fd,char *value);
