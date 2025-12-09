#include "setting_service.h"
#include <iostream>
#include <iostream>

namespace Solarwinds {
    SettingService::SettingService(const std::string& service_key, const std::string& collector, int refresh_interval_ms) : Service(refresh_interval_ms), service_key_(service_key), collector_(collector) {
        start();
    }

    SettingService::~SettingService() {
        stop();
    }

    void SettingService::task() {
        // task
        std::cout << collector_ << ", " << service_key_ << std::endl;
    }
}