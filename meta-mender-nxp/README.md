# Mender integration for NXP (i.MX) based boards

The supported and tested boards are:

 - [i.MX 8XLite](https://www.nxp.com/design/development-boards/i-mx-evaluation-and-development-boards/i-mx-8xlite-evaluation-kit:MCIMX8DXL-WEVK) (uSD)


## Dependencies

This layer depends on:

```
URI: https://github.com/Freescale/meta-freescale
branch: master
revision: HEAD
```

```
URI: https://github.com/Freescale/meta-freescale-3rdparty
branch: master
revision: HEAD
```

```
URI: https://github.com/Freescale/meta-freescale-distro
branch: master
revision: HEAD
```

```
URI: https://github.com/mendersoftware/meta-mender.git
layers: meta-mender-core
branch: kirkstone
revision: HEAD
```

```
URI: https://github.com/nxp-imx/meta-imx
branch: langdale-6.1.1-1.0.0
revision: HEAD
```

## Setup resources

The following commands will setup the environment and allow you to build images
that have Mender integrated.

- NXP Sources
```
mkdir mender-nxp && cd mender-nxp
repo init -u https://github.com/nxp-imx/imx-manifest.git \
          -b imx-linux-langdale \
          -m imx-6.1.1-1.0.0.xml
repo sync -j$(nproc)

```

- Mender Sources
```
cd sources
git clone https://github.com/mendersoftware/meta-mender.git \
         -b kirkstone
git clone https://github.com/estape11/meta-mender-community.git \
         -b langdale
cd ..
```

## Build 
- Setup the enviroment
```
MACHINE=imx8dxlb0-lpddr4-evk DISTRO=fsl-imx-wayland source ./imx-setup-release.sh -b build
```

- Add `langdale` in the `LAYERSERIES_COMPAT_mender`:

```bash
vi meta-mender/meta-mender-core/conf/layer.conf
vi meta-mender/meta-mender-demo/conf/layer.conf
```

- Add mender to the bblayers

```bash
bitbake-layers add-layer ../sources/meta-mender/meta-mender-core/
bitbake-layers add-layer ../sources/meta-mender/meta-mender-demo/

```

- Apply the local.conf changes
```bash
cat ../sources/meta-mender-community/templates/local.conf.append >> conf/local.conf
cat ../sources/meta-mender-community/meta-mender-nxp/templates/local.conf.append >> conf/local.conf
cat ../sources/meta-mender-community/meta-mender-nxp/templates/local-sdcard.conf.append >> conf/local.conf
```

- Build
```
bitbake core-image-minimal
```

## Flash the image 
The resources should available in the result deploy folder (`<build_dir>/tmp/deploy/images/imx8dxlb0-lpddr4-evk`)

- Flash the SD card (predefined partitions)
```bash
dd if=core-image-minimal-imx8dxlb0-lpddr4-evk.sdimg | pv | dd of=/dev/<sd_dev> 
```

- Flash the bootloader

The device has to be in `Download Mode` and the USB connected from the OTG-2 to the PC
```bash
uuu -lsusb
```
With the card inserted in the device, flash using the `uuu` tool
```bash
uuu -b sd imx-boot-imx8dxlb0-lpddr4-evk-sd.bin-flash_linux_m4
```

## Boot the board

After flashing:
 1. Turn the board off
 2. Change the BOOT-MODE jumpers to boot into the SD card
 3. Connect the DEBUG cable (micro-usb) to the board
 4. Open a serial program in the host computer (3rd serial device @ 115200 8N1 / Flow Control = NO)
 5. Power on the board
 6. Stop the uboot process (press a key) and reset the env:
    ```bash
    env default -a
    saveenv
    reset
    ```