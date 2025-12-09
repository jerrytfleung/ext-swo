#include "setting_service.h"
#include <iostream>

namespace Solarwinds {
    SettingService::SettingService(int refresh_interval_ms) : Service(refresh_interval_ms) {
        start();
    }

    SettingService::~SettingService() {
        stop();
    }

    void SettingService::task() {
        // task
    }
}