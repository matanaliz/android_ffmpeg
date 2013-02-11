#include <VideoDecoder.h>
#include "VideoDecoderImpl.h"

VideoDecoder::VideoDecoder()
	: __pImpl(0)
{
	__pImpl = new VideoDecoderImpl();
}

VideoDecoder::~VideoDecoder()
{
	//__pImpl->Stop();
	delete __pImpl;
}

int 
	VideoDecoder::OpenFile(const char* filepath)
{	
	if (__pImpl)
		return __pImpl->OpenFile(filepath);
	else
		return -1;
}


int 
	VideoDecoder::Start()
{
	if (__pImpl)
		return __pImpl->Start();
	else
		return -1;
}


int	
	VideoDecoder::Pause()
{
	if (__pImpl)
		return __pImpl->Pause();
	else
		return -1;
}

int 
	VideoDecoder::Close()
{
	if (__pImpl)
		return __pImpl->Close();
	else
		return -1;
}

int
	VideoDecoder::Seek(double perc)
{
	if (__pImpl)
		return __pImpl->Seek(perc);
	else
		return -1;
}

int 
	VideoDecoder::SetOutputPictureFormat(PictureFormat picFormat)
{
	if (__pImpl)
		return __pImpl->SetOutputPictureFormat(picFormat);
	else
		return -1;
}

const unsigned char* 
	VideoDecoder::GetFrame()
{
	if (__pImpl)
		return __pImpl->GetFrame();
	else
		return 0;
}

const unsigned char* 
	VideoDecoder::GetFrameAtIndex(long long int index)
{
	if (__pImpl)
		return __pImpl->GetFrameAtIndex(index);
	else
		return 0;
}

int 
	VideoDecoder::MoveToFrame(long long int index)
{
	if (__pImpl)
		return __pImpl->MoveToFrame(index);
	else
		return -1;
}

const int 
	VideoDecoder::GetWidth() const
{
	if (__pImpl)
		return __pImpl->GetWidth();
	else
		return -1;
}

const int 
	VideoDecoder::GetHeight() const
{
	if (__pImpl)
		return __pImpl->GetHeight();
	else
		return -1;
}

const int 
	VideoDecoder::GetFrameBufferSize() const
{
	if (__pImpl)
		return __pImpl->GetFrameBufferSize();
	else
		return -1;
}
