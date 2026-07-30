// Copyright (c) 2026
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("dashyt1011062");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Droid DDK KCFI verification module");
MODULE_VERSION("1.0");

static int __init hello_ko_kcfi_init(void)
{
	pr_info("hello from dddk kcfi\n");
	return 0;
}

static void __exit hello_ko_kcfi_exit(void)
{
	pr_info("goodbye from dddk kcfi\n");
}

module_init(hello_ko_kcfi_init);
module_exit(hello_ko_kcfi_exit);
