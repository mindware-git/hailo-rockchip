## system info

maverick@maverick-BQM5:~/Documents/hailo-rockchip/temperature$ lsb_release -a
No LSB modules are available.
Distributor ID:	Ubuntu
Description:	Ubuntu 22.04.5 LTS
Release:	22.04
Codename:	jammy

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

In hailort/libhailort/include/hailo/hailort.h
```
/**
 * Get temperature information on the device
 *
 * @param[in] device          A ::hailo_device object.
 * @param[out] temp_info      A @a hailo_chip_temperature_info_t to be filled.
 * @return Upon success, returns ::HAILO_SUCCESS. Otherwise, returns a ::hailo_status error.
 * @note Temperature in Celsius of the 2 internal temperature sensors (TS).
 */
HAILORTAPI hailo_status hailo_get_chip_temperature(hailo_device device, hailo_chip_temperature_info_t *temp_info);
```
