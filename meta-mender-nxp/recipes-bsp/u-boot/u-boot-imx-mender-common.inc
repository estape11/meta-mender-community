FILESEXTRAPATHS:prepend := "${THISDIR}/patches:"

SRC_URI:append:imx8dxlb0-lpddr4-evk = " \
    file://0001-PATCH-conf-for-imx8dxlb0_lpddr4_evk-board-for-Mender.patch \
    file://0001-uboot-cmds-modifications-to-use-Mender-variables.patch \
"

MENDER_UBOOT_CONFIG_SYS_MMC_ENV_PART:imx8dxlb0-lpddr4-evk = "0"
BOOTENV_SIZE:imx8dxlb0-lpddr4-evk = "0x2000"

MENDER_UBOOT_ENV_STORAGE_DEVICE_OFFSET:imx8dxlb0-lpddr4-evk = "0x400000"
MENDER_UBOOT_ENV_STORAGE_DEVICE_OFFSET_2:imx8dxlb0-lpddr4-evk = "0x440000"
MENDER_BOOTENV_TOTAL_ALIGNED_SIZE:imx8dxlb0-lpddr4-evk = "524288"