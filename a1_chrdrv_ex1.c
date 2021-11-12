/* Allocating major and minor number
 * we can allocate the major and minor number in two ways:
 * 	Statically
 * 		int register_chrdev_region(dev_t first, unsigned int count, char *name);
 * 		if you wnat to create the dev_t structure variable for your major and minor number
 * 		to get you major number and minor number from dev_t, use below method
 * 		MAJOR(dev_t dev);
 * 		MINOR(dev_t dev);
 * 	Dynamically
 * 		int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);
 *
 * How Application communicate with the hardware device?
 * 	First application will open the device file which is created by device driver which we can create in two ways:
 * 	Manually: mkmod -m 666 /dev/char_device c 246 o
 * 	Automatically:
 * 		Include the header file linux/device.h and linux/kdev_t.h
 * 		create the struct class
 * 			struct class *class_create(struct moduel *owner, const char *name);
 * 		create device with the class
 * 			struct device *device_create(struct *class, struct device *parent, dev_t dev, const char *fmt,..)
 * 	You can destroy the device using device_destroy()
 * 		void device_destroy(struct class *class, dev_t devt);
 */

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

#define mem_size 1024

dev_t dev = 0;
static struct class *dev_class;
static struct cdev my_cdev;
uint8_t *kernel_buffer;

static int __init chr_driver_init(void);
static void __exit chr_driver_exit(void);
static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *filp, char __user *buf, size_t len,loff_t *off);
static ssize_t my_write(struct file *filp, const char *buf, size_t len,loff_t *off);

static struct file_operations fops =
{
	.owner   = THIS_MODULE,
	.read    = my_read,
	.write   = my_write,
	.open    = my_open,
	.release = my_release,
};

static int my_open(struct inode *inode, struct file *file)
{
	//creating memory
	if((kernel_buffer = kmalloc(mem_size,GFP_KERNEL))==0)
	{
		printk(KERN_INFO"Cannot allocate the memory to the kernel\n");
		return -1;
	}
	printk(KERN_INFO"Device File opened\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	kfree(kernel_buffer);
	printk(KERN_INFO"Device file clone\n");
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf,size_t len,loff_t *off)
{
	copy_to_user(buf,kernel_buffer,mem_size);
	printk(KERN_INFO,"Data read : done\n");
	return mem_size;
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	copy_from_user(kernel_buffer,buf,len);
	printk(KERN_INFO"Data is written \n");
	return len;
}

static int __init chr_driver_init(void)
{
	// allocating major number
	if(alloc_chrdev_region(&dev,0,1,"my_dev")< 0)
	{
		printk(KERN_INFO"Cannot allocate the major number\n");
		return -1;
	}
	printk(KERN_INFO"Major %d Minor %d",MAJOR(dev),MINOR(dev));

	//creating a cdev structure
	cdev_init(&my_cdev,&fops);

	//adding character device to the system
	if((cdev_add(&my_cdev,1))<0)
	{
		printk(KERN_INFO "Cannot add the device to the system\n");
	goto r_class;
	}

	//creating struct class
	if((dev_class = class_create(THIS_MODULE,"MYCLASS"))==NULL)
	{
		printk(KERN_INFO "Cannot create the struct class\n");
		goto r_class;
	}

	//creating device
	if((device_create(dev_class,NULL,dev,NULL,"my_device"))==NULL)
	{
		printk(KERN_INFO"Cannot create the device\n");
		goto r_class;
	}
	printk(KERN_INFO"Device driver insert done properly\n");
	return 0;



r_class:
	unregister_chrdev_region(dev,1);
	return -1;

}

void __exit chr_driver_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO"Device driver is removed succesfully\n");
}
module_init(chr_driver_init);
module_exit(chr_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NIKHIL");
MOUDLE_DESCRIPTION("The_character_device_driver");



