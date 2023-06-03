#include <linux/init.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <asm/uaccess.h>

void dfs_traverse_tasks(struct task_struct *task)
{
    struct task_struct *child;
    struct list_head *list;

    // Print out this task's informations
    printk("Command: %s\t PID: %d\t State: %d\n", task->comm, task->pid, task->__state);

    /**
     * list: A loop cursor
     * &task->children: A list of children of the current task.
    */
    list_for_each(list, &task->children) {
        // We can get `child` task from `list`
        child = list_entry(list, struct task_struct, sibling);
        dfs_traverse_tasks(child);
    }
}


/* This function is called when the module is loaded. */
static int list_init(void)
{
    printk(KERN_INFO "created\n");
    dfs_traverse_tasks(&init_task);
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
