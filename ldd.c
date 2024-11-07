#include <linux/proc_fs.h>

// https://youtu.be/iSiyDHobXHA?t=15322

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sami Vevari");
MODULE_DESCRIPTION("Basic read loadable kernel module -- following this (Linux Device Drivers Development Course for Beginners) https://youtu.be/iSiyDHobXHA tutorial by Piyush Itankar");


static struct proc_dir_entry *custom_proc_node;

ssize_t (*proc_read)(struct file *, char __user *, size_t, loff_t *);

ssize_t pyjama_read(struct file *, char __user *, size_t, loff_t *) {
    printk("pyjama read\n");
    return 0;
}

struct proc_ops driver_proc_ops = {

};

static int pyjama_module_init(void) {
    printk("pyjama_module_init: entry\n");

    custom_proc_node = proc_create("pyjama_diver",
                                    0,
                                    NULL,
                                    &driver_proc_ops
    );

    if(custom_proc_node == NULL) {
        printk("pyjama_module_init: error\n");
        return -1;
    }

    printk("pyjama_module_init: exit\n");

    return 0;
}

