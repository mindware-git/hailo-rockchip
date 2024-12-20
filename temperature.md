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
