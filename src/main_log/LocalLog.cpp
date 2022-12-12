//
// Created by dev on 2022/11/3.
//

#include "LocalLog.h"
#include "../LogUtil.h"
#include <stdio.h>
static char* sLastLogError = NULL;

void LocalLog::initLogPath(char *logPath,bool isNeedLog,bool isDebug) {
    ERROR_LOG_PATH = logPath;
    IS_NEED_LOG = isNeedLog;
    IS_DEBUG = isDebug;

    LOGCATI(" initLogPath ERROR_LOG_PATH %s",ERROR_LOG_PATH);
    createLogDirs(logPath);
}


void LocalLog::createLogDirs(const char *muldir) {
    if(!IS_NEED_LOG){
        NATIVE_LOGCAT_W("the diff log switch is off. it won`t mk dirs.\n");
        return;
    }
    int i, len;
    char str[512];
    strncpy(str, muldir, 512);
    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == '/') {
            str[i] = '\0';
            if (access(str, 0) != 0) {
                mkdir(str, 0777);
            }
            str[i] = '/';
        }
    }
    if (len > 0 && access(str, 0) != 0) {
        mkdir(str, 0777);
    }
}

void LocalLog:: needLog(char *func_name, char *error_type) {
    sLastLogError = func_name;
    if(!IS_NEED_LOG){
        NATIVE_LOGCAT_W("needLog : the diff log switch is off.\n");
        return;
    }
    NATIVE_LOGCAT_E("needLog : func_name: %s,error_type: %s,", func_name, error_type)
    const char *divider = " : ";
    auto bufferSize = 1 + strlen(func_name) + strlen(divider) + strlen(error_type);
    char *finalLog = static_cast<char *>(malloc(bufferSize));
    memset(finalLog, 0, bufferSize);
    snprintf(finalLog, bufferSize, "%s:%s", func_name, error_type);
    startWriteLog(finalLog);
    free(finalLog);
}

void LocalLog::startWriteLog(char *logContent) {
    NATIVE_LOGCAT_I("invoke startWriteLog");
    createLogDirs(ERROR_LOG_PATH);
    const char *logName = "/mian_log.txt";
    char *finalLogPath = (char *) malloc(1 + strlen(ERROR_LOG_PATH) + strlen(logName));
    strcpy(finalLogPath, ERROR_LOG_PATH);
    strcat(finalLogPath, logName);
    LOGCATI("finalLogPath %s\n", finalLogPath);

    FILE *file = fopen(finalLogPath, "a");
    if (file == NULL) {
        file = fopen(finalLogPath, "w");
        NATIVE_LOGCAT_W("the file is not in exist,it will be created.\n");
        if (file == nullptr) {
            NATIVE_LOGCAT_W("open file still in ERROR\n");
        }
    }
    fputs("ERROR TIME :", file);
    time_t error_time = time(NULL);
    char *logTime = ctime(&error_time);
    fputs(logTime, file);

    fputs("ERROR log:", file);
    fputs("\n", file);
    fputs(logContent, file);
    fputs("\n", file);
    fputs("-------------------------------------------------------------------------------------------------|", file);
    fputs("\n", file);
    fputs("\n", file);
    fflush(file);
    fclose(file);
}
const  char *LocalLog::getLastLog() {
    return sLastLogError;
}
