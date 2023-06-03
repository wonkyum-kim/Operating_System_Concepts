#include <linux/init.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>

struct task_struct *task;

void iterate_process(void)
{
    for_each_process(task) {
        printk(KERN_INFO "Command: %s\t PID: %d\t State: %d\n", task->comm, task->pid, task->__state);
    }
}

/* This function is called when the module is loaded. */
static int list_init(void)
{
    printk(KERN_INFO "created\n");
    iterate_process();
	  return 0;
}

/* This function is called when the module is removed. */
static void list_exit(void) 
{
    printk( KERN_INFO "removed\n");
}

/* Macros for registering module entry and exit points. */
module_init( list_init );
module_exit( list_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module");
MODULE_AUTHOR("SGG");
