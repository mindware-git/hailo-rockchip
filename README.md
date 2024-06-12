# hailo-rockchip
Install hailo driveron rockcihp board.

## reference
https://tlab.hongo.wide.ad.jp/2024/03/04/hailo-8-edge-ai-accelerator-deployment-guide/

## When I got the board
```
linux@linux:~$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 20.04.5 LTS
Release:	20.04
Codename:	focal

linux@linux:~$ uname -a
Linux linux 4.19.232 #149 SMP Mon Feb 26 14:06:41 CST 2024 aarch64 aarch64 aarch64 GNU/Linux

linux@linux:~$ hailortcli fw-control identify
[HailoRT] [error] Can't find hailo pcie class, this may happen if the driver is not installed (this may happen if the kernel was updated), or if there is no connected Hailo board
[HailoRT] [error] CHECK_SUCCESS failed with status=HAILO_PCIE_DRIVER_NOT_INSTALLED(64) - Failed listing pcie devices
[HailoRT] [error] CHECK_SUCCESS failed with status=HAILO_PCIE_DRIVER_NOT_INSTALLED(64)
[HailoRT] [error] CHECK_SUCCESS failed with status=HAILO_PCIE_DRIVER_NOT_INSTALLED(64)
[HailoRT CLI] [error] CHECK_SUCCESS failed with status=HAILO_PCIE_DRIVER_NOT_INSTALLED(64)

linux@linux:~$ apt list | grep hailo

WARNING: apt does not have a stable CLI interface. Use with caution in scripts.

golang-github-hailocab-go-hostpool-dev/focal 0.0~git20160125.0.e80d13c-1 all
hailort-pcie-driver/now 4.17.0 all [installed,local]
hailort/now 4.17.0 arm64 [installed,local]

```

## Issue 1
When I got board, there are already installed packages.  
but I can see there is no driver, which is dkms error.  
I tried re-install, they say failed with error.  
`linux@linux:~$ cat /var/log/hailort-pcie-driver.deb.log`
It turns out deb package has bug for no directory, no kernel header.  
So I switch to install using source.  

### Solution for Issue 1
Kenrel version is too old. 4.xx.
hailo-8 driver needs kernel & header for compile.  
But Ubuntu don't have kernel source & header.  
`sudo apt-get install linux-headers-$(uname -r)`
check.  

## Install driver using source
```
git clone https://github.com/hailo-ai/hailort-drivers.git && cd hailort-drivers
cd linux/pcie
make all
sudo make install_dkms
sudo modprobe hailo_pci
```
Now it's clear. Issue 1 & install from source all same warning that we don't have kernel source & header!!!  

## install source & header
```
sudo apt update
sudo apt install adduser apt-utils bash-completion bash bc bison build-essential ca-certificates cmake coreutils cpio curl device-tree-compiler dkms gcc less g++ vim util-linux python3-dev linux-headers-$(uname -r)
```
