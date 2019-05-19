LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := com_example_ndk_JNITest.c \
                   com_example_ndk_PosixTest.c
LOCAL_MODULE := ndk
include $(BUILD_SHARED_LIBRARY)