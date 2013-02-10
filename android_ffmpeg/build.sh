#!/bin/bash

echo "*******BUILDING NATIVE********"
ndk-build
echo "*******BUILDING JAVA********"
ant debug
#adb install -r bin/android_ffmpeg-debug.apk
echo "*******COPY APK FILE******"
cp bin/android_ffmpeg-debug.apk /media/sf_SPEC/
