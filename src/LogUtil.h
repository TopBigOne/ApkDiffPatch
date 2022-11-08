
#ifndef BYTEFLOW_LOGUTIL_H
#define BYTEFLOW_LOGUTIL_H

#include<android/log.h>
#include <stdbool.h>

#define  LOG_TAG "apk_diff_native"


static bool IS_BUILD_DEBUG = true;


#define NATIVE_LOGCAT_V(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__);
#define NATIVE_LOGCAT_I(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);
#define NATIVE_LOGCAT_D(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__);
#define NATIVE_LOGCAT_W(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__);
#define NATIVE_LOGCAT_E(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);

#define  LOGCATE(...)   \
    if(IS_BUILD_DEBUG){    \
          NATIVE_LOGCAT_E(__VA_ARGS__);\
    }\

#define  LOGCATV(...){ \
    if(IS_BUILD_DEBUG){    \
          NATIVE_LOGCAT_V(__VA_ARGS__);\
    }\
}

#define LOGCATD(...)\
    if(IS_BUILD_DEBUG){    \
           NATIVE_LOGCAT_D(__VA_ARGS__);\
    }

#define  LOGCATI(...)\
    if(IS_BUILD_DEBUG){    \
           NATIVE_LOGCAT_I(__VA_ARGS__);\
    }

#define  LOGCATW(...)\
    if(IS_BUILD_DEBUG){    \
           NATIVE_LOGCAT_W(__VA_ARGS__);\
    }
#endif
