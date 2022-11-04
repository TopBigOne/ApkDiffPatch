//
// Created by dev on 2022/11/3.
//

#ifndef APKDIFFPATCH_LOCALLOG_H
#define APKDIFFPATCH_LOCALLOG_H


class LocalLog {
public:
    void initLogPath(char *logPath);

    void startWriteLog(char *logContent);

    void createLogDirs( const char *muldir);
};


#endif //APKDIFFPATCH_LOCALLOG_H
