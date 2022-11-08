//
// Created by dev on 2022/11/3.
//

#ifndef APKDIFFPATCH_LOCALLOG_H
#define APKDIFFPATCH_LOCALLOG_H


#include <stdio.h>
#include "ctime"
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

static char *ERROR_LOG_PATH = strdup("/data/user/0/com.example.testapkdiff/files/diff_patch/error_log");
static  bool  IS_DEBUG = false;
static  bool  IS_NEED_LOG = false;


class LocalLog {
public:
    void initLogPath(char *logPath,bool isNeedLog,bool isDebug);

    void startWriteLog(char *logContent);

    void createLogDirs(const char *muldir);

    void needLog(char *func_name, char *error_type);
};


#endif //APKDIFFPATCH_LOCALLOG_H
