#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x465ae224, "module_layout" },
	{ 0xef843552, "rtdm_dev_unregister" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xda2282ff, "rtdm_dev_register" },
	{ 0xcd87b1c6, "rtdm_sem_init" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xc136d49a, "rtdm_sem_down" },
	{ 0xb569241f, "rtdm_sem_up" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "DF2FF4C2CDF1B29D5B5929F");
