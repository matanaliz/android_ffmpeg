#include <VideoDecoder.h>
#include <log.h>
#include "VideoDecoderImpl.h"

VideoDecoderImpl::VideoDecoderImpl()
    : __pCodecCtx(0)
    , __pCodec(0)
    , __pFrame(0)
    , __pFrameOut(0)
    , __pFrameBuffer(0)
    , __pSwsCtx(0)
    , __videoStream(0)
    , __isOpened(false)
    , __width(0)
    , __height(0)
    , __bufferOutSize(0)
{
    __pixelFormat = PIX_FMT_BGR32;
    __state = STOP;

    LOGD("Constructor");

}

VideoDecoderImpl::~VideoDecoderImpl()
{
    delete __pCodecCtx;
    delete __pCodec;
}

int 
VideoDecoderImpl::initFrames()
{
	//if (__pFrameOut)
	//	av_free(__pFrameOut);

    // Allocate video frame
    __pFrame = avcodec_alloc_frame();
    if(!__pFrame)
    {
        LOGE("Cannot allocate Frame");
        return -1;
    }

    __pFrameOut = avcodec_alloc_frame();
    if(!__pFrameOut)
    {
        LOGE("Cannot allocate FrameOut");
        return -1;
    }

    __width  = __pCodecCtx->width;
    __height = __pCodecCtx->height;
    
    LOGD("Video size [%d x %d]", __width, __height);
    

    // Determine required buffer size and allocate buffer
    __bufferOutSize = avpicture_get_size(__pixelFormat, __width, __height);

	//if (__pFrameBuffer)
	//	av_free(__pFrameBuffer);

    __pFrameBuffer = (unsigned char *) av_malloc(__bufferOutSize);

    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
    avpicture_fill((AVPicture *)__pFrameOut, __pFrameBuffer, __pixelFormat, __width, __height);
    
	//if (__topBuffer)
	//	free(__topBuffer);

	//if (__botBuffer)
	//	free(__botBuffer);

    __topBuffer = (unsigned char*)malloc(__bufferOutSize);
    __botBuffer = (unsigned char*)malloc(__bufferOutSize);
    

    return 0;
}

int 
VideoDecoderImpl::initSwscale()
{
	if (__pSwsCtx)
		sws_freeContext(__pSwsCtx);

    __pSwsCtx = sws_getContext(
        __width, 
        __height, 
        __pCodecCtx->pix_fmt, 
        __width, 
        __height, 
        __pixelFormat, 
        SWS_FAST_BILINEAR, 
        NULL, 
        NULL, 
        NULL
        );

    if (!__pSwsCtx)
        return -1;

    return 0;
}

int 
VideoDecoderImpl::OpenFile(const char* filepath)
{
    LOGD("Open Start");
    __isOpened = false;
    int err = 0;

    //Register all codecs
    av_register_all();
    LOGD("Codecs registered");

    if (!filepath)
        LOGE("Filepath is null!");

    //Try to open file
    LOGD("Try open file");
    if( (err = av_open_input_file(&__pFormatCtx, filepath, NULL, 0, NULL)) != 0)
    {
        LOGE("Error opening input file %d", err);
        return -1; // Error opening input file
    }
    LOGD("File opened");

    //Retriev stream info
    LOGD("Try retreav stream info");
    if(av_find_stream_info(__pFormatCtx) < 0)
    {
        LOGE("Error retreaving stream info");
        return -1;
    }

    __videoStream = -1;
    for(int i = 0; i < __pFormatCtx->nb_streams; i++)
        if(__pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO) 
        {
            __videoStream = i;
            break;
        }
        if(__videoStream == -1)
        {
            LOGE("Didn't find a video stream");
            return -1;
        }

    // Get a pointer to the codec context for the video stream
    __pCodecCtx = __pFormatCtx->streams[__videoStream]->codec;

    // Find the decoder for the video stream
    __pCodec = avcodec_find_decoder(__pCodecCtx->codec_id);
    if(__pCodec == NULL) 
    {
        LOGE("Codec not found");
        return -1;
    }
    // Open codec
    if(avcodec_open(__pCodecCtx, __pCodec) < 0)
    {
        LOGE("Could not open codec");
        return -1;
    }

    if(initFrames() < 0)
    {
        LOGE("Could not init frames and buffer");
        return -1;
    }

    if(initSwscale() < 0)
    {
        LOGE("Could not init SwsContext");
        return -1;
    }
    
    __isOpened = true;
    __state = PLAY;

    return 0;
}

int 
VideoDecoderImpl::Start()
{
	if (__isOpened)
	{
		this->start();
		return 0;
	}
	else
	{
		LOGE("Cannot start decoding thread. Open file first.");
		return -1;
	}
}

int 
VideoDecoderImpl::Pause()
{
	if (PLAY == __state)
	{
		LOGD("Changed state to pause");
		__mutex.lock();
		__state = PAUSE;
		__mutex.unlock();
	}
	else if (PAUSE == __state)
	{
		LOGD("Changed state to play");
		__mutex.lock();
		__state = PLAY;
		__mutex.unlock();
	}
}

int 
VideoDecoderImpl::Close()
{
    if (__isOpened)
    {
		__isOpened = false;
        // Free the out image
        av_free(__pFrameBuffer);
        av_free(__pFrameOut);

        // Free the frame
        av_free(__pFrame);

        // Close the codec
        avcodec_close(__pCodecCtx);

        // Close the video file
        av_close_input_file(__pFormatCtx);
        
        return 0;
    }
    else
        return -1;
}

int
VideoDecoderImpl::Seek(double percentage)
{
	int64_t ts;
	int ns, hh, mm, ss;
	int tns, thh, tmm, tss;
	tns = __pFormatCtx->duration/1000000LL;
	thh = tns/3600;
	tmm = (tns%3600)/60;
	tss = (tns%60);
	
	ns = percentage*tns;
	hh = ns/3600;
	mm = (ns%3600)/60;
	ss = (ns%60);

	ts = percentage*__pFormatCtx->duration;
	if (__pFormatCtx->start_time != AV_NOPTS_VALUE)
		ts += __pFormatCtx->start_time;
	//stream_seek(cur_stream, ts, 0, 0);
	
	return -1;
}

int 
VideoDecoderImpl::SetOutputPictureFormat(PictureFormat picFormat)
{
	switch (picFormat)
	{
	case PIC_FORMAT_RGBA:
		__pixelFormat = PIX_FMT_RGB32;
		break;
	case PIC_FORMAT_BGRA:
		__pixelFormat = PIX_FMT_BGR32;
		break;
	case PIC_FORMAT_RGB:
		__pixelFormat = PIX_FMT_RGB24;
		break;
	case PIC_FORMAT_BGR:
		__pixelFormat = PIX_FMT_RGB24;
		break;
	case PIC_FORMAT_YUV420P:
		__pixelFormat = PIX_FMT_YUV420P;
		break;
	case PIC_FORMAT_YUV420SP:
		__pixelFormat = PIX_FMT_NV12;
		break;
	default:
		LOGE("Unsupported input pixel format");
		__pixelFormat = PIX_FMT_RGB32;
		break;
	};

	if(initFrames() < 0)
	{
		LOGE("Could not reinit frames and buffer");
		return -1;
	}

	if(initSwscale() < 0)
	{
		LOGE("Could not reinit SwsContext");
		return -1;
	}

	return 0;
}

const unsigned char* 
VideoDecoderImpl::GetFrame()
{
   return __topBuffer;
}

const unsigned char* 
VideoDecoderImpl::GetFrameAtIndex(long long int index)
{
	//TODO implement
	return 0;
}

int 
VideoDecoderImpl::MoveToFrame(const long long int index)
{
    //TODO implement
    return -1;
}

const int 
VideoDecoderImpl::GetWidth() const
{
    if(__isOpened)
        return __width;
    else
        return -1;
}

const int 
VideoDecoderImpl::GetHeight() const
{
    if(__isOpened)
        return __height;
    else
        return 0;
}

const int 
VideoDecoderImpl::GetFrameBufferSize() const
{
    if (__isOpened)
        return __bufferOutSize;
    else
        return 0;
}

bool 
VideoDecoderImpl::IsOpened()
{
    return __isOpened;
}

void 
VideoDecoderImpl::doThread()
{
	int frameFinished;
	int readResult = -1;
	AVPacket packet;

    while (__isOpened)
    {
        while(__state == PLAY) 
        {
			readResult = av_read_frame(__pFormatCtx, &packet);
			if (readResult >= 0)
			{
				// Is this a packet from the video stream?
				if(packet.stream_index == __videoStream) 
				{
					// Decode video frame
					avcodec_decode_video2(__pCodecCtx, __pFrame, &frameFinished, &packet);
						
					LOGD("Decoded frame");
					
					// Did we get a video frame?
					if(frameFinished) 
					{
						// Convert the image from its native format to RGB
						sws_scale(__pSwsCtx, __pFrame->data, __pFrame->linesize, 0, __pCodecCtx->height, __pFrameOut->data, __pFrameOut->linesize);
						
						memcpy(__botBuffer,  __pFrameOut->data[0], __bufferOutSize);
						swapBuffer();
					}
				}

				// Free the packet that was allocated by av_read_frame
				av_free_packet(&packet);
			}
			else
			{
				//Cycle video. Seek to begin
				if (av_seek_frame(__pFormatCtx, -1, 10, AVSEEK_FLAG_FRAME) < 0)
					LOGD("Unsuccessful seek ");
				else
					avcodec_flush_buffers(__pCodecCtx);
			}
		}

		//__cond.wait(1);
    }
}

void 
VideoDecoderImpl::swapBuffer()
{
	unsigned char* temp;
	
	temp = __botBuffer;
	__mutex.lock();
	__botBuffer = __topBuffer;
	__topBuffer = temp;
	__mutex.unlock();
}

void 
VideoDecoderImpl::saveFrame(AVFrame *pFrame, int width, int height, int iFrame)
{
	LOGD("SAVING");
	FILE *pFile;
	char szFilename[50];
	int  y;

	// Open file
	sprintf(szFilename, "/mnt/sdcard/ffmpeg/frame%d.ppm", iFrame);
	pFile=fopen(szFilename, "wb");
	if(pFile==NULL)
	return;

	// Write header
	fprintf(pFile, "P6\n%d %d\n255\n", width, height);

	// Write pixel data
	for(y = 0; y < height; y++)
	fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width * 3, pFile);

	// Close file
	fclose(pFile);
}
