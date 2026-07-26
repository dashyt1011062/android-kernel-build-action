// Copyright (c) 2025-2026 fei_cong(https://github.com/feicong/feicong-course)
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("feicong");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Droid DDK action verification module");
MODULE_VERSION("2.0");

static int __init hello_ko_init(void) {
	pr_info("hello from dddk\n");
	return 0;
}

static void __exit hello_ko_exit(void) {
	pr_info("goodbye from dddk\n");
}

module_init(hello_ko_init);
module_exit(hello_ko_exit);
