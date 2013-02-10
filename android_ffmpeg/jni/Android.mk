LOCAL_PATH := $(call my-dir)

TARGET_ARCH = armv6

include $(CLEAR_VARS)
LOCAL_MODULE := ffmpeg
LOCAL_SRC_FILES := ../../libffmpeg.so
LOCAL_EXPORT_C_INCLUDES := ../../rockplayer_ffmpeg_git_20100418/android/armv6/include/
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE    := nativeffmpeg
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../ffmpeg \
                    $(LOCAL_PATH)/../../rockplayer_ffmpeg_git_20100418/android/$(TARGET_ARCH)/include/


LOCAL_SRC_FILES := NativeVideo.cpp ../../ffmpeg/VideoPlayer.cpp ../../ffmpeg/Render.cpp ../../ffmpeg/ShaderProgram.cpp ../../ffmpeg/Threading.cpp

LOCAL_SHARED_LIBRARIES := ffmpeg

LOCAL_LDLIBS +=  -lc -lm -lz -ldl -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
