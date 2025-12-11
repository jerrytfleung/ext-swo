#include "setting_service.h"
#include <curl/curl.h>
#include "php.h"

namespace Solarwinds {
    // Callback to write received data into a std::string
    size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userdata) {
        size_t totalSize = size * nmemb;
        std::string* response = static_cast<std::string*>(userdata);
        response->append(contents, totalSize);
        return totalSize;
    }

    SettingService::SettingService(const std::string& service_key, const std::string& collector, int refresh_interval_ms) : Service(refresh_interval_ms), service_key_(service_key), collector_(collector) {
        start();
    }

    SettingService::~SettingService() {
        stop();
    }

    void SettingService::task() {
        auto curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://apm.collector.na-01.cloud.solarwinds.com:443/v1/settings/opentelemetry-lambda-nodejs-experimental-staging-arm64/169.254.29.109");
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            // ssl options
            auto ssl_options = CURLSSLOPT_NATIVE_CA;
            curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, ssl_options);
            // Authorization header
            struct curl_slist *headers = nullptr;
            headers = curl_slist_append(headers, "Authorization: Bearer token:unknown");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            // 10 seconds timeout
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
            // write callback and response body
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            std::string response_body;
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_body);
            auto res = curl_easy_perform(curl);
            curl_slist_free_all(headers);
            if (res != CURLE_OK) {
                php_printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            }
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            if (http_code != 200) {
                php_printf("HTTP request failed with code: %ld\n", http_code);
            } else {
                php_printf("Settings fetched successfully: %s\n", response_body.c_str());
            }
            curl_easy_cleanup(curl);
        } else {
            php_printf("Failed to initialize CURL\n");
        }
    }
}