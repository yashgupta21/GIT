#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>

#define MEM_SIZE 1024
dev_t dev=0;
uint8_t *kernal_buffer;
static struct cdev my_cdev;
static struct class *dev_class=NULL; 
static int __init char_driver_init(void);
static void __exit char_driver_exit(void);
static int my_open(struct inode *inode,struct file *file);
static int my_release(struct inode *inode,struct file *file);
static ssize_t my_read(struct file *filep,char *buffer,size_t len,loff_t *offset);
ssize_t my_write(struct file *, const char *, size_t, loff_t *);
static struct file_operations fops=
{
	.owner		= THIS_MODULE,
	.read		= my_read,
	.write		= my_write,
	.open		= my_open,
	.release 	= my_release,
};
static int my_open(struct inode *inode,struct file *file)
{
	if((kernal_buffer=kmalloc(MEM_SIZE,GFP_KERNEL))==NULL)
	{
		printk(KERN_ALERT"Cannot allocate Memory to Kernal\n");
		return -1;
	}
	printk(KERN_ALERT"Device File Opened Succesfully\n");
	return 0;
}
static int my_release(struct inode *inode,struct file *file)
{
	kfree(kernal_buffer);
	printk(KERN_ALERT"Device File Closed Succesfully\n");
	return 0;
}
ssize_t my_read(struct file *filep,char *buffer,size_t len,loff_t *offset)
{
	copy_to_user(buffer,kernal_buffer,len);
	printk(KERN_ALERT"Device File Read Succesfully");
	return MEM_SIZE;
}
ssize_t my_write(struct file *filep,const char *buffer,size_t len,loff_t *offset)
{
        copy_from_user(kernal_buffer,buffer,len);
        printk(KERN_ALERT"Device File Written Succesfully");
        return len;
}
static int __init char_driver_init(void)
{
	/*Major number alllocation*/
	if((alloc_chrdev_region(&dev,0,1,"My_Dev"))<0)
	{
		printk(KERN_ALERT"Cannot Allocate major Number\n");
		return -1;
	}

	printk(KERN_ALERT"MAJOR = %d MINOR = %d \n",MAJOR(dev),MINOR(dev));
	
	/*Cdev Stucture*/
	cdev_init(&my_cdev,&fops);

	/*Adding Character Device To the System*/
	if((cdev_add(&my_cdev,dev,1))<0)
	{
		printk(KERN_ALERT"Cannot add Device\n");
		goto r_class;
	}

	/*Create Stuct class*/
	if((dev_class=class_create(THIS_MODULE,"my_device"))==NULL)
	{
		printk(KERN_ALERT"Cannot Create Class\n");
		goto r_class;
	}
	/*Create Device*/
	if((device_create(dev_class,NULL,dev,NULL,"my_device"))==NULL)
	{
		printk(KERN_ALERT"Cannot Create Device");
		goto r_device;
	}

	printk(KERN_ALERT"DEVICE inserted\n");

r_class:
	unregister_chrdev_region(dev,1);
	return -1;

r_device:
	class_destroy(dev_class);
	return 0;
}

void __exit char_driver_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_ALERT"Device driver removed succesfully\n");

}

module_init(char_driver_init);
module_exit(char_driver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("YASH_GUPTA");
MODULE_DESCRIPTION("Character Device Driver");
