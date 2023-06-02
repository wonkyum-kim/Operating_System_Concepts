/**
 * make
 * sudo insmod seconds.ko
 * cat /proc/seconds
 * sudo rmmod seconds
 * dmesg
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/jiffies.h>
#include <asm/param.h>

#define BUFFER_SIZE 128

#define PROC_NAME "seconds"

/**
 * Function prototypes
 */
static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);

static struct proc_ops proc_ops2 = {
        .proc_read = proc_read,
};


/* This function is called when the module is loaded. */
static int proc_init(void)
{
        proc_create(PROC_NAME, 0, NULL, &proc_ops2);

        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

	return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void) {
        remove_proc_entry(PROC_NAME, NULL);

        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;

        unsigned long current_jiffies = jiffies;
        char str[20];
        sprintf(str, "%lu", current_jiffies / HZ);

        rv = sprintf(buffer, str);

        // copies the contents of buffer to userspace usr_buf
        if (copy_to_user(usr_buf, buffer, rv)) {
                return -1;
        }

        return rv;
}


/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("SGG");
