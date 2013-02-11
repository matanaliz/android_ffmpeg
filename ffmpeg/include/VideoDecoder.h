#ifndef _VIDEO_PLAYER_H
#define _VIDEO_PLAYER_H

enum PictureFormat
{
	PIC_FORMAT_RGBA,
	PIC_FORMAT_BGRA,
	PIC_FORMAT_RGB,
	PIC_FORMAT_BGR,
	PIC_FORMAT_YUV420P,
	PIC_FORMAT_YUV420SP
};

enum PlayerState
{
	PLAY,
	STOP,
	PAUSE
};

class VideoDecoderImpl;

class VideoDecoder
{
public:

	VideoDecoder();
	~VideoDecoder();

	int                  OpenFile(const char* filepath);
	int					 Start();
	int					 Pause();
	int                  Close();
	int					 Seek(double percentage);
	int				     SetOutputPictureFormat(PictureFormat picFormat = PIC_FORMAT_RGBA);
	const unsigned char* GetFrame();
	const unsigned char* GetFrameAtIndex(long long int index);
	int                  MoveToFrame(long long int index);
	const int            GetWidth() const;
	const int            GetHeight() const;
	const int            GetFrameBufferSize() const;

private:
	VideoDecoderImpl*   __pImpl;

};

#endif //_VIDEO_PLAYER_H
