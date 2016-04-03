#include <linux/module.h>

static int kmodule_init(void) {
	return 0;
}

static void kmodule_exit(void) {
}

MODULE_LICENSE("GPL");
module_init(kmodule_init);
module_exit(kmodule_exit);