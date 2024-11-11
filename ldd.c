#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

// https://youtu.be/iSiyDHobXHA?t=15322

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sami Vevari");
MODULE_DESCRIPTION("Basic read loadable kernel module -- following this tutorial (Linux Device Drivers Development Course for Beginners) https://youtu.be/iSiyDHobXHA by Piyush Itankar");

// Version of form [<epoch>:]<version>[-<extra-version>].
MODULE_VERSION("0:1.0-rusty");

static struct proc_dir_entry *custom_proc_node;

static ssize_t pyjama_read(struct file *file_pointer, 
                    char *user_space_buffer, 
                    size_t count, 
                    loff_t *offset) {
    char msg[] = "ack!\n";
    size_t len = strlen(msg);
    int result = -1;
    printk("pyjama read\n");

    if(*offset >= len) {
        return 0;
    }

    result = copy_to_user(user_space_buffer, msg, len);
    *offset += len;

    return len;
}

struct proc_ops driver_proc_ops = {
    .proc_read = pyjama_read
};

static int pyjama_module_init(void) {
    printk("pyjama_module_init: entry\n");

    custom_proc_node = proc_create("pyjama_driver",
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


static void pyjama_module_exit(void) {
    printk("pyjama_module_exit: entry\n");

    proc_remove(custom_proc_node);

    printk("pyjama_module_exit: exit\n");
}

module_init(pyjama_module_init);
module_exit(pyjama_module_exit);
