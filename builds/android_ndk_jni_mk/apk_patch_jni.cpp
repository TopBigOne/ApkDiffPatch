// apk_patch_jni.cpp
// Created by sisong on 2019-08-22.
#include <jni.h>
#include "apk_patch.h"
#include <android/log.h>
#include "../../src/main_log/LocalLog.h"
#include "../../src/LogUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT int
Java_com_github_sisong_ApkPatch_patch(JNIEnv *jenv, jobject jobj,
                                      jstring oldApkPath, jstring patchFilePath, jstring outNewApkPath,
                                      jlong maxUncompressMemory, jstring tempUncompressFilePath, int threadNum) {
    const char *cOldApkPath = jenv->GetStringUTFChars(oldApkPath, NULL);
    const char *cPatchFilePath = jenv->GetStringUTFChars(patchFilePath, NULL);
    const char *cOutNewApkPath = jenv->GetStringUTFChars(outNewApkPath, NULL);
    const char *cTempFilePath = NULL;

    LOGCATI("--------------------------------------------------------------------|");
    LOGCATI("cOldApkPath     : %s ", cOldApkPath);
    LOGCATI("cPatchFilePath  : %s", cPatchFilePath);
    LOGCATI("cOutNewApkPath  : %s", cOutNewApkPath);
    LOGCATI("--------------------------------------------------------------------|\n");

    if (tempUncompressFilePath != NULL) {
        cTempFilePath = jenv->GetStringUTFChars(tempUncompressFilePath, NULL);
        if ((cTempFilePath != NULL) && (strlen(cTempFilePath) == 0)) {
            jenv->ReleaseStringUTFChars(tempUncompressFilePath, cTempFilePath);
            cTempFilePath = NULL;
        }
    }

    size_t cMaxUncompressMemory = (size_t) maxUncompressMemory;
    assert((jlong) cMaxUncompressMemory == maxUncompressMemory);

    TPatchResult result = ApkPatch(cOldApkPath, cPatchFilePath, cOutNewApkPath,
                                   cMaxUncompressMemory, cTempFilePath, threadNum);

    LocalLog localLog;
    if(result==PATCH_SUCCESS){
        localLog.needLog("TPatchResult: ","finally , the apk diff patch is generated success.");
    }

    if (cTempFilePath != NULL){
        jenv->ReleaseStringUTFChars(tempUncompressFilePath, cTempFilePath);
    }

    jenv->ReleaseStringUTFChars(outNewApkPath, cOutNewApkPath);
    jenv->ReleaseStringUTFChars(patchFilePath, cPatchFilePath);
    jenv->ReleaseStringUTFChars(oldApkPath, cOldApkPath);
    return (int) result;
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void
Java_com_github_sisong_ApkPatch_initApkDiff(JNIEnv *env, jclass clazz, jstring log_path,
                                            jboolean is_need_log, jboolean is_debug) {
    LocalLog localLog;
    char *logPathChar = const_cast<char *>(env->GetStringUTFChars(log_path, JNI_FALSE));
    IS_BUILD_DEBUG = is_debug==JNI_TRUE;
    localLog.initLogPath(logPathChar,is_need_log==JNI_TRUE,IS_BUILD_DEBUG);
    NATIVE_LOGCAT_V("---------init apk diff native-------------------|");
    NATIVE_LOGCAT_I(" initApkDiff #is_need_log : %d\n", is_need_log);
    NATIVE_LOGCAT_D(" initApkDiff #is_debug    : %d\n", is_debug);
    NATIVE_LOGCAT_W("------------------------------------------------|\n");
}

#ifdef __cplusplus
}
#endif
