#ifndef _NATIVE_VIDEO_H_
#define _NATIVE_VIDEO_H_

#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include "../../ffmpeg/log.h"
#include "../../ffmpeg/Render.h"

#ifdef __cplusplus
extern "C" {
#endif

    JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_init(JNIEnv *, jclass, jint width, jint height);
    JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_draw(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif

#endif
