#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
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
__used
__attribute__((section("__versions"))) = {
	{ 0xf230cadf, "module_layout" },
	{ 0xff178f6, "__aeabi_idivmod" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0x97255bdf, "strlen" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xe851e37e, "gpio_to_desc" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0xd697e69a, "trace_hardirqs_on" },
	{ 0x526c3a6c, "jiffies" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x5f754e5a, "memset" },
	{ 0x7c32d0f0, "printk" },
	{ 0xf720264e, "gpiod_direction_input" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x61651be, "strcat" },
	{ 0xdb7305a1, "__stack_chk_fail" },
	{ 0xfe990052, "gpio_free" },
	{ 0x4f68e5c9, "do_gettimeofday" },
	{ 0xc04ebd1, "gpiod_to_irq" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x924948ef, "gpiod_get_raw_value" },
	{ 0xec3d2e1b, "trace_hardirqs_off" },
	{ 0xc1514a3b, "free_irq" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "856DCE22F44D355F62DBC4C");
