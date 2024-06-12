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
