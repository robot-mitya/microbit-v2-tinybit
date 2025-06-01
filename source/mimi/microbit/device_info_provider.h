#ifndef DEVICE_INFO_PROVIDER_H
#define DEVICE_INFO_PROVIDER_H

namespace mimi::microbit {

class DeviceInfoProvider {
public:
    static const char* manufacturer();
    static const char* model();
    static const char* serialNumber();
    static const char* hardwareVersion();
    static const char* firmwareVersion();
};

} // namespace mimi::microbit

#endif //DEVICE_INFO_PROVIDER_H
