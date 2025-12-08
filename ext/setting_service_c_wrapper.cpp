#include "setting_service_c_wrapper.h"
#include "setting_service.h"

void* Setting_Service_Allocate() {
    auto p = new Solarwinds::SettingService();
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