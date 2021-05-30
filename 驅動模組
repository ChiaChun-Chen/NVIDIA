#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
 {
    printk("Enter read function\n");
    
	char gpio[3]={0};
	char userChar[1]={0};
	copy_from_user(gpio, buf, 3);
	printk("gpio(char): %s\n", gpio);
	
	struct file *io;
	loff_t pos = 0;
	mm_segment_t old_fs;
    	old_fs = get_fs();
    	set_fs(get_ds());

	if(strcmp(gpio, "396")==0){
        	io=filp_open("/sys/class/gpio/gpio396/value", O_RDONLY, 0);
	}else if(strcmp(gpio, "255")==0){
        	io=filp_open("/sys/class/gpio/gpio255/value", O_RDONLY, 0);
	}else if(strcmp(gpio, "428")==0){
        	io=filp_open("/sys/class/gpio/gpio428/value", O_RDONLY, 0);
	}else if(strcmp(gpio, "427")==0){
        	io=filp_open("/sys/class/gpio/gpio427/value", O_RDONLY, 0);
	}
	vfs_read(io, userChar, 1, &pos);
    	filp_close(io, NULL);
    	pos=0;
	if(strcmp(gpio, "396")==0){
        	printk("LED1 Status: %s", userChar);
	}else if(strcmp(gpio, "255")==0){
        	printk("LED2 Status: %s", userChar);
	}else if(strcmp(gpio, "428")==0){
        	printk("LED3 Status: %s", userChar);
	}else if(strcmp(gpio, "427")==0){
        	printk("LED4 Status: %s", userChar);
	}
    	
	// send the result
	copy_to_user(buf, userChar, 1);

	set_fs(old_fs);
    return count;
 }

 static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos)
 {
    printk("Enter write function\n");
	printk("iCount=%d\n", iCount);
	printk("W_buf_size: %d\n", (int)count);
	char userChar[10]={0};
	copy_from_user(userChar, buf, count);
	userChar[count-1]='\0';
	printk("userChar(char): %s\n", userChar);
	char gpio[10]={0};
	strncpy(gpio, userChar, 3);
	printk("gpio: %s, len: %ld\n", gpio, strlen(gpio));
	struct file *io;
	loff_t pos = 0;
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(get_ds());

	io=filp_open("/sys/class/gpio/export", O_WRONLY, 0);
	vfs_write(io, gpio, strlen(gpio), &pos);
	filp_close(io, NULL);
	pos=0;

	if(strcmp(gpio, "396")==0){
        	io=filp_open("/sys/class/gpio/gpio396/direction", O_WRONLY, 0);
        	vfs_write(io, "out", 3, &pos);
		filp_close(io, NULL);
		pos=0;
		io=filp_open("/sys/class/gpio/gpio396/value", O_WRONLY, 0);
		vfs_write(io, &userChar[count-2], 1, &pos);
		filp_close(io, NULL);
		pos=0;
	}else if(strcmp(gpio, "255")==0){
		io=filp_open("/sys/class/gpio/gpio255/direction", O_WRONLY, 0);
		vfs_write(io, "out", 3, &pos);
		filp_close(io, NULL);
		pos=0;
		io=filp_open("/sys/class/gpio/gpio255/value", O_WRONLY, 0);
		vfs_write(io, &userChar[count-2], 1, &pos);
		filp_close(io, NULL);
		pos=0;
	}else if(strcmp(gpio, "428")==0){
		io=filp_open("/sys/class/gpio/gpio428/direction", O_WRONLY, 0);
		vfs_write(io, "out", 3, &pos);
		filp_close(io, NULL);
		pos=0;
		io=filp_open("/sys/class/gpio/gpio428/value", O_WRONLY, 0);
		vfs_write(io, &userChar[count-2], 1, &pos);
		filp_close(io, NULL);
		pos=0;
	}else if(strcmp(gpio, "427")==0){
		io=filp_open("/sys/class/gpio/gpio427/direction", O_WRONLY, 0);
		vfs_write(io, "out", 3, &pos);
		filp_close(io, NULL);
		pos=0;
		io=filp_open("/sys/class/gpio/gpio427/value", O_WRONLY, 0);
		vfs_write(io, &userChar[count-2], 1, &pos);
		filp_close(io, NULL);
		pos=0;
	}

	set_fs(old_fs);
	iCount++;
	return count;
    
	//printk("device write\n");
    //printk("%d\n",iCount);
    //printk("W_buf_size: %d\n",(int)count);
    //iCount++;
    //return count;
 }

 static int drv_open(struct inode *inode, struct file *filp)
 {
    printk("Enter Open function\n");
    return 0;
 }

 long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
 {
    printk("Enter I/O Control function\n");
    return 0;
 }

 static int drv_release(struct inode *inode, struct file *filp)
 {
    printk("Enter Release function\n");
    return 0;
 }

 struct file_operations drv_fops =
 {
    read:           drv_read,
    write:          drv_write,
    unlocked_ioctl: drv_ioctl,
    open:           drv_open,
    release:        drv_release,
 };

static int demo_init(void) {
   if (register_chrdev(MAJOR_NUM, "demo", &drv_fops) < 0) 
  {
      printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
      return (-EBUSY);
   }
   printk("<1>%s: started\n", MODULE_NAME);
   return 0;
}
static void demo_exit(void) {
   unregister_chrdev(MAJOR_NUM, "demo");
   printk("<1>%s: removed\n", MODULE_NAME);
}
module_init(demo_init);
module_exit(demo_exit);
