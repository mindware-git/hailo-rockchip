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
sudo apt install adduser apport apt-transport-https apt-utils apt atop base-files base-passwd bash-completion bash bc bcache-tools binfmt-support bison bluez bsdutils btrfs-progs build-essential byobu ca-certificates chromium-browser cloud-guest-utils cloud-initramfs-copymods cloud-initramfs-dyn-netconf cmake console-setup-linux console-setup coreutils cpio cron curl dash dbus-x11 dbus debconf-i18n debconf debianutils debootstrap device-tree-compiler diffutils dirmngr distro-info-data distro-info dkms dmidecode dmsetup dosfstools dpkg dvb-tools e2fsprogs eject ethtool exfat-fuse fake-hwclock fakeroot fdisk ffmpeg findutils flex fonts-ubuntu-console fwupd g++-9 gcc-12-base gcc-9 gcc gdisk gir1.2-glib-2.0 gir1.2-gtk-3.0 git-lfs git gnupg gpgv grep gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-libav gstreamer1.0-plugins-bad gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-ugly gstreamer1.0-pulseaudio gstreamer1.0-qt5 gstreamer1.0-rockchip1 gstreamer1.0-tools gstreamer1.0-x gzip hostname htop hwinfo i2c-tools ifupdown init-system-helpers init initramfs-tools iotop iproute2 iputils-ping ir-keytable isc-dhcp-client isc-dhcp-common iso-codes kbd keyboard-configuration kmod less libacl1 libapparmor1 libapt-pkg6.0 libargon2-1 libatm1 libattr1 libaudit-common libaudit1 libblkid1 libbpf0 libbsd0 libbz2-1.0 libc-bin libc6-dev libc6 libcairo2-dev libcanberra-pulse libcap-ng0 libcap2-bin libcap2 libcom-err2 libcrypt1 libcryptsetup12 libdb5.3 libdbus-1-3 libdebconfclient0 libdevmapper1.02.1 libdns-export1110 libdvbv5-0 libdvbv5-dev libdvbv5-doc libegl-mesa0 libegl1-mesa-dev libelf-dev libelf1 libestr0 libexpat1 libext2fs2 libfastjson4 libffi8 libfribidi0 libgbm-dev libgcc-s1 libgcrypt20 libgirepository-1.0-1 libgirepository1.0-dev libgl1-mesa-dev libgles2-mesa-dev libglib2.0-0 libglib2.0-data libglx-mesa0 libgmp10 libgnutls30 libgpg-error0 libgssapi-krb5-2 libgstreamer-plugins-bad1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev libhogweed6 libicu70 libidn2-0 libip4tc2 libisc-export1105 libjson-c5 libk5crypto3 libkeyutils1 libkmod2 libkrb5-3 libkrb5support0 liblocale-gettext-perl liblz4-1 liblzma5 libmd0 libmnl0 libmount1 libmpdec3 libncurses6 libncursesw6 libnetplan0 libnettle8 libnewt0.52 libnsl2 libnss-systemd libp11-kit0 libpam-cap libpam-modules-bin libpam-modules libpam-runtime libpam-systemd libpam0g libpcre2-8-0 libpcre3 libpopt0 libprocps8 libpython3-stdlib libpython3.10-minimal libpython3.10-stdlib libreadline8 librga-dev librga2 librist-dev librist4 librockchip-mpp-dev librockchip-mpp1 librockchip-vpu0 libseccomp2 libselinux1 libsemanage-common libsemanage2 libsepol2 libslang2 libsmartcols1 libsqlite3-0 libss2 libssl-dev libssl3 libstdc++6 libsystemd0 libtasn1-6 libtext-charwidth-perl libtext-iconv-perl libtext-wrapi18n-perl libtinfo6 libtirpc-common libtirpc3 libudev1 libunistring2 libuuid1 libv4l-0 libv4l-dev libv4l-rkmpp libv4l2rds0 libv4lconvert0 libwidevinecdm libxml2 libxtables12 libxxhash0 libyaml-0-2 libzmq3-dev libzstd1 linux-rockchip-5.10 lm-sensors locales login logrotate logsave lsb-base lsb-release lshw lsof lvm2 lxd-agent-loader make mali-g610-firmware malirun man-db manpages mawk mdadm media-types mesa-common-dev mesa-utils mesa-vulkan-drivers mmc-utils motd-news-config mount mpv mtd-utils mtools multipath-tools nano ncurses-base ncurses-bin net-tools netbase netcat-openbsd netplan.io networkd-dispatcher ntfs-3g open-iscsi open-vm-tools openssh-client openssh-server openssl p7zip-full parted passwd patch pavucontrol pciutils perl-base pigz pollinate procps pulseaudio python-apt-common python-gi-dev python-is-python3 python2 python3-apt python3-dbus python3-dev python3-gi-cairo python3-gi python3-minimal python3-netifaces python3-pip python3-pkg-resources python3-setuptools python3-virtualenv python3-yaml python3.10-minimal python3.10 python3 qemu-efi qemu-system-arm qemu-user-static qt6-qpa-plugins qt6-wayland qtwayland5 qv4l2 readline-common rfkill rist-tools rockchip-firmware rockchip-mpp-demos rockchip-multimedia-config rsync rsyslog screen sed sensible-utils shared-mime-info snapd software-properties-common sosreport sudo systemd-sysv systemd-timesyncd systemd sysvinit-utils tar tmux tzdata u-boot-rock-5b u-boot-tools ubuntu-advantage-tools ubuntu-desktop ubuntu-drivers-common ubuntu-keyring ubuntu-minimal ucf udev unattended-upgrades update-notifier-common usb-modeswitch-data usb-modeswitch usbutils usrmerge util-linux uuid-runtime v4l-utils vim-common vim-tiny vim virtualenv wget whiptail wireless-regdb wireless-tools wpasupplicant x11-utils xcb xdg-user-dirs xfsprogs xkb-data xterm xxd xz-utils zip zlib1g 
```
