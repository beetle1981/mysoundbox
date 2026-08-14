# Rockchip RK3399 hexa core 2GB/4GB RAM SoC GBE eMMC USB3 USB-C WiFi/BT
BOARD_NAME="XL-WZB211"
BOARDFAMILY="rockchip64"
#BOOTCONFIG="../../../../../../userpatches/config/u-boot/configs/xl-wzb211-rk3399_defconfig"
BOOTCONFIG="xl-wzb211-rk3399_defconfig"
BOOT_FDT_FILE="rockchip/rk3399-xl-wzb211.dtb"
KERNEL_TARGET="current,edge"
DEFAULT_CONSOLE="serial"
BUILD_MINIMAL="yes"
FULL_DESKTOP="no"
ASOUND_STATE="asound.state.rt5651"
BOOTBRANCH_BOARD="tag:v2025.04"
BOOTPATCHDIR="u-boot-rockchip64-v2025.04"
#BOOTPATCHDIR="none"
KERNELPATCHDIR="kernel-xl-wzb211"
#KERNELBRANCH="tag:v6.12"


#KERNEL_GIT=shallow
KERNEL_GIT=full
