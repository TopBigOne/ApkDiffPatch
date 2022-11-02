// apk_patch_jni.cpp
// Created by sisong on 2019-08-22.
#include <jni.h>
#include "apk_patch.h"
#include "../../src/TT.h"
#include <android/log.h>


#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT int
Java_com_github_sisong_ApkPatch_testNdk(JNIEnv *jenv, jobject jobj) {
    TT tt;
    // tt.testNdk();
    __android_log_print(ANDROID_LOG_ERROR, "TRACKERS", "%s", "77777777");
    return 123;
}
#ifdef __cplusplus
}
#endif


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

    if (cTempFilePath != NULL) jenv->ReleaseStringUTFChars(tempUncompressFilePath, cTempFilePath);

    jenv->ReleaseStringUTFChars(outNewApkPath, cOutNewApkPath);
    jenv->ReleaseStringUTFChars(patchFilePath, cPatchFilePath);
    jenv->ReleaseStringUTFChars(oldApkPath, cOldApkPath);
    return (int) result;
}

#ifdef __cplusplus
}
#endif
