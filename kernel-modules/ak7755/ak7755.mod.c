#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

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

KSYMTAB_DATA(soc_component_dev_ak7755, "_gpl", "");

MODULE_INFO(depends, "snd-soc-core");

MODULE_ALIAS("i2c:ak7755");
MODULE_ALIAS("of:N*T*Cakm,ak7755");
MODULE_ALIAS("of:N*T*Cakm,ak7755C*");
