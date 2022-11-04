//
// Created by dev on 2022/11/3.
//

#include "LocalLog.h"
#include "../LogUtil.h"


#include <stdio.h>
#include "ctime"
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>

#define  LOG_PATH /data/user/0/com.example.testapkdiff/files/diff_patch/error_log;

// /data/user/0/com.example.testapkdiff/files/
const char *logPath = "/data/user/0/com.example.testapkdiff/files/diff_patch/error_log";

void LocalLog::initLogPath(char *logPath) {
    LOGCATD("logFilePath %s", logPath);

    char *main_log = "Hello--1--》 老铁；下午好, 今天喝咖啡吗？";
    startWriteLog(main_log);

}


void LocalLog::startWriteLog(char *logContent) {
    printf("start invoke testLocalWriteLog,logPath %s\n", logPath);
    createLogDirs(logPath);
    const char *logName = "/mian_log.txt";
    char *finalLogPath = (char *) malloc(1 + strlen(logPath) + strlen(logName));
    strcpy(finalLogPath, logPath);
    strcat(finalLogPath, logName);
    printf("finalLogPath %s\n", finalLogPath);

    FILE *file = fopen(finalLogPath, "a");
    if (file == NULL) {
        file = fopen(finalLogPath, "w");
        printf("the file is not in exist,it will be created.\n");
        if (file == nullptr) {
            printf("open file still in ERROR\n");
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
