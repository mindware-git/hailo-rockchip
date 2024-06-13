# hailo-rockchip
Install hailo driveron rockcihp board.

## reference
https://tlab.hongo.wide.ad.jp/2024/03/04/hailo-8-edge-ai-accelerator-deployment-guide/  
https://community.hailo.ai/t/cant-install-hailo-pci-driver/117/5  
https://community.hailo.ai/t/how-could-i-install-the-hailort-driver-into-rockchip-device-such-as-rk3588/124/2  

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
## install source & header
```
sudo apt update
sudo apt install adduser apt-utils bash-completion bash bc bison \
build-essential ca-certificates cmake coreutils cpio curl device-tree-compiler \
dkms gcc less g++ vim util-linux python3-dev python python-dev \
flex make
```

## install linux header
unzip linux header from vendor.  
```
unzip linux-headers-4.19.232.zip
sudo cp -r linux-headers-4.19.232 /usr/src/
sudo ln -s /usr/src/linux-headers-$(uname -r) /lib/modules/$(uname -r)/build
```

## Install driver using source
*warning: do not install dkms! It will not boot.*
sudo make install_dkms -> This is really problem.

```
git clone https://github.com/hailo-ai/hailort-drivers.git && cd hailort-drivers
cd linux/pcie
make all
sudo make install
sudo modprobe hailo_pci
```

## install firmware & udev rule
excute script ./download_firmware.sh to download hailo8 firmware bin.  
```
sudo mv hailo8_fw.4.xx.0.bin /lib/firmware/hailo/hailo8_fw.bin 
sudo cp 51-hailo-udev.rules /etc/udev/rules.d/
```
## Attempt 1
벤더사에서 받은 커널 헤드를 기반으로 빌드 성공.  
처음 dkms 를 이용하여 부팅을 시도하였더니 rockchip kernel이라는 로고만 뜨고 부팅이 안됨.  
pcie를 보드에서 제거하니 다시 부팅이 되기 시작했음.  
이상하다 생각해서 dkms를 제거하였더니 pcie 장착 후에도 부팅이 되기 시작.  

## Attempt 2
앞에서 시도로 커널 드라이버가 무언가 잘못되고 있다는 것을 직감했음.  
그래서 dkms 후 부팅이 아니라 modprobe로 run-time 로드를 시도해봄.  
*맨 처음 modprobe 시 /dev/halio 라는 노드가 장착 되었었음.*  
따라서 성공한 줄 알고 재부팅 하였으나 그떄 부터 노드도 보이지 않고, 모듈이 적재만 될 뿐 아무런 반응이 없음.  
첨부된 test.log 를 보면 마지막 부분에 펌웨어도 정상적으로 존재하나, 
```
[   86.730303] hailo_pci: loading out-of-tree module taints kernel.
[   86.734832] hailo: Init module. driver version 4.17.1
```
만 나오고 아무런 반응이 없음.  
init exit 로그만 나올 뿐 실제로 char 노드가 붙지 않는 것으로 예상 됨.

## 결론
아마 커널에서 pcie 에서 불안전하게 돌아가던 드라이버가 최초 적재 되고 난 후,
펌웨어간의 통신 중 무언가 에러가 나서 이후로는 작동이 안된다고 추론 중.
실제 dmesg에서 pcie 관련 에러가 많이 나오는 것으로 보이고,  
부팅 자체가 안되는 것은 시리얼 케이블을 이용해서 부팅로그를 보면 더 자세히 알 수 있을 듯.  

## Old history

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
Ubuntu에 제공되는 헤더가 없음 따라서 벤더에게서 받아야함  

Get linux header from vendor  
벤더에게서 받은 헤더 설치  
`sudo dpkg -i linux-headers-4.19.232_4.19.232-86_arm64.deb`  

명령어 설명
벤더에게서 받은 헤더가 불완전함. 따라서 다시 스크립트를 이용해야함.  
su - 는 root로 가는 명령어이다. 비밀번호는 root  
이후 헤더 조정을 위한 make 명령어들  
```
su -
cd /usr/src/linux-headers-$(uname -r)
make headers_check
make headers_install
make scripts
```
*여기서도 에러가 발생함.*  
missing file들이 존재함.  

심볼릭 링크를 제공해주어서 및에서 hailort-driver에서 접근할 수 있게 해줌.  
`sudo ln -s /usr/src/linux-headers-$(uname -r) /lib/modules/$(uname -r)/build`


