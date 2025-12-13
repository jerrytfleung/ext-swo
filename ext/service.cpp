#include "service.h"

#include "service.h"
#include <chrono>
#include <system_error>
#include <sys/types.h>
#include <unistd.h>
#include "php.h"

using namespace std::chrono_literals;

namespace Solarwinds {
    Service::Service(int interval) : stopping_(false), interval_(interval) {
        init_ = false;
    }

    Service::~Service() {
    }

    void Service::start() {
        try {
            th_ = std::thread([&]() {
                while (true) {
                    std::unique_lock<std::mutex> lock(mutex_);
                    if (cv_.wait_for(lock, interval_ * 1ms, [&]() { return stopping_ || !init_; })) {
                        if (stopping_) {
                            php_printf("SettingService pid: %u Stopping\n", getpid());
                            break;
                        }
                        if (!init_) {
                            init_ = true;
                            php_printf("SettingService pid: %u Init task\n", getpid());
                            task();
                        }
                    } else {
                        php_printf("SettingService pid: %u Time to do the task\n", getpid());
                        task();
                    }
                }
            });
        } catch (const std::system_error& e) {
            php_printf("SettingService pid: %u System error %s\n", getpid(), e.what());
        }
    }
    void Service::stop() {
        try {
            {
                std::unique_lock<std::mutex> lock(mutex_);
                stopping_ = true;
            }
            cv_.notify_all();
            th_.join();
        } catch (const std::system_error& e) {
        }
    }
}