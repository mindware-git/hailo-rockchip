#include <hailo/hailort.hpp>

#include <iostream>

using namespace hailort;

int main()
{
    auto scan_res = Device::scan_pcie();
    if (!scan_res)
    {
        std::cerr << "Failed to scan pcie_device" << std::endl;
        return scan_res.status();
    }

    hailo_vdevice_params_t params;
    auto status = hailo_init_vdevice_params(&params);
    if (HAILO_SUCCESS != status)
    {
        std::cerr << "Failed init vdevice_params, status = " << status << std::endl;
        return status;
    }

    params.device_count = static_cast<uint32_t>(scan_res->size());
    auto vdevice = VDevice::create(params);
    if (!vdevice)
    {
        std::cerr << "Failed create vdevice, status = " << vdevice.status() << std::endl;
        return vdevice.status();
    }

    auto physical_devices = vdevice.value()->get_physical_devices();
    if (!physical_devices)
    {
        std::cerr << "Failed to get physical devices" << std::endl;
        return physical_devices.status();
    }

    for (auto &physical_device : physical_devices.value())
    {
        auto thermal_res = physical_device.get().get_chip_temperature();
        if (!thermal_res)
        {
            std::cerr << "Failed to get_chip_temperature" << std::endl;
            return thermal_res.status();
        }

        auto temp = thermal_res.value();
        std::cout << "Chip temperature: " << std::endl
                  << "ts0_temperature :" << temp.ts0_temperature << "C" << std::endl
                  << "ts1_temperature :" << temp.ts1_temperature << "C" << std::endl
                  << "sample_count :" << temp.sample_count
                  << std::endl;
    }
}
