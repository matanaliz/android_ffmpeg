#ifndef _NATIVE_VIDEO_H_
#define _NATIVE_VIDEO_H_

#include <jni.h>
#include <stdlib.h>
#include <string.h>
#include <VideoDecoder.h>
#include <log.h>
#include <Render.h>

#ifdef __cplusplus
extern "C" {
#endif

    JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Open(JNIEnv *env, jclass, jstring path);
    JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Close(JNIEnv *, jclass);
	JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Start(JNIEnv *, jclass);
	JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Pause(JNIEnv *, jclass);
	JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Seek(JNIEnv *, jclass, jdouble percentage);
    
    JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_GetFrame(JNIEnv *env, jclass, jbyteArray bArray);
    JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_getBufferSize(JNIEnv *, jclass);
    JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_GetWidth(JNIEnv *, jclass);
    JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_GetHeight(JNIEnv *, jclass);
    JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_init(JNIEnv *, jclass, jint width, jint height);
    JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_draw(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif

#endif
