#include "setting_service_c_wrapper.h"
#include "setting_service.h"
#include <cstring>

void* Setting_Service_Allocate(char *collector, char *service_key) {
    std::string collector_str = "apm.collector.na-01.cloud.solarwinds.com";
    if (collector != nullptr && std::strlen(collector) > 0) {
        collector_str = collector;
    }
    std::string service_key_str = "token:unknown";
    if (service_key != nullptr && std::strlen(service_key) > 0) {
        service_key_str = service_key;
    }
    auto p = new Solarwinds::SettingService(service_key_str, collector_str);
    if (p != nullptr) {
        return static_cast<void *>(p);
    }
    return nullptr;
}

void Setting_Service_Free(void* service) {
    if (service != nullptr) {
        auto s = static_cast<Solarwinds::SettingService *>(service);
        if (s != nullptr) {
            delete s;
        }
    }
}
