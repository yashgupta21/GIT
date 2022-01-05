/*******************************************************************************
*  \file       Driver.c
*
*  \details    Simple Linux device driver (IOCTL)
*
*  \author     Yash Gupta
*
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
/*kmalloc()*/
#include <linux/slab.h>
/*Copy to/from User*/
#include <linux/uaccess.h>        
#include <linux/ioctl.h>
typedef struct _data_addr
{
	// TODO: does the following two variables needs to be a pointer?
	uint32_t*	data_cube_address;             /* Data cube address */
	uint32_t*	meta_data_cube_address;        /* Meta data cube address */
	uint8_t		index;                          /* Index of the data cube in list */
	// TODO: add data_cube and meta_data_cube offset
} data_addresses;
data_addresses data;
//#define IOCTL_WR_FPGA_REGISTER _IOW('a','a',data_addresses*)
#define IOCTL_RD_FPGA_REGISTER _IOR('a','b',data_addresses*)
#define IOCTL_SET_DMA_ADDRESS _IOW('a','a',data_addresses*)
dev_t dev = 0;
u_int16_t *buffer;
u_int8_t i=0;
/*u_int8_t flag=0,i=0;
u_int8_t newValue_8=10;
u_int16_t newValue_16=1000;
u_int32_t newValue_32=10000;*/
static struct class *dev_class;
static struct cdev cdev;
/* Function Prototypes*/
static int      __init io_driver_init(void);
static void     __exit io_driver_exit(void);
static int      open(struct inode *inode, struct file *file);
static int      release(struct inode *inode, struct file *file);
static ssize_t  read(struct file *filp, char __user *buf, size_t len,loff_t * off);
static ssize_t  write(struct file *filp, const char *buf, size_t len, loff_t * off);
static long     ioctl(struct file *file, unsigned int cmd, long unsigned int arg );
/* File operation sturcture*/
static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = read,
        .write          = write,
        .open           = open,
        .unlocked_ioctl = ioctl,
        .release        = release,
};
/*This function will be called when we open the Device file*/
static int open(struct inode *inode, struct file *file)
{
	if((buffer=kmalloc(1024,GFP_KERNEL))==NULL)
        {
                pr_info(KERN_ALERT"Cannot allocate Memory to Kernal\n");
                return -1;
        }
	//pr_info(KERN_ALERT"Memory Allocation Successful\n");
        pr_info("Device File Opened...!!!\n");
        return 0;
}
/*This function will be called when we close the Device file*/
static int release(struct inode *inode, struct file *file)
{
        pr_info("Device File Closed...!!!\n");
        return 0;
}
/*This function will be called when we read the Device file*/
static ssize_t read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
        pr_info("Read Function\n");
        return 0;
}
/*This function will be called when we write the Device file*/
static ssize_t write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
        pr_info("Write function\n");
        return len;
}
/*This function will be called when we write IOCTL on the Device file*/
static long ioctl(struct file *file, unsigned int cmd, long unsigned int arg)
{	
	//data_addresses *data =NULL;
	//memset(data,0x00,sizeof(data_addresses));
        switch(cmd)
	{
                case IOCTL_SET_DMA_ADDRESS:
			if( copy_from_user(&data ,(data_addresses *)arg, sizeof(data_addresses)) )
			{
				pr_err("Data Write : Err!\n");
			}
            		pr_info("WELCOME\n");
            		pr_info("%p\n",(data.data_cube_address));
			pr_info("%p\n",(data.meta_data_cube_address));
			pr_info("%d\n",(data.index));
			/*if(recVariable.size == 1)
			{
                        	pr_info("Value = %d ",(*(u_int8_t*)recVariable.value));
			}
			else if(recVariable.size == 2)
			{
                       		pr_info("Value = %d ",(*(u_int16_t*)recVariable.value));
			}
			else if(recVariable.size == 4)
                       	{
                        	pr_info("Value = %d ",(*(u_int32_t*)recVariable.value));
			}
                       	else if(recVariable.size == 16)
                       	{
                        	for( i=0;i<recVariable.size;i++)
        			{
                			pr_info("%d\n",(*(u_int8_t*)recVariable.value+i));	
        			}
                       	}*/
                       	break;

		case IOCTL_RD_FPGA_REGISTER:
			/*if( copy_from_user(&recVariable ,(recStruct*)arg, sizeof(recVariable)) )
			{
				pr_err("Data Write : Err!\n");
			}
			if(recVariable.size == 1)
			{
				memcpy(recVariable.value,&newValue_8,sizeof(newValue_8));
				if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                        	{
                               	 	pr_err("Data Read : Err!\n");
                        	}                        	
			}
			else if(recVariable.size == 2)
                       	{
                       		memcpy(recVariable.value,&newValue_16, sizeof(newValue_16));
                             	if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                             	{
                             		pr_err("Data Read : Err!\n");
                             	}                             		       
		       	}
			else if(recVariable.size == 4)
                       	{
				memcpy(recVariable.value,&newValue_32, sizeof(newValue_32));
				if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                               	{
                               		pr_err("Data Read : Err!\n");
                               	}
                       	}
                       	else if(recVariable.size == 16)
                       	{
                        	memcpy(recVariable.value,&newValue_8, sizeof(newValue_8));
				if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                               	{
                               		pr_err("Data Read : Err!\n");
                               	}
                               	for( i=0;i<recVariable.size;i++)
        			{
                			memcpy(recVariable.value+i,&newValue_8, sizeof(newValue_8));
					newValue_8=newValue_8+10;
        			}
                       	}*/
                       	break;

		default:
                        pr_err("Send correct IOCTL \n");
                        break;
        }
        return 0;
} 
/*Module Init function*/
static int __init io_driver_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "Dev")) <0)
	{
                pr_err("Cannot allocate major number\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
 
        /*Creating cdev structure*/
        cdev_init(&cdev,&fops);
 
        /*Adding character device to the system*/
        if((cdev_add(&cdev,dev,1)) < 0)
	{
            pr_err("Cannot add the device to the system\n");
            goto r_class;
        }
 
        /*Creating struct class*/
        if((dev_class = class_create(THIS_MODULE,"class")) == NULL)
	{
            pr_err("Cannot create the struct class\n");
            goto r_class;
        }
 
        /*Creating device*/
        if((device_create(dev_class,NULL,dev,NULL,"my_device")) == NULL)
	{
            pr_err("Cannot create the Device 1\n");
            goto r_device;
        }
        pr_info("Device Driver Insert...Done!!!\n");
        return 0;
 
r_device:
        class_destroy(dev_class);
r_class:
        unregister_chrdev_region(dev,1);
        return -1;
}
/*Module exit function*/
static void __exit io_driver_exit(void)
{
        device_destroy(dev_class,dev);
        class_destroy(dev_class);
        cdev_del(&cdev);
        unregister_chrdev_region(dev, 1);
        pr_info("Device Driver Remove...Done!!!\n");
}
 
module_init(io_driver_init);
module_exit(io_driver_exit); 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yash Gupta");
MODULE_DESCRIPTION("Simple Linux device driver (IOCTL)");

