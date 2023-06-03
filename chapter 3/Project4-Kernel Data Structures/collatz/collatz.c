#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <linux/moduleparam.h>
#include <asm/uaccess.h>

static int start = 25;

module_param(start, int, 0);

struct collatz {
	int num;
	struct list_head list;
};

static LIST_HEAD(sequence);

/* This function is called when the module is loaded. */
static int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    while (start) {
        struct collatz *temp;
        temp = kmalloc(sizeof(*temp), GFP_KERNEL);
        temp->num = start;
        INIT_LIST_HEAD(&temp->list);
        list_add_tail(&temp->list, &sequence);
        if (start == 1) {
            break;
        } else if (start % 2 == 0) {
            start >>= 1;
        } else {
            start = start * 3 + 1;
        }
    }
    
    struct collatz *ptr;
    printk(KERN_INFO "traverse start\n");
    list_for_each_entry(ptr, &sequence, list) {
        printk(KERN_INFO "%d ", ptr->num);
    }
    printk(KERN_INFO "traverse end\n");
    return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void) {

    struct collatz *ptr, *next;
    list_for_each_entry_safe(ptr, next, &sequence, list) {
        list_del(&ptr->list);
        kfree(ptr);
    }

    // Delete all elements of this list.
    // If success, nothing will be printed out.
    list_for_each_entry(ptr, &sequence, list) {
        printk(KERN_INFO "%d ", &ptr->num);
    }

	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module");
MODULE_AUTHOR("SGG");
