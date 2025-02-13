LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := apkpatch

Lzma_Files := $(LOCAL_PATH)/../../lzma/C/LzmaDec.c \
              $(LOCAL_PATH)/../../lzma/C/Lzma2Dec.c 
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
  Lzma_Files += $(LOCAL_PATH)/../../lzma/Asm/arm64/LzmaDecOpt.S
endif

ZLIB_PATH  := $(LOCAL_PATH)/../../zlib1.2.11
Zlib_Files := $(ZLIB_PATH)/crc32.c    \
              $(ZLIB_PATH)/deflate.c  \
              $(ZLIB_PATH)/inflate.c  \
              $(ZLIB_PATH)/zutil.c    \
              $(ZLIB_PATH)/adler32.c  \
              $(ZLIB_PATH)/trees.c    \
              $(ZLIB_PATH)/inftrees.c \
              $(ZLIB_PATH)/inffast.c

HDP_PATH  := $(LOCAL_PATH)/../../HDiffPatch
Hdp_Files := $(HDP_PATH)/file_for_patch.c \
             $(HDP_PATH)/libHDiffPatch/HPatch/patch.c \
             $(HDP_PATH)/libParallel/parallel_import.cpp \
             $(HDP_PATH)/libParallel/parallel_channel.cpp

ADP_PATH  := $(LOCAL_PATH)/../../src/patch
Adp_Files := $(ADP_PATH)/NewStream.cpp \
             $(ADP_PATH)/OldStream.cpp \
             $(ADP_PATH)/Patcher.cpp \
             $(ADP_PATH)/ZipDiffData.cpp \
             $(ADP_PATH)/Zipper.cpp

MAIN_LOG  := $(LOCAL_PATH)/../../src/main_log
Log_Files := $(MAIN_LOG)/LocalLog.cpp \

Src_Files := $(LOCAL_PATH)/apk_patch_jni.cpp \
             $(LOCAL_PATH)/apk_patch.cpp 

LOCAL_SRC_FILES  := $(Src_Files) $(Lzma_Files) $(Zlib_Files) $(Hdp_Files) $(Adp_Files) $(Log_Files)

LOCAL_LDLIBS     := -llog
LOCAL_CFLAGS     := -Os -DANDROID_NDK -DNDEBUG -D_IS_USED_MULTITHREAD=1 -D_IS_USED_PTHREAD=1 -D_IS_NEED_CACHE_OLD_BY_COVERS=0
ifneq ($(TARGET_ARCH_ABI),armeabi)
LOCAL_CFLAGS     += -DUNALIGNED_OK 
endif
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_CFLAGS     += -D_LZMA_DEC_OPT 
endif

include $(BUILD_SHARED_LIBRARY)

