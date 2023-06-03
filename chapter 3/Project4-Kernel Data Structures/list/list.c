#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>

struct color {
	int black;
	struct list_head list;
};

static LIST_HEAD(color_list);

/* This function is called when the module is loaded. */
static int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");

    struct color *red, *orange, *yellow, *green;

    red = kmalloc(sizeof(*red), GFP_KERNEL);
    orange = kmalloc(sizeof(*orange), GFP_KERNEL);
    yellow = kmalloc(sizeof(*yellow), GFP_KERNEL);
    green = kmalloc(sizeof(*green), GFP_KERNEL);

    red->black = 0;
    orange->black = 1;
    yellow->black = 2;
    green->black = 3;

    INIT_LIST_HEAD(&red->list);
    INIT_LIST_HEAD(&orange->list);
    INIT_LIST_HEAD(&yellow->list);
    INIT_LIST_HEAD(&green->list);

    list_add_tail(&red->list, &color_list);
    list_add_tail(&orange->list, &color_list);
    list_add_tail(&yellow->list, &color_list);
    list_add_tail(&green->list, &color_list);
    
    struct color *ptr;
    printk(KERN_INFO "traverse start\n");
    list_for_each_entry(ptr, &color_list, list) {
        printk(KERN_INFO "black: %d\n", ptr->black);
    }
    printk(KERN_INFO "traverse end\n");
    return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void) {

    struct color *ptr, *next;
    list_for_each_entry_safe(ptr, next, &color_list, list) {
        list_del(&ptr->list);
        kfree(ptr);
    }

    // Delete all elements of this list.
    // If success, nothing will be printed out.
    list_for_each_entry(ptr, &color_list, list) {
        printk(KERN_INFO "black: %d\n", &ptr->black);
    }

	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module");
MODULE_AUTHOR("SGG");
