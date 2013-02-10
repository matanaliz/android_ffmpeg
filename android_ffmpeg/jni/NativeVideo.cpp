#include "NativeVideo.h"

static VideoDecoder *pVideoPlayer = new VideoDecoder();
static Render *pRender = new Render();
static int isOpened = 0;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Open(JNIEnv *env, jclass, jstring path)
{
    const char *nativePath = env->GetStringUTFChars(path, 0);

    isOpened = pVideoPlayer->OpenFile(nativePath);
       
    env->ReleaseStringUTFChars(path, nativePath);
}


JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_GetFrame(JNIEnv *env, jclass, jbyteArray bArray)
{
    
    unsigned char *data = (unsigned char *)(env->GetByteArrayElements(bArray, 0));

    env->ReleaseByteArrayElements(bArray, (jbyte*)data, 0);

}

JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Close(JNIEnv *, jclass)
{
	pVideoPlayer->Close();
}

JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Start(JNIEnv *, jclass)
{
	pVideoPlayer->Start();
}

JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Pause(JNIEnv *, jclass)
{
	pVideoPlayer->Pause();
}

JNIEXPORT void JNICALL Java_com_iasa_NativeVideo_Seek(JNIEnv *env, jclass, jdouble percentage)
{
	pVideoPlayer->Seek(percentage);
}

JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_getBufferSize(JNIEnv *, jclass)
{
    return pVideoPlayer->GetFrameBufferSize();
}

JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_GetWidth(JNIEnv *, jclass)
{
    return pVideoPlayer->GetWidth();
}

JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_GetHeight(JNIEnv *, jclass)
{
    return pVideoPlayer->GetHeight();
}

JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_init(JNIEnv *, jclass, jint width, jint height)
{
    pRender->init(width, height);
    
    return 0;
}

JNIEXPORT jint JNICALL Java_com_iasa_NativeVideo_draw(JNIEnv *, jclass)
{
    if (isOpened == 0) //change to STATUS enum
    {
        pRender->setTexture(pVideoPlayer->GetFrame(), pVideoPlayer->GetWidth(), pVideoPlayer->GetHeight());
        pRender->draw();
    }
    return 0;
}


#ifdef __cplusplus
}
#endif
