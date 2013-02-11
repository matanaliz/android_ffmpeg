#ifndef _VIDEO_DECODER_IMPL_H_
#define _VIDEO_DECODER_IMPL_H_

#define __STDC_CONSTANT_MACROS

typedef long long int UINT64_C;

extern "C" 
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <stdio.h>
#include "Threading.h"

class VideoDecoderImpl : public Thread
{
public: 
	VideoDecoderImpl();
	~VideoDecoderImpl();

	int                  OpenFile(const char* filepath);
	int					 Start();
	int					 Pause();
	int                  Close();
	int					 Seek(double percentage);
	int				     SetOutputPictureFormat(PictureFormat picFormat = PIC_FORMAT_BGRA);
	const unsigned char* GetFrame();
	const unsigned char* GetFrameAtIndex(long long int index);
	int                  MoveToFrame(long long int index);
	const int            GetWidth() const;
	const int            GetHeight() const;
	const int            GetFrameBufferSize() const;

	bool                 IsOpened();

	virtual void         doThread();

private:

	int initFrames();
	int initSwscale();
	void swapBuffer();
	void saveFrame(AVFrame *pFrame, int width, int height, int iFrame);

	AVFormatContext *__pFormatCtx;
	AVCodecContext  *__pCodecCtx;
	AVCodec         *__pCodec;
	AVFrame         *__pFrame;
	AVFrame         *__pFrameOut;
	uint8_t         *__pFrameBuffer;
	SwsContext      *__pSwsCtx;
	int              __videoStream;
	bool             __isOpened;

	int              __width;
	int              __height;
	int              __bufferOutSize;
	PixelFormat      __pixelFormat;

	unsigned char    *__topBuffer;
	unsigned char    *__botBuffer;
	Mutex			  __mutex;
	Mutex			  __pauseMutex;
	Condition         __cond;
	PlayerState __state;
};

#endif //_VIDEO_DECODER_IMPL_H_
