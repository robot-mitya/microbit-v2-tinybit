#include "device_info_provider.h"

// Global variables for CODAL
extern "C" {
    const char* MICROBIT_MANUFACTURER       = mimi::microbit::DeviceInfoProvider::manufacturer();
    const char* MICROBIT_MODEL              = mimi::microbit::DeviceInfoProvider::model();
    const char* MICROBIT_SERIAL             = mimi::microbit::DeviceInfoProvider::serialNumber();
    const char* MICROBIT_HARDWARE_VERSION   = mimi::microbit::DeviceInfoProvider::hardwareVersion();
    const char* MICROBIT_FIRMWARE_VERSION   = mimi::microbit::DeviceInfoProvider::firmwareVersion();
}

namespace mimi::microbit {

const char* DeviceInfoProvider::manufacturer() {
    return "Robot Mitya";
}

const char* DeviceInfoProvider::model() {
    return "MicroMitya (aka mimi) v1";
}

const char* DeviceInfoProvider::serialNumber() {
    return "000001";
}

const char* DeviceInfoProvider::hardwareVersion() {
    return "1.0";
}

const char* DeviceInfoProvider::firmwareVersion() {
    return "0.1-alpha";
}

} // namespace mimi::microbit
