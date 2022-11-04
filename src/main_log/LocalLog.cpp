//
// Created by dev on 2022/11/3.
//

#include "LocalLog.h"
#include "../LogUtil.h"

void LocalLog::initLogPath(char *logPath) {
    ERROR_LOG_PATH = logPath;
    LOGCATD("ERROR_LOG_PATH %s",ERROR_LOG_PATH);
    createLogDirs(logPath);
}
void LocalLog::startWriteLog(char *logContent) {
    LOGCATD("invoke startWriteLog,and the log path is : %s\n", ERROR_LOG_PATH);
    createLogDirs(ERROR_LOG_PATH);
    const char *logName = "/mian_log.txt";
    char *finalLogPath = (char *) malloc(1 + strlen(ERROR_LOG_PATH) + strlen(logName));
    strcpy(finalLogPath, ERROR_LOG_PATH);
    strcat(finalLogPath, logName);
    LOGCATD("finalLogPath %s\n", finalLogPath);

    FILE *file = fopen(finalLogPath, "a");
    if (file == NULL) {
        file = fopen(finalLogPath, "w");
        LOGCATD("the file is not in exist,it will be created.\n");
        if (file == nullptr) {
            LOGCATD("open file still in ERROR\n");
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

void LocalLog::createLogDirs(const char *muldir) {
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
    const char *divider = " : ";
    char *finalLog = static_cast<char *>(malloc(1 + strlen(func_name) + strlen(divider) + strlen(error_type)));
    strcpy(finalLog, func_name);
    strcat(finalLog, divider);
    strcat(finalLog, error_type);
    startWriteLog(finalLog);
}
