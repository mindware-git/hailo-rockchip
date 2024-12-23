## 요구사항

Hailort를 이용하여 cpp로 된 온도 측정 프로그램을 작성.

## 빌드 방법

```
$ cd temperature
$ ./build.sh
$ ./build/get_temp
```

## system info

```
maverick@maverick-BQM5:~/Documents/hailo-rockchip/temperature$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description: Ubuntu 22.04.5 LTS
Release: 22.04
Codename: jammy

maverick@maverick-BQM5:~/Documents/hailo-rockchip/temperature$ hailortcli -v
HailoRT-CLI version 4.19.0

maverick@maverick-BQM5:~/Documents/hailo-rockchip/temperature$ apt list | grep hailo

WARNING: apt does not have a stable CLI interface. Use with caution in scripts.

golang-github-hailocab-go-hostpool-dev/jammy,jammy 0.0~git20160125.0.e80d13c-1.1 all
hailo-accelerator-integration-tool/now 1.19.0 amd64 [installed,local]
hailort-pcie-driver/now 4.19.0 all [installed,local]
hailort/now 4.19.0 amd64 [installed,local]

/usr/include/hailo/hailort.h
/usr/lib/libhailort.so.4.19.0
/usr/lib/libhailort.so
```
