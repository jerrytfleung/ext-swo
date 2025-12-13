#ifndef EXT_SETTING_SERVICE_H
#define EXT_SETTING_SERVICE_H

#include "service.h"
#include <mutex>
#include <string>

namespace Solarwinds {
class SettingService : public Service {
  static constexpr int DEFAULT_REFRESH_INTERVAL_MS = 600000;

public:
  SettingService(const std::string &service_key, const std::string &collector,
                 int refresh_interval_ms = DEFAULT_REFRESH_INTERVAL_MS);
  virtual ~SettingService();
  virtual void task() override;
  std::string getSetting();

private:
  std::string service_key_;
  std::string collector_;
  std::string hostname_;
  std::string service_name_;
  std::mutex setting_mutex_;
  std::string setting_;
};
} // namespace Solarwinds

#endif // EXT_SETTING_SERVICE_H