require recipes-bsp/u-boot/u-boot-imx-mender-common.inc
require recipes-bsp/u-boot/u-boot-mender.inc

MENDER_UBOOT_AUTO_CONFIGURE:imx8dxlb0-lpddr4-evk = "0"

DEPENDS:append = " bc-native "
B = "${WORKDIR}/build"
do_configure[cleandirs] = "${B}"