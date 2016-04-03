#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>

/* Буфер для хранения "высказываний" */
static const int mesg_max_len = PAGE_SIZE;
static int mesg_cur_len = 0;
static int mesg_next = 0;
static int len_check = 1;
static char *mesg_buf;

static const char *kmodule_proc_en = "kmodule";

static int kmodule_proc_open(struct inode *inode, struct file *file) {
	return 0;
}

static int kmodule_proc_release(struct inode *inode, struct file *file) {
	return 0;
}

static ssize_t kmodule_proc_read(struct file *file, char __user *buf, size_t size, loff_t *offset) {
	
	int len = 0;

	/* Костыль от бесконечного цикла */
	if (len_check) {
		len_check = 0;
	} else {
		len_check = 1;
		return 0;
	}

	if (mesg_next >= mesg_cur_len) {
		mesg_next = 0;
	}

	len = sprintf(buf, "%s\n", &mesg_buf[mesg_next]);
	mesg_next += len;

	return len;

}

static ssize_t kmodule_proc_write(struct file *file, const char __user *buf, size_t size, loff_t *offset) {

	if (size > (mesg_max_len - mesg_cur_len + 1)) {
		return -ENOMEM;
	}

	if (copy_from_user(&mesg_buf[mesg_cur_len], buf, size)) {
		return -EFAULT;
	}

	mesg_cur_len += size;
	mesg_buf[mesg_cur_len - 1] = 0;

	return size;

}

static struct file_operations fops = {
	.open = kmodule_proc_open,
	.read = kmodule_proc_read,
	.write = kmodule_proc_write,
	.release = kmodule_proc_release
};

static int __init kmodule_init(void) {

	proc_create(kmodule_proc_en, 0644, NULL, &fops);

	mesg_buf = (char*) vmalloc(mesg_max_len);

	if (!mesg_buf) {
		remove_proc_entry(kmodule_proc_en, NULL);
		return -ENOMEM;
	}

	memset(mesg_buf, 0, mesg_max_len);
	mesg_cur_len = mesg_next = 0;

	return 0;

}

static void __exit kmodule_exit(void) {
	remove_proc_entry(kmodule_proc_en, NULL);
	vfree(mesg_buf);
}

MODULE_LICENSE("GPL");
module_init(kmodule_init);
module_exit(kmodule_exit);