//
// Created by dev on 2022/11/3.
//

#include "LocalLog.h"
#include "../LogUtil.h"

#define  LOG_PATH /data/user/0/com.example.testapkdiff/files/diff_patch/error_log;

void initLogPath(char *logFilePath) {
    LOGCATD("logFilePath %s", logFilePath);
}