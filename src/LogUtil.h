
#ifndef BYTEFLOW_LOGUTIL_H
#define BYTEFLOW_LOGUTIL_H

#include<android/log.h>
#include <sys/time.h>

#define  LOG_TAG "xiao_ya_hello"

#define  LOGCATE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGCATV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  LOGCATD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGCATI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

#define ByteFlowPrintE LOGCATE
#define ByteFlowPrintV LOGCATV
#define ByteFlowPrintD LOGCATD
#define ByteFlowPrintI LOGCATI

static long long GetSysCurrentTime() {
    struct timeval time = {};
    gettimeofday(&time, NULL);
    long long curTime = ((long long) (time.tv_sec)) * 1000 + time.tv_usec / 1000;
    return curTime;
}

#endif //BYTEFLOW_LOGUTIL_H
