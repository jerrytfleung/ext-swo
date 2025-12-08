#ifndef EXT_SETTING_SERVICE_H
#define EXT_SETTING_SERVICE_H

#include "service.h"

namespace Solarwinds {
    class SettingService : public Service {
        static constexpr int DEFAULT_REFRESH_INTERVAL_MS = 60000;
    public:
        SettingService(int refresh_interval_ms = DEFAULT_REFRESH_INTERVAL_MS);
        virtual ~SettingService();
        virtual void task() override;
    };
}

#endif //EXT_SETTING_SERVICE_H