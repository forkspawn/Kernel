#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x972f93ab, "module_layout" },
	{ 0xc8ab5383, "device_destroy" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0xea3c74e, "tasklet_kill" },
	{ 0xbf5b584a, "kthread_stop" },
	{ 0x215f7233, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xad39bb2b, "class_destroy" },
	{ 0xe55e795f, "sysfs_remove_file_ns" },
	{ 0x2b68b15f, "kobject_put" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xf01b5aed, "wake_up_process" },
	{ 0x2831ba2d, "kthread_create_on_node" },
	{ 0x2364c85a, "tasklet_init" },
	{ 0xdc80a8de, "kmem_cache_alloc_trace" },
	{ 0xbdbfaccb, "kmalloc_caches" },
	{ 0x15ba50a6, "jiffies" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x89991a0b, "sysfs_create_file_ns" },
	{ 0x81515fc2, "kobject_create_and_add" },
	{ 0xa93ab294, "kernel_kobj" },
	{ 0x712605e5, "device_create" },
	{ 0x5b54da1d, "__class_create" },
	{ 0xa89d7d2, "cdev_add" },
	{ 0xe3b72f06, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xf9a482f9, "msleep" },
	{ 0xba8fbd64, "_raw_spin_lock" },
	{ 0x9d2ab8ac, "__tasklet_schedule" },
	{ 0xa52e8c96, "pv_ops" },
	{ 0x8427cc7b, "_raw_spin_lock_irq" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0xbcab6ee6, "sscanf" },
	{ 0xc5850110, "printk" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1558804BD7894A4E2ED9687");
