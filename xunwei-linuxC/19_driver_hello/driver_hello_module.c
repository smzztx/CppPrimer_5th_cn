#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("TX");

static int hello_init(void)
{
    printk(KERN_EMERG "HELLO WORLD init\n");
    return 0;
}

static int hello_exit(void)
{
    printk(KERN_EMERG "HELLO WORLD exit\n");
    return 0;
}

module_init(hello_init);
module_exit(hello_exit);
