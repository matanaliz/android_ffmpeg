#ifndef _LOG_H_
#define _LOG_H_

#include <android/log.h>

#define TAG "ffmpeg"
//#define LOGD(MESSAGE) __android_log_print(ANDROID_LOG_DEBUG, TAG, MESSAGE);  
//__android_log_print(ANDROID_LOG_INFO, "MYPROG", "errno = %d, %s", errno, strerror(errno));
//__android_log_print(ANDROID_LOG_DEBUG, "MYPROG", "Hellowrold");


#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , TAG, __VA_ARGS__)


#endif