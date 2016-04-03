#include <linux/module.h>
#include <linux/proc_fs.h>

static struct file_operations fops;

static int __init kmodule_init(void) {
	proc_create("kmodule", 0644, NULL, &fops);
	return 0;
}

static void __exit kmodule_exit(void) {
	remove_proc_entry("kmodule", NULL);
}

MODULE_LICENSE("GPL");
module_init(kmodule_init);
module_exit(kmodule_exit);