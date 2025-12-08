#ifndef EXT_SETTING_SERVICE_C_WRAPPER_H
#define EXT_SETTING_SERVICE_C_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocate a Solarwinds::SettingService object
 * @return
 */
void *Setting_Service_Allocate();

/**
 * Free a Solarwinds::SettingService object
 * @param service void*
 * @return
 */
void Setting_Service_Free(void *service);

#ifdef __cplusplus
}
#endif

#endif // EXT_SETTING_SERVICE_C_WRAPPER_H