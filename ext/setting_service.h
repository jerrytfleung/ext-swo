#ifndef EXT_SETTING_SERVICE_H
#define EXT_SETTING_SERVICE_H

#include "service.h"

namespace Solarwinds {
class SettingService : public Service {
  static constexpr int DEFAULT_REFRESH_INTERVAL_MS = 60000;

public:
  SettingService(const std::string &service_key, const std::string &collector,
                 int refresh_interval_ms = DEFAULT_REFRESH_INTERVAL_MS);
  virtual ~SettingService();
  virtual void task() override;

private:
  std::string service_key_;
  std::string collector_;
};
} // namespace Solarwinds

#endif // EXT_SETTING_SERVICE_H