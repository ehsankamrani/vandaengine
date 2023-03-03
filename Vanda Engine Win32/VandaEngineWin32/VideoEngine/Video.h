//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

//How to load and play video with FFmpeg, OpenAL and OpenAL. See also video.cpp

#pragma once
#include "../common/utility.h"
#include "../ScriptEngine/luaforcpp.h"
#include "..\AudioEngine/openal.h"
#include "..\AudioEngine/OpenALSystem.h"

#define NUM_VIDEO_SOUND_BUFFERS 30

extern "C"
{
#include <ffmpeg/libavcodec/avcodec.h>
#include <ffmpeg/libavutil/avutil.h>
#include <ffmpeg/libavutil/audio_fifo.h>
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libswscale/swscale.h>
#include <ffmpeg/libavutil/imgutils.h>  // <-- Requiered for av_image_get_buffer_size
#include <ffmpeg/libswresample/swresample.h>
}

#include <string>
#include <set>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <inttypes.h>

class CVideo
{
public:
	CVideo();
	~CVideo();

	CVoid Reset();
	CBool Load();
	CBool Update();
	CBool UpdateVideo();
	CBool UpdateAudio();
	CBool Render();
	CVoid SeekFrame(CInt frame);
	CBool SeekIFrame(CInt frame_index);
	CVoid SetSeekFrame(CBool set) { m_seekFrame = set; }
	CVoid StopSound();
	CVoid PauseSound();
	CVoid PlaySound();
	CVoid SetMaintenanceMode(CBool state) { m_maintenanceMode = state; }
	CBool GetMaintenanceMode() { return m_maintenanceMode; }
	CVoid SetName(CChar* name) { Cpy(m_name, name); }
	CVoid SetPath(CChar* path) { Cpy(m_path, path); }
	CVoid SetVolume(CFloat volume) { m_volume = volume; }
	CVoid SetLoop(CBool loop) { m_loop = loop; }
	CVoid SetPlay(CBool play) { m_play = play; if (!m_play) Reset(); }
	CVoid SetVideoFileName(CChar* soundName) { Cpy(m_videoFileName, soundName); }
	CVoid SetLastName(CChar* name);
	CVoid SetUpdateData(CBool update) { m_updateData = update; }

	CChar* GetName() { return m_name; }
	CChar* GetPath() { return m_path; }
	CFloat GetVolume() { return m_volume; }
	CBool GetLoop() { return m_loop; }
	CBool GetPlay() { return m_play; }
	CChar* GetVideoFileName() { return m_videoFileName; }
	CChar* GetLastName();
	CBool GetUpdateData() { return m_updateData; }

	CVoid ResetLua();
	CBool LoadLuaFile();

	CVoid SetHasScript(CBool set) { m_hasScript = set; }
	CBool GetHasScript() { return m_hasScript; }
	CVoid SetScript(CChar* script) { Cpy(m_script, script); }
	CChar* GetScript() { return m_script; }
	CVoid SetLastScriptPath(CChar* script) { Cpy(m_lastScriptPath, script); }
	CChar* GetLastScriptPath() { return m_lastScriptPath; }

	CVoid SetUpdateScript(CBool set) { m_updateScript = set; }
	CBool GetUpdateScript() { return m_updateScript; }

	CVoid SetTempScriptPath(CChar* path) { Cpy(m_tempScriptPath, path); }
	CVoid SetTempCurrentScriptPath(CChar* path) { Cpy(m_tempCurrentScriptPath, path); }

	CChar* GetTempScriptPath() { return m_tempScriptPath; }
	CChar* GetTempCurrentScriptPath() { return m_tempCurrentScriptPath; }

	CVoid InitScript();
	CVoid UpdateScript();

	//functions to get and set script variables
	CChar* GetScriptStringVariable(CChar* variableName);
	CBool GetScriptBoolVariable(CChar* variableName);
	CInt GetScriptIntVariable(CChar* variableName);
	CDouble GetScriptDoubleVariable(CChar* variableName);
	CVoid SetScriptStringVariable(CChar* variableName, CChar* value);
	CVoid SetScriptBoolVariable(CChar* variableName, CBool value);
	CVoid SetScriptIntVariable(CChar* variableName, CInt value);
	CVoid SetScriptDoubleVariable(CChar* variableName, CDouble value);

	CChar m_name[MAX_NAME_SIZE];
	CChar m_lastName[MAX_NAME_SIZE];
	CChar m_path[MAX_NAME_SIZE];
	CFloat m_volume;
	CBool m_loop, m_play;
	CChar m_videoFileName[MAX_NAME_SIZE];

private:
	lua_State* m_lua;
	CBool m_hasScript;
	CChar m_script[MAX_URI_SIZE];
	CBool m_updateScript;
	CChar m_tempScriptPath[MAX_URI_SIZE];
	CChar m_tempCurrentScriptPath[MAX_URI_SIZE];
	CChar m_lastScriptPath[MAX_URI_SIZE];
	CBool m_updateData;
	CBool m_initialized;
	CBool m_maintenanceMode;

	CFloat m_elapsedVideoTime;
	CFloat m_nextVideoFrameTime;

	CFloat m_elapsedAudioTime;
	//Video
	AVCodecContext* m_pVideoCodecContext;
	AVFormatContext* m_pFormatVideoContext;
	AVPacket* m_pVideoPacket;
	AVFrame* m_pVideoFrame;
	AVFrame* m_pVideoFrameRGB;
	unsigned char* m_frameBuffer;
	struct SwsContext* m_sws_ctx;
	GLuint m_texureID;
	CUInt m_width, m_height;
	CInt m_video_stream_index;
	AVStream* m_videoStream;
	CFloat m_videoFrameTime;
	CBool m_seekFrame;

	CBool InitVideoStream();
	CInt DecodeVideoPacket();
	CVoid SaveGrayscaleFrame(CChar* filePath);
	CVoid SaveRGBFrame(CChar* filePath);

	//Audio
	AVCodecContext* m_pAudioCodecContext;
	AVFormatContext* m_pFormatAudioContext;
	AVPacket* m_pAudioPacket;
	AVFrame* m_pAudioFrame;
	CInt m_audio_stream_index;
	AVStream* m_audioStream;
	CInt m_num_sound_buffers;
	CBool m_updateAudio;
	CBool InitAudioStream();
	CInt DecodeAudioPacket();
	CVoid SaveAudioFrame(CChar* filePath, AVFrame* audioFrame);
	CInt GetFormatFromSampleFMT(const char** fmt, enum AVSampleFormat sample_fmt);
	//OpenAL
	ALuint m_soundBuffers[NUM_VIDEO_SOUND_BUFFERS];
	ALuint m_soundSource;
	SwrContext* m_resampler;
};