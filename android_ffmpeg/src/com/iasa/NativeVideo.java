package com.iasa;

public class NativeVideo {

    static
    {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("nativeffmpeg");
    }

    public static native void Open(String path);
    public static native void Close();
    public static native void Start();
    public static native void Pause();
    public static native void Seek(double percentage);
    
    public static native void GetFrame(byte[] array);

    public static native int  getBufferSize();
    
    public static native int GetWidth();
    public static native int GetHeight();
    
    
    public static native int init(int width, int height);
    public static native int draw();


}
