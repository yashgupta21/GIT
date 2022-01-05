/***************************************************************************//**
*  \file       driver.c
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
/*User Defined Structure*/
typedef struct 
{
	u_int16_t offset; 
	char *value; 
	u_int8_t value_8;
	u_int16_t value_16;
	u_int32_t value_32; 
	u_int16_t size; 
}recStruct;
recStruct recVariable;
#define IOCTL_WR_FPGA_REGISTER _IOW('a','a',recStruct*)
#define IOCTL_RD_FPGA_REGISTER _IOR('a','b',recStruct*)
dev_t dev = 0;
u_int8_t flag=0,i=0;
u_int16_t *buffer;
u_int8_t newValue_8=10;
u_int16_t newValue_16=100;
u_int32_t newValue_32=1000;
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
	pr_info(KERN_ALERT"Memory Allocation Successful\n");
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
        switch(cmd)
	{
              case IOCTL_WR_FPGA_REGISTER:
                        if( copy_from_user(&recVariable ,(recStruct*)arg, sizeof(recVariable)) )
			{
				pr_err("Data Write : Err!\n");
			}
			pr_info("Size = %d\n",recVariable.size);
			if(recVariable.size == 1)
			{
                        	pr_info("Value = %d ",recVariable.value_8);
			}
			else if(recVariable.size == 2)
                       {
                       	pr_info("Value = %d ",recVariable.value_16);
                       }
			else if(recVariable.size == 4)
                       {
                        	pr_info("Value = %d ",recVariable.value_32);
                                
                       }
                       else if(recVariable.size == 16)
                       {
                        	for( i=0;i<16;i++)
        				{
                				pr_info("%d\n",(*(u_int8_t*)recVariable.value+i));	
        				}
                       }
			break;

		case IOCTL_RD_FPGA_REGISTER:
			if( copy_from_user(&recVariable ,(recStruct*)arg, sizeof(recVariable)) )
			{
				pr_err("Data Write : Err!\n");
			}
			if(recVariable.size == 1)
			{
				recVariable.value_8=newValue_8;
				//memcpy(recVariable.value_8,&newValue_8, sizeof(newValue_8));
                        	if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                        	{
                               	 	pr_err("Data Read : Err!\n");
                        	}
                        	pr_info("Value = %d ",recVariable.value_8);
			}
			else if(recVariable.size == 2)
                       {
                       	recVariable.value_16=newValue_16;
                       	//memcpy(recVariable.value_16,&newValue_16, sizeof(newValue_16));
                             	if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                             	{
                             		pr_err("Data Read : Err!\n");
                             	}
                             	pr_info("Value = %d ",recVariable.value_16);
                       }
			else if(recVariable.size == 4)
                       {
                        	recVariable.value_32=newValue_32;
                        	//memcpy(recVariable.value_32,&newValue_32, sizeof(newValue_32));
				if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                               {
                               	pr_err("Data Read : Err!\n");
                               }
                               pr_info("Value = %d ",recVariable.value_32);
                                
                       }
                       else if(recVariable.size == 16)
                       {
                        	memcpy(recVariable.value,&newValue_8, sizeof(newValue_8));
				if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                               {
                               	pr_err("Data Read : Err!\n");
                               }
                               for( i=0;i<16;i++)
        				{
                				memcpy(recVariable.value+i,&newValue_8, sizeof(newValue_8));
						//pr_info("%d ",(*(u_int8_t*)recVariable.value+i));
						newValue_8=newValue_8+10;
        				}
                       }
                        if( copy_to_user((recStruct*)arg, &recVariable, sizeof(recVariable)) )
                        {
                                pr_err("Data Read : Err!\n");
                        }
                        break;

                default:
                        pr_info("Default\n");
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

