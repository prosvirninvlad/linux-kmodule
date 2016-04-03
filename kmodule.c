#include <linux/module.h>
#include <linux/proc_fs.h>

int kmodule_proc_open(struct inode *inode, struct file *file) {
	return 0;
}

int kmodule_proc_release(struct inode *inode, struct file *file) {
	return 0;
}

ssize_t kmodule_proc_read(struct file *file, char __user *buf, size_t size, loff_t *offset) {
	return 0;
}

ssize_t kmodule_proc_write(struct file *file, const char __user *buf, size_t size, loff_t *offset) {
	return size;
}

static struct file_operations fops = {
	.open = kmodule_proc_open,
	.read = kmodule_proc_read,
	.write = kmodule_proc_write,
	.release = kmodule_proc_release
};

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