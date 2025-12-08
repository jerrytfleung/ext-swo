#include "setting_service.h"

namespace Solarwinds {
    SettingService::SettingService(int refresh_interval_ms) : Service(refresh_interval_ms) {
        task();
        start();
    }

    SettingService::~SettingService() {
        stop();
    }

    void SettingService::task() {
        // task
    }
}