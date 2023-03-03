//Copyright (C) 2023 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

//How to load and play video with FFmpeg, OpenAL and OpenAL. See also video.h

#include "stdafx.h"
#include "Video.h"
#include "VandaEngineEditorDlg.h"
#include <thread>

CVideo::CVideo()
{
	m_sws_ctx = NULL;
	m_initialized = CFalse;
	m_maintenanceMode = CFalse;
	m_elapsedVideoTime = 0.0f;
	m_nextVideoFrameTime = 0.0f;
	m_elapsedAudioTime = 0.0f;
	//video
	m_pFormatVideoContext = NULL;
	m_pVideoCodecContext = NULL;
	m_pVideoPacket = NULL;
	m_pVideoFrame = NULL;
	m_pVideoFrameRGB = NULL;
	m_video_stream_index = -1;
	m_frameBuffer = NULL;
	Cpy(m_videoFileName, "\n");
	m_videoStream = NULL;
	m_seekFrame = CFalse;
	//

	//audio
	m_pFormatAudioContext = NULL;
	m_pAudioCodecContext = NULL;
	m_pAudioPacket = NULL;
	m_pAudioFrame = NULL;
	m_audio_stream_index = -1;
	m_resampler = NULL;
	m_num_sound_buffers = 0;
	m_audioStream = NULL;
	m_updateAudio = CTrue;
	//OpenAL
	alListener3f(AL_POSITION, 0, 0, 0);
	alGenSources(1, & m_soundSource);
	alSourcef(m_soundSource, AL_PITCH, 1.0f);
	alSourcef(m_soundSource, AL_GAIN, 1.0f);
	alSource3f(m_soundSource, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(m_soundSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	alSourcei(m_soundSource, AL_LOOPING, AL_FALSE);
	alSourcei(m_soundSource, AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcei(m_soundSource, AL_ROLLOFF_FACTOR, 0);
	alGenBuffers(NUM_VIDEO_SOUND_BUFFERS, &m_soundBuffers[0]);

	ALenum err = alGetError();
	if (err == AL_INVALID_NAME)
		PrintInfo("\nCVideo Error: AL_INVALID_NAME", COLOR_RED);
	else if (err == AL_INVALID_ENUM)
		PrintInfo("\nCVideo Error: AL_INVALID_ENUM", COLOR_RED);
	else if (err == AL_INVALID_VALUE)
		PrintInfo("\nCVideo Error: AL_INVALID_VALUE", COLOR_RED);
	else if (err == AL_INVALID_OPERATION)
		PrintInfo("\nCVideo Error: AL_INVALID_OPERATION", COLOR_RED);
	else if (err == AL_OUT_OF_MEMORY)
		PrintInfo("\nCVideo Error: AL_OUT_OF_MEMORY", COLOR_RED);

	//script
	m_hasScript = CFalse;
	m_updateScript = CFalse;
	Cpy(m_script, "\n");
	Cpy(m_lastScriptPath, "\n");
	m_updateData = CFalse;
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);

}

CVideo::~CVideo()
{
	//PrintInfo("\nreleasing all the resources");

	//Free video data
	av_free(m_frameBuffer);
	av_frame_free(&m_pVideoFrame);
	av_frame_free(&m_pVideoFrameRGB);
	avformat_close_input(&m_pFormatVideoContext);
	avcodec_free_context(&m_pVideoCodecContext);
	av_packet_free(&m_pVideoPacket);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &m_texureID);

	//Free Audio Data
	av_frame_free(&m_pAudioFrame);
	avformat_close_input(&m_pFormatAudioContext);
	avcodec_free_context(&m_pAudioCodecContext);
	av_packet_free(&m_pAudioPacket);
	swr_free(&m_resampler);

	//Free OpenAL resources
	alDeleteSources(1, &m_soundSource);
	alDeleteBuffers(NUM_VIDEO_SOUND_BUFFERS, &m_soundBuffers[0]);

	//Free Script
	LuaClose(m_lua);
}

CVoid CVideo::Reset()
{
	if (!m_pFormatVideoContext)
		return;
	SeekFrame(0);
	alSourceStop(m_soundSource);
	alDeleteSources(1, &m_soundSource);
	alDeleteBuffers(NUM_VIDEO_SOUND_BUFFERS, &m_soundBuffers[0]);
	alGenSources(1, &m_soundSource);
	alGenBuffers(NUM_VIDEO_SOUND_BUFFERS, &m_soundBuffers[0]);
	m_num_sound_buffers = 0;
	m_elapsedVideoTime = 0.0f;
	m_nextVideoFrameTime = 0.0f;
	m_elapsedAudioTime = 0.0f;
	m_updateAudio = CTrue;

	m_seekFrame = CTrue;
	UpdateAudio(); //reload audio
	UpdateVideo();
	UpdateVideo(); //Previous UpdateVideo() results in EAGAIN error so I have to request the video update again
	m_seekFrame = CFalse;
}

CVoid CVideo::SeekFrame(CInt frame)
{
	if(m_pFormatVideoContext)
		av_seek_frame(m_pFormatVideoContext, -1, frame, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_ANY);
	if(m_pFormatAudioContext)
		av_seek_frame(m_pFormatAudioContext, -1, frame, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_ANY);
	//avcodec_flush_buffers(m_pVideoCodecContext);
	//avcodec_flush_buffers(m_pAudioCodecContext);
}

CBool CVideo::SeekIFrame(CInt frame_index)
{
	double m_streamTimebase = av_q2d(m_videoStream->time_base) * 1000.0 * 10000.0; // Convert timebase to ticks so we can easily convert stream's timestamps to ticks
	long startTime = m_videoStream->start_time != AV_NOPTS_VALUE ? (long)(m_videoStream->start_time * m_streamTimebase) : 0; // We will need this when we seek (adding it to seek timestamp)
	double avgFrameDuration = 10000000 / av_q2d(m_videoStream->avg_frame_rate); // eg. 1 sec / 25 fps = 400.000 ticks (40ms)	avcodec_flush_buffers(m_pVideoCodecContext);
	long frameTimestamp = (long)(frame_index * avgFrameDuration);
	int ret = av_seek_frame(m_pFormatVideoContext, m_video_stream_index, (startTime + frameTimestamp) / 10, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_BACKWARD);
	if (ret < 0)
	{
		PrintInfo("\nCVideo::SeekIFrame() ERROR: Couldn't seek the frame");
		return CFalse;
	}
	//avcodec_flush_buffers(m_pVideoCodecContext);

	return CTrue;
}

CBool CVideo::Load()
{
	if (!InitVideoStream())
		return CFalse;

	if(!InitAudioStream())
	{
		PrintInfo("\nCouldn't initialize audio stream. Does your video format contain audio?", COLOR_YELLOW);
	}

	SeekFrame(0);
	m_seekFrame = CTrue;
	UpdateAudio(); //reload audio
	UpdateVideo();
	UpdateVideo(); //Previous UpdateVideo() results in EAGAIN error so I have to request the video update again
	m_seekFrame = CFalse;

	m_initialized = CTrue;
	return CTrue;
}

CBool CVideo::Update()
{
	if (!m_initialized || m_maintenanceMode)
		return CFalse;

	if (!m_play)
		return CFalse;

	UpdateAudio();
	UpdateVideo();

	return CTrue;
}

CBool CVideo::UpdateVideo()
{
	if (m_num_sound_buffers < NUM_VIDEO_SOUND_BUFFERS)
		return CFalse;

	if (!m_play)
		return CFalse;

	//if you want to seek sepecific frame over time
	//make sure to enable m_seekFrame variable as well
	//CFloat frame_time = (CFloat)m_videoStream->time_base.den / m_videoStream->r_frame_rate.num;
	//int frame_index = int(m_elapsedVideoTime * (CFloat)m_videoStream->time_base.den / frame_time);
	//SeekIFrame(frame_index);

	CInt response = 0;
	CBool videoFrameLoaded = CFalse;

	//PrintInfo("\nReading Frame...", COLOR_YELLOW);

	CBool exit = CFalse;

	if (!m_seekFrame)
	{
		while (m_elapsedVideoTime >= m_nextVideoFrameTime)
		{
			while (!videoFrameLoaded)
			{
				if (av_read_frame(m_pFormatVideoContext, m_pVideoPacket) >= 0)
				{
					if (m_pVideoPacket->stream_index == m_video_stream_index)
					{
						//CChar temp[MAX_URI_SIZE];
						//sprintf(temp, "\nVIDEO: AVPacket->pts %lld (%.2f sec)", m_pVideoPacket->pts, (CFloat)m_pVideoPacket->pts / (CFloat)m_videoStream->time_base.den);
						//PrintInfo(temp);

						response = DecodeVideoPacket();

						if (response < 0)
						{
							av_packet_unref(m_pVideoPacket);
							return CFalse;
						}
						videoFrameLoaded = CTrue;
					}

					av_packet_unref(m_pVideoPacket);
				}
				else
				{
					if (m_loop)
					{
						av_seek_frame(m_pFormatVideoContext, -1, 0, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_ANY);
						m_elapsedVideoTime = m_nextVideoFrameTime = 0.0f;
					}
					else
					{
						m_play = CFalse;
					}
					exit = CTrue;
					break;
				}
			}
			videoFrameLoaded = CFalse;
			m_nextVideoFrameTime += m_videoFrameTime;


			if (exit)
				break;
		}

		m_elapsedVideoTime += g_elapsedTime;
	}
	else
	{
		while (!videoFrameLoaded)
		{
			if (av_read_frame(m_pFormatVideoContext, m_pVideoPacket) >= 0)
			{
				if (m_pVideoPacket->stream_index == m_video_stream_index)
				{
					//CChar temp[MAX_URI_SIZE];
					//sprintf(temp, "\nVIDEO: AVPacket->pts %lld (%.2f sec)", m_pVideoPacket->pts, (CFloat)m_pVideoPacket->pts / (CFloat)m_videoStream->time_base.den);
					//PrintInfo(temp);

					response = DecodeVideoPacket();

					if (response < 0)
					{
						av_packet_unref(m_pVideoPacket);
						return CFalse;
					}
					videoFrameLoaded = CTrue;
				}

				av_packet_unref(m_pVideoPacket);
			}
			else
			{
				if (m_loop)
				{
					av_seek_frame(m_pFormatVideoContext, -1, 0, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_ANY);
					m_elapsedVideoTime = m_nextVideoFrameTime = 0.0f;
				}
				else
				{
					m_play = CFalse;
				}
				exit = CTrue;
				break;
			}
		}
	}

	return CTrue;
}

CBool CVideo::UpdateAudio()
{
	CInt response = 0;

	ALint buffersProcessed = 0;
	if (m_audioStream == NULL) //video has no audio
	{
		buffersProcessed = 1; 
		m_num_sound_buffers = NUM_VIDEO_SOUND_BUFFERS;
		return CFalse;
	}
	else if(m_updateAudio && m_num_sound_buffers >= NUM_VIDEO_SOUND_BUFFERS)
	{
		//how many audio buffers have been processed
		alGetSourcei(m_soundSource, AL_BUFFERS_PROCESSED, &buffersProcessed);

		//make sure listener is at 0,0,0
		alListener3f(AL_POSITION, 0, 0, 0);

		//Update volume
		alSourcef(m_soundSource, AL_GAIN, m_volume);

		//Play audio source if it's not playing
		PlaySound();
		///////////////////////////////////////
	}

	if (!m_updateAudio)
		return CFalse;

	//make sure we unqueu/queue all processed audio buffers
	while (buffersProcessed > 0 || m_num_sound_buffers < NUM_VIDEO_SOUND_BUFFERS)
	{
		// fill the Packet with data from the Stream
		if (av_read_frame(m_pFormatAudioContext, m_pAudioPacket) >= 0)
		{
			if (m_pAudioPacket->stream_index == m_audio_stream_index)
			{
				//CChar temp[MAX_URI_SIZE];
				//sprintf(temp, "\nAUDIO: AVPacket->pts %" PRId64, m_pAudioPacket->pts);
				//PrintInfo(temp);

				response = DecodeAudioPacket();

				if (response < 0)
				{
					av_packet_unref(m_pAudioPacket);
					return CFalse;
				}
				if (m_num_sound_buffers >= NUM_VIDEO_SOUND_BUFFERS)
					buffersProcessed--;
			}

			av_packet_unref(m_pAudioPacket);
		}
		else
		{
			if (m_loop)
			{
				av_seek_frame(m_pFormatAudioContext, -1, 0, AVSEEK_FLAG_FRAME | AVSEEK_FLAG_ANY);
			}
			else
			{
				m_updateAudio = CFalse;
				break;
			}
		}

		if (!m_updateAudio)
			break;

		if (m_audioStream == NULL) //video has no audio. make sure we loop just once
			buffersProcessed--;

	}

	return CTrue;
}

CInt CVideo::DecodeVideoPacket()
{
	// Supply raw packet data as input to a decoder
	int response = avcodec_send_packet(m_pVideoCodecContext, m_pVideoPacket);

	if (response < 0) 
	{
		CChar buffer[MAX_NAME_SIZE];
		av_strerror(response, buffer, sizeof(buffer));

		CChar temp[MAX_URI_SIZE];
		sprintf(temp, "\nCVideo::DecodeVideoPacket ERROR while sending a packet to the decoder: %s", buffer);
		PrintInfo(temp, COLOR_RED);
		return response;
	}

	while (response >= 0)
	{
		// Return decoded output data (into a frame) from a decoder
		response = avcodec_receive_frame(m_pVideoCodecContext, m_pVideoFrame);
		if (response == AVERROR(EAGAIN) || response == AVERROR_EOF) 
		{
			break;
		}
		else if (response < 0)
		{
			av_frame_unref(m_pVideoFrame);

			CChar buffer[MAX_NAME_SIZE];
			av_strerror(response, buffer, sizeof(buffer));

			CChar temp[MAX_URI_SIZE];
			sprintf(temp, "\nCVideo::DecodeVideoPacket ERROR while receiving a frame from the decoder: %s", buffer);
			PrintInfo(temp, COLOR_RED);
			return response;
		}

		//do not update the frame if m_elapsedVideoTime is much higher than m_nextvideoFrameTime. Just update last frame
		if (response >= 0 && ((m_elapsedVideoTime - m_nextVideoFrameTime) / m_videoFrameTime <= 1.0f || m_seekFrame))
		{
			//CChar temp[MAX_URI_SIZE];
			/*sprintf(temp,
				"\nFrame %d (type=%c, size=%d bytes, format=%d) pts %lld key_frame %d [DTS %d]",
				m_pCodecContext->frame_number,
				av_get_picture_type_char(m_pVideoFrame->pict_type),
				m_pVideoFrame->pkt_size,
				m_pVideoFrame->format,
				m_pVideoFrame->pts,
				m_pVideoFrame->key_frame,
				m_pVideoFrame->coded_picture_number
			);*/
			//PrintInfo(temp);

			response = sws_scale(m_sws_ctx, (unsigned char const* const*)(m_pVideoFrame->data), (m_pVideoFrame->linesize),
				0, m_pVideoCodecContext->height, m_pVideoFrameRGB->data, m_pVideoFrameRGB->linesize);

			if (response <= 0)
			{
				CChar temp[MAX_URI_SIZE];
				sprintf(temp, "\nDecodeVideoPacket ERROR: sws_scale status = %d\n", response);
				PrintInfo(temp, COLOR_RED);
			}
			//SaveGrayscaleFrame("c://temp/gray-%s-%d.pgm");
			//SaveRGBFrame("c://temp/RGB-%s-%d.ppm");
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_texureID);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width,
				m_height, GL_RGB, GL_UNSIGNED_BYTE,
				m_pVideoFrameRGB->data[0]);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		//free frames
		av_frame_unref(m_pVideoFrame);
	}
	return 0;
}

CBool CVideo::InitVideoStream()
{
	//PrintInfo("\ninitializing all the containers, codecs and protocols.");

	// AVFormatContext holds the header information from the format (Container)
	// Allocating memory for this component
	m_pFormatVideoContext = avformat_alloc_context();
	if (!m_pFormatVideoContext) {
		PrintInfo("\nCVideo::InitVideoStream() ERROR: could not allocate memory for Format Context", COLOR_RED);
		return CFalse;
	}

	// Open the file and read its header. The codecs are not opened.
	// The function arguments are:
	// AVFormatContext (the component we allocated memory for),
	// url (filename),
	// AVInputFormat (if you pass NULL it'll do the auto detect)
	// and AVDictionary (which are options to the demuxer)
	int error = avformat_open_input(&m_pFormatVideoContext, m_path, NULL, NULL);
	if (error != 0) {
		CChar temp[MAX_URI_SIZE];
		CChar buffer[MAX_NAME_SIZE];
		av_strerror(error, buffer, sizeof(buffer));
		printf(temp, "\nCVideo::InitVideoStream() ERROR < %s > while loading video file '%s'", buffer, m_path);
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	// now we have access to some information about our file
	// since we read its header we can say what format (container) it's
	// and some other information related to the format itself.
	//CChar temp[MAX_URI_SIZE];
	//sprintf(temp, "\nformat %s, duration %lld us, bit_rate %lld", m_pFormatContext->iformat->name, m_pFormatContext->duration, m_pFormatContext->bit_rate);
	//PrintInfo(temp);

	//PrintInfo("\nfinding stream info from format");
	// read Packets from the Format to get stream information
	// this function populates pFormatContext->streams
	// (of size equals to pFormatContext->nb_streams)
	// the arguments are:
	// the AVFormatContext
	// and options contains options for codec corresponding to i-th stream.
	// On return each dictionary will be filled with options that were not found.
	if (avformat_find_stream_info(m_pFormatVideoContext, NULL) < 0) {
		PrintInfo("\nCVideo::InitVideoStream() ERROR: could not get the stream info", COLOR_RED);
		return CFalse;
	}

	// the component that knows how to encode and Decode the video stream
	const AVCodec* pVideoCodec = NULL;
	// this component describes the properties of a video codec used by the stream i
	AVCodecParameters* pVideoCodecParameters = NULL;

	// loop though all the streams and print its main information
	for (unsigned int i = 0; i < m_pFormatVideoContext->nb_streams; i++)
	{
		AVCodecParameters* pLocalCodecParameters = NULL;
		pLocalCodecParameters = m_pFormatVideoContext->streams[i]->codecpar;

		//CChar temp1[MAX_URI_SIZE];
		//CChar temp2[MAX_URI_SIZE];
		//CChar temp3[MAX_URI_SIZE];
		//CChar temp4[MAX_URI_SIZE];
		//sprintf(temp1, "\nAVStream->time_base before open coded %d/%d", m_pFormatVideoContext->streams[i]->time_base.num, m_pFormatVideoContext->streams[i]->time_base.den);
		//sprintf(temp2, "\nAVStream->r_frame_rate before open coded %d/%d", m_pFormatVideoContext->streams[i]->r_frame_rate.num, m_pFormatVideoContext->streams[i]->r_frame_rate.den);
		//sprintf(temp3, "\nAVStream->start_time %" PRId64, m_pFormatVideoContext->streams[i]->start_time);
		//sprintf(temp4, "\nAVStream->duration %" PRId64, m_pFormatVideoContext->streams[i]->duration);

		//PrintInfo(temp1);
		//PrintInfo(temp2);
		//PrintInfo(temp3);
		//PrintInfo(temp4);

		//PrintInfo("\nfinding the proper decoder (CODEC)");

		const AVCodec* pLocalCodec = NULL;

		// finds the registered decoder for a codec ID
		pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

		if (pLocalCodec == NULL) {
			//PrintInfo("\nERROR unsupported codec!");
			// In this example if the codec is not found we just skip it
			continue;
		}

		// when the stream is a video we store its index, codec parameters and codec
		if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO) {
			if (m_video_stream_index == -1)
			{
				m_video_stream_index = i;
				m_videoStream = m_pFormatVideoContext->streams[i];
				m_videoFrameTime = (CFloat)m_videoStream->r_frame_rate.den / (CFloat)m_videoStream->r_frame_rate.num;

				pVideoCodec = pLocalCodec;
				pVideoCodecParameters = pLocalCodecParameters;

				m_width = pLocalCodecParameters->width;
				m_height = pLocalCodecParameters->height;
			}

			//CChar temp[MAX_URI_SIZE];
			//sprintf(temp, "\nVideo Codec: resolution %d x %d", pLocalCodecParameters->width, pLocalCodecParameters->height);
			//PrintInfo(temp);
		}
		// print its name, id and bitrate
		//CChar temp5[MAX_URI_SIZE];
		//sprintf(temp5, "\nCodec %s ID %d bit_rate %lld", pLocalCodec->name, pLocalCodec->id, pLocalCodecParameters->bit_rate);
		//PrintInfo(temp5);
	}

	m_pVideoPacket = av_packet_alloc();
	if (!m_pVideoPacket)
	{
		PrintInfo("\nCVideo::InitVideoStream() ERROR: failed to allocate memory for AVPacket", COLOR_RED);
		return CFalse;
	}

	if (m_video_stream_index == -1)
	{
		CChar temp[MAX_URI_SIZE];
		sprintf(temp, "\nCVideo::InitVideoStream() ERROR: File %s does not contain a video stream!", m_path);
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	m_pVideoCodecContext = avcodec_alloc_context3(pVideoCodec);
	if (!m_pVideoCodecContext)
	{
		PrintInfo("\nCVideo::InitVideoStream() ERROR: failed to allocated memory for AVCodecContext", COLOR_RED);
		return CFalse;
	}

	// Fill the codec context based on the values from the supplied codec parameters
	if (avcodec_parameters_to_context(m_pVideoCodecContext, pVideoCodecParameters) < 0)
	{
		PrintInfo("\nCVideo::InitVideoStream() ERROR: failed to copy codec params to codec context", COLOR_RED);
		return CFalse;
	}

	// Initialize the AVCodecContext to use the given AVCodec.
	if (avcodec_open2(m_pVideoCodecContext, pVideoCodec, NULL) < 0)
	{
		PrintInfo("\nCVideo::InitVideoStream() ERROR: failed to open codec through avcodec_open2", COLOR_RED);
		return CFalse;
	}

	m_pVideoFrame = av_frame_alloc();
	if (!m_pVideoFrame)
	{
		PrintInfo("\nCVideo::InitVideoStream() ERROR: failed to allocate memory for AVFrame", COLOR_RED);
		return CFalse;
	}

	m_sws_ctx = sws_getContext
	(
		m_pVideoCodecContext->width,
		m_pVideoCodecContext->height,
		m_pVideoCodecContext->pix_fmt,
		m_pVideoCodecContext->width,
		m_pVideoCodecContext->height,
		AV_PIX_FMT_RGB24,
		SWS_BILINEAR,
		NULL,
		NULL,
		NULL
	);

	///////////////////////////////////////////////////////////////////////////
	m_pVideoFrameRGB = av_frame_alloc();

	CInt num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, m_pVideoCodecContext->width, m_pVideoCodecContext->height, 1);

	m_frameBuffer = (uint8_t*)av_malloc(num_bytes);

	CInt response = av_image_fill_arrays(m_pVideoFrameRGB->data,       //uint8_t *dst_data[4], 
		m_pVideoFrameRGB->linesize,   //int dst_linesize[4],
		m_frameBuffer,          //const uint8_t * src,
		AV_PIX_FMT_RGB24,      //enum AVPixelFormat pix_fmt,
		m_pVideoCodecContext->width,   //int width, 
		m_pVideoCodecContext->height,  //int height,
		1);                    //int align);

	if (response < 0)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\nav_image_fill_arrays Failed, response = %d\n", response);
		PrintInfo(temp, COLOR_RED);
	}

	m_pVideoFrameRGB->width = m_pVideoCodecContext->width;
	m_pVideoFrameRGB->height = m_pVideoCodecContext->height;
	///////////////////////////////////////////////////////////////////////////

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_texureID);
	glBindTexture(GL_TEXTURE_2D, m_texureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height,
		0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	return CTrue;
}

CInt CVideo::DecodeAudioPacket()
{
	// Supply raw packet data as input to a decoder
	int response = avcodec_send_packet(m_pAudioCodecContext, m_pAudioPacket);

	if (response < 0) 
	{
		CChar buffer[MAX_NAME_SIZE];
		av_strerror(response, buffer, sizeof(buffer));

		CChar temp[MAX_URI_SIZE];
		sprintf(temp, "\nCVideo::DecodeAudioPacket ERROR while sending a packet to the decoder: %s", buffer);
		PrintInfo(temp, COLOR_RED);
		return response;
	}

	while (response >= 0)
	{
		// Return decoded output data (into a frame) from a decoder
		response = avcodec_receive_frame(m_pAudioCodecContext, m_pAudioFrame);
		if (response == AVERROR(EAGAIN) || response == AVERROR_EOF)
		{
			break;
		}
		else if (response < 0) 
		{
			av_frame_unref(m_pAudioFrame);

			CChar buffer[MAX_NAME_SIZE];
			av_strerror(response, buffer, sizeof(buffer));

			CChar temp[MAX_URI_SIZE];
			sprintf(temp, "\nCVideo::DecodeAudioPacket ERROR while receiving a frame from the decoder: %s", buffer);
			PrintInfo(temp, COLOR_RED);
			return response;
		}
		
		//Resample audio frame
		AVFrame* resampled_frame = av_frame_alloc();
		resampled_frame->sample_rate = m_pAudioFrame->sample_rate;
		resampled_frame->ch_layout.nb_channels = m_pAudioFrame->ch_layout.nb_channels;
		resampled_frame->ch_layout = m_pAudioFrame->ch_layout;
		resampled_frame->format = AV_SAMPLE_FMT_FLT;

		CInt result = swr_convert_frame(m_resampler, resampled_frame, m_pAudioFrame);

		CInt data_size = resampled_frame->nb_samples * resampled_frame->ch_layout.nb_channels * av_get_bytes_per_sample(AV_SAMPLE_FMT_FLT);

		if (m_num_sound_buffers < NUM_VIDEO_SOUND_BUFFERS)
		{
			alBufferData(m_soundBuffers[m_num_sound_buffers], AL_FORMAT_STEREO_FLOAT32, resampled_frame->data[0], data_size, resampled_frame->sample_rate);
			alSourceQueueBuffers(m_soundSource, 1, &m_soundBuffers[m_num_sound_buffers]);
			m_num_sound_buffers++;
		}
		else
		{
			ALuint buffer;
			alSourceUnqueueBuffers(m_soundSource, 1, &buffer);
			alBufferData(buffer, AL_FORMAT_STEREO_FLOAT32, resampled_frame->data[0], data_size, resampled_frame->sample_rate);
			alSourceQueueBuffers(m_soundSource, 1, &buffer);
		}

		//SaveAudioFrame("c://temp/Audio-Planar-%s-%d.pcm", m_pAudioFrame);
		//SaveAudioFrame("c://temp/Audio-Interleaved-%s-%d.pcm", resampled_frame);

		//free frames
		av_frame_unref(m_pAudioFrame);
		av_frame_free(&resampled_frame);

	}

	return 0;
}

CBool CVideo::InitAudioStream()
{
	// AVFormatContext holds the header information from the format (Container)
// Allocating memory for this component
	m_pFormatAudioContext = avformat_alloc_context();
	if (!m_pFormatAudioContext) {
		PrintInfo("\nCVideo::InitAudioStream() ERROR: could not allocate memory for Format Context", COLOR_RED);
		return CFalse;
	}

	// Open the file and read its header. The codecs are not opened.
	// The function arguments are:
	// AVFormatContext (the component we allocated memory for),
	// url (filename),
	// AVInputFormat (if you pass NULL it'll do the auto detect)
	// and AVDictionary (which are options to the demuxer)
	int error = avformat_open_input(&m_pFormatAudioContext, m_path, NULL, NULL);
	if (error != 0) {
		CChar temp[MAX_URI_SIZE];
		CChar buffer[MAX_NAME_SIZE];
		av_strerror(error, buffer, sizeof(buffer));
		printf(temp, "\nCVideo::InitAudioStream() ERROR < %s > while loading video file '%s'", buffer, m_path);
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	// now we have access to some information about our file
	// since we read its header we can say what format (container) it's
	// and some other information related to the format itself.
	//CChar temp[MAX_URI_SIZE];
	//sprintf(temp, "\nformat %s, duration %lld us, bit_rate %lld", m_pFormatContext->iformat->name, m_pFormatContext->duration, m_pFormatContext->bit_rate);
	//PrintInfo(temp);

	//PrintInfo("\nfinding stream info from format");
	// read Packets from the Format to get stream information
	// this function populates pFormatContext->streams
	// (of size equals to pFormatContext->nb_streams)
	// the arguments are:
	// the AVFormatContext
	// and options contains options for codec corresponding to i-th stream.
	// On return each dictionary will be filled with options that were not found.
	if (avformat_find_stream_info(m_pFormatAudioContext, NULL) < 0) {
		PrintInfo("\nCVideo::InitAudioStream() ERROR: could not get the stream info", COLOR_RED);
		return CFalse;
	}

	// the componens that knows how to encode and Decode the audio stream
	const AVCodec* pAudioCodec = NULL;
	// this component describes the properties of a audio codec used by the stream i
	AVCodecParameters* pAudioCodecParameters = NULL;

	// loop though all the streams and print its main information
	for (unsigned int i = 0; i < m_pFormatAudioContext->nb_streams; i++)
	{
		AVCodecParameters* pLocalCodecParameters = NULL;
		pLocalCodecParameters = m_pFormatAudioContext->streams[i]->codecpar;
		//CChar temp1[MAX_URI_SIZE];
		//CChar temp2[MAX_URI_SIZE];
		//CChar temp3[MAX_URI_SIZE];
		//CChar temp4[MAX_URI_SIZE];
		//sprintf(temp1, "\nAVStream->time_base before open coded %d/%d", m_pFormatContext->streams[i]->time_base.num, m_pFormatContext->streams[i]->time_base.den);
		//sprintf(temp2, "\nAVStream->r_frame_rate before open coded %d/%d", m_pFormatContext->streams[i]->r_frame_rate.num, m_pFormatContext->streams[i]->r_frame_rate.den);
		//sprintf(temp3, "\nAVStream->start_time %" PRId64, m_pFormatContext->streams[i]->start_time);
		//sprintf(temp4, "\nAVStream->duration %" PRId64, m_pFormatContext->streams[i]->duration);

		//PrintInfo(temp1);
		//PrintInfo(temp2);
		//PrintInfo(temp3);
		//PrintInfo(temp4);

		//PrintInfo("\nfinding the proper decoder (CODEC)");

		const AVCodec* pLocalCodec = NULL;

		// finds the registered decoder for a codec ID
		pLocalCodec = avcodec_find_decoder(pLocalCodecParameters->codec_id);

		if (pLocalCodec == NULL) {
			//PrintInfo("\nERROR unsupported codec!");
			// In this example if the codec is not found we just skip it
			continue;
		}

		if (pLocalCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			if (m_audio_stream_index == -1)
			{
				m_audio_stream_index = i;
				pAudioCodec = pLocalCodec;
				pAudioCodecParameters = pLocalCodecParameters;
				m_audioStream = m_pFormatAudioContext->streams[i];

				//Most audio players don't accept planar frames, so we have to convert the frame to interleaved frame
				int result = swr_alloc_set_opts2(&m_resampler, &m_audioStream->codecpar->ch_layout, AV_SAMPLE_FMT_FLT, m_audioStream->codecpar->sample_rate,
					&m_audioStream->codecpar->ch_layout, (AVSampleFormat)m_audioStream->codecpar->format, m_audioStream->codecpar->sample_rate, 0, NULL);
				if (result != 0)
				{
					PrintInfo("\nCVideo::InitAudioStream() swr_alloc_set_opts2 ERROR", COLOR_RED);
					return CFalse;
				}
				result = swr_init(m_resampler);
				/////////////////////////

			}
			//CChar temp[MAX_URI_SIZE];
			//sprintf(temp, "\nAudio Codec: %d channels, sample rate %d", pLocalCodecParameters->ch_layout.nb_channels, pLocalCodecParameters->sample_rate);
			//PrintInfo(temp);
		}

		// print its name, id and bitrate
		//CChar temp5[MAX_URI_SIZE];
		//sprintf(temp5, "\nCodec %s ID %d bit_rate %lld", pLocalCodec->name, pLocalCodec->id, pLocalCodecParameters->bit_rate);
		//PrintInfo(temp5);
	}

	m_pAudioPacket = av_packet_alloc();
	if (!m_pAudioPacket)
	{
		PrintInfo("\nCVideo::InitAudioStream() ERROR: failed to allocate memory for AVPacket", COLOR_RED);
		return CFalse;
	}

	if (m_audio_stream_index == -1) 
	{
		CChar temp[MAX_URI_SIZE];
		sprintf(temp, "\nCAudio::InitAudioStream() ERROR: File %s does not contain an audio stream!", m_path);
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	m_pAudioCodecContext = avcodec_alloc_context3(pAudioCodec);
	if (!m_pAudioCodecContext)
	{
		PrintInfo("\nCVideo::InitAudioStream() ERROR: failed to allocated memory for AVCodecContext", COLOR_RED);
		return CFalse;
	}

	// Fill the codec context based on the values from the supplied codec parameters
	if (avcodec_parameters_to_context(m_pAudioCodecContext, pAudioCodecParameters) < 0)
	{
		PrintInfo("\nCVideo::InitAudioStream() ERROR: failed to copy codec params to codec context", COLOR_RED);
		return CFalse;
	}

	// Initialize the AVCodecContext to use the given AVCodec.
	if (avcodec_open2(m_pAudioCodecContext, pAudioCodec, NULL) < 0)
	{
		PrintInfo("\nCVideo::InitAudioStream() ERROR: failed to open codec through avcodec_open2", COLOR_RED);
		return CFalse;
	}

	m_pAudioFrame = av_frame_alloc();
	if (!m_pAudioFrame)
	{
		PrintInfo("\nCVideo::InitAudioStream() ERROR: failed to allocate memory for AVFrame", COLOR_RED);
		return CFalse;
	}

	//Print audio data here
	//enum AVSampleFormat sfmt;
	//const char* fmt;
	//int num_channels = 0;

	///* print output pcm infomations, because there have no metadata of pcm */
	//sfmt = m_pAudioCodecContext->sample_fmt;

	//if (av_sample_fmt_is_planar(sfmt)) {

	//	CChar temp[MAX_URI_SIZE];
	//	const char* packed = av_get_sample_fmt_name(sfmt);
	//	sprintf(temp, "\nWarning: the sample format the decoder produced is planar (%s). Vanda Engine will output the first channel only.",
	//		packed ? packed : "?");
	//	PrintInfo(temp);
	//	sfmt = av_get_packed_sample_fmt(sfmt);
	//}

	//num_channels = m_pAudioCodecContext->ch_layout.nb_channels;
	//GetFormatFromSampleFMT(&fmt, sfmt);

	//CChar temp[MAX_URI_SIZE];
	//sprintf(temp, "\nsfmt: %s num_channels: %d sample_rate: %d", fmt, num_channels, m_pAudioCodecContext->sample_rate);
	//PrintInfo(temp);
	//

	return CTrue;
}

CVoid CVideo::PlaySound()
{
	ALenum state;

	alGetSourcei(m_soundSource, AL_SOURCE_STATE, &state);

	if (state != AL_PLAYING)
		alSourcePlay(m_soundSource);
}

CVoid CVideo::StopSound()
{
	ALenum state;

	alGetSourcei(m_soundSource, AL_SOURCE_STATE, &state);

	if (state == AL_PLAYING)
		alSourceStop(m_soundSource);
}

CVoid CVideo::PauseSound()
{
	ALenum state;

	alGetSourcei(m_soundSource, AL_SOURCE_STATE, &state);

	if (state == AL_PLAYING)
		alSourcePause(m_soundSource);
}

CInt CVideo::GetFormatFromSampleFMT(const char** fmt, enum AVSampleFormat sample_fmt)
{
	CInt i;
	struct sample_fmt_entry {
		enum AVSampleFormat sample_fmt; const CChar* fmt_be, * fmt_le;
	} sample_fmt_entries[] = {
		{ AV_SAMPLE_FMT_U8,  "u8",    "u8"    },
		{ AV_SAMPLE_FMT_S16, "s16be", "s16le" },
		{ AV_SAMPLE_FMT_S32, "s32be", "s32le" },
		{ AV_SAMPLE_FMT_FLT, "f32be", "f32le" },
		{ AV_SAMPLE_FMT_DBL, "f64be", "f64le" },
	};
	*fmt = NULL;

	for (i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++)
	{
		struct sample_fmt_entry* entry = &sample_fmt_entries[i];
		if (sample_fmt == entry->sample_fmt)
		{
			*fmt = AV_NE(entry->fmt_be, entry->fmt_le);
			return 0;
		}
	}

	CChar temp[MAX_URI_SIZE];
	sprintf(temp,"\nsample format %s is not supported as output format", av_get_sample_fmt_name(sample_fmt));
	PrintInfo(temp);
	return -1;
}

CBool CVideo::Render()
{
	if (!m_initialized || m_maintenanceMode)
		return CFalse;

	if (m_num_sound_buffers < NUM_VIDEO_SOUND_BUFFERS)
	{
		return CFalse;
	}

	if (!m_play)
		return CFalse;

	glUseProgram(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glViewport(0, 0, g_width, g_height);// resets the viewport to new dimensions.

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glUseProgram(0);
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushAttrib(GL_ENABLE_BIT);
	glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity();
	gluOrtho2D(0, g_width, 0, g_height);
	glMatrixMode(GL_MODELVIEW); glPushMatrix();	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, m_texureID);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 1);	glVertex2d(0, 0);
	glTexCoord2d(1, 1);	glVertex2d(g_width, 0);
	glTexCoord2d(1, 0);	glVertex2d(g_width, g_height);
	glTexCoord2d(0, 0);	glVertex2d(0, g_height);
	glEnd();

	glPopAttrib();
	glMatrixMode(GL_PROJECTION); glPopMatrix();
	glMatrixMode(GL_MODELVIEW); glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);

	return CTrue;
}

CVoid CVideo::SaveGrayscaleFrame(CChar* filePath)
{
	char frame_filename[MAX_NAME_SIZE];
	snprintf(frame_filename, sizeof(frame_filename), filePath, "frame", m_pVideoCodecContext->frame_number);
	// Check if the frame is a planar YUV 4:2:0, 12bpp
	// That is the format of the provided .mp4 file
	// RGB formats will definitely not give a gray image
	// Other YUV image may do so, but untested, so give a warning
	//if (m_pVideoFrame->format != AV_PIX_FMT_YUV420P)
	//{
	//	PrintInfo("\nWarning: the generated file may not be a grayscale image, but could e.g. be just the R component if the video format is RGB", COLOR_YELLOW);
	//}

	//Saving one frame///////////////////
	FILE* f;
	int i;

	f = fopen(frame_filename, "w");
	// writing the minimal required header for a pgm file format
	fprintf(f, "P5\n%d %d\n%d\n", m_pVideoFrame->width, m_pVideoFrame->height, 255);

	// writing line by line
	for (i = 0; i < m_pVideoFrame->height; i++)
		fwrite(m_pVideoFrame->data[0] + i * m_pVideoFrame->linesize[0], 1, m_pVideoFrame->width, f);
	fclose(f);
	//End of saving one frame///////////
}

CVoid CVideo::SaveRGBFrame(CChar* filePath)
{
	char frame_filename[MAX_NAME_SIZE];
	snprintf(frame_filename, sizeof(frame_filename), filePath, "frame", m_pVideoCodecContext->frame_number);

	//Saving one frame///////////////////
	FILE* f;
	int i;

	f = fopen(frame_filename, "wb");
	fprintf(f, "P6\n%d %d\n255\n", m_pVideoFrameRGB->width, m_pVideoFrameRGB->height);

	// writing line by line
	for (i = 0; i < m_pVideoFrameRGB->height; i++)
		fwrite(m_pVideoFrameRGB->data[0] + i * m_pVideoFrameRGB->linesize[0], 1, m_pVideoFrameRGB->width * 3, f);
	fclose(f);
	//End of saving one frame///////////

}

CVoid CVideo::SaveAudioFrame(CChar* filePath, AVFrame* audioFrame)
{
	AVSampleFormat format_type = (AVSampleFormat)audioFrame->format;

	CInt data_size = av_get_bytes_per_sample((AVSampleFormat)audioFrame->format);

	char frame_filename[MAX_NAME_SIZE];
	snprintf(frame_filename, sizeof(frame_filename), filePath, "frame", m_pVideoCodecContext->frame_number);

	//Saving one frame///////////////////
	FILE* f;

	f = fopen(frame_filename, "wb");

	if (format_type == AV_SAMPLE_FMT_FLTP) // planar audio
	{
		for (CInt i = 0; i < audioFrame->nb_samples; i++)
			for (CInt ch = 0; ch < m_pAudioCodecContext->ch_layout.nb_channels; ch++)
				fwrite(audioFrame->data[ch] + data_size * i, 1, data_size, f);
	}
	else if( format_type == AV_SAMPLE_FMT_FLT) // interleaved audio
	{
		for (CInt i = 0; i < audioFrame->nb_samples * m_pAudioCodecContext->ch_layout.nb_channels; i++)
				fwrite(audioFrame->data[0] + data_size * i, 1, data_size, f);
	}

	fclose(f);
}

//script functions

CVoid CVideo::ResetLua()
{
	LuaClose(m_lua);
	m_lua = LuaNewState();
	LuaOpenLibs(m_lua);
	LuaRegisterFunctions(m_lua);
}

CBool CVideo::LoadLuaFile()
{
	ResetLua();

	if (!m_hasScript)
	{
		return CFalse;
	}

	if (!LuaLoadFile(m_lua, m_script))
		return CFalse;
	return CTrue;
}

CChar* CVideo::GetScriptStringVariable(CChar* variableName)
{
	CChar* s = NULL;
	lua_getglobal(m_lua, variableName);
	if (!lua_isnil(m_lua, -1))
		s = _strdup(lua_tostring(m_lua, -1));
	else
		s = _strdup("");

	lua_pop(m_lua, 1);
	return s;
}

CBool CVideo::GetScriptBoolVariable(CChar* variableName)
{
	CInt value;
	CBool result;
	lua_getglobal(m_lua, variableName);
	value = lua_toboolean(m_lua, -1);
	if (value)
		result = CTrue;
	else
		result = CFalse;
	lua_pop(m_lua, 1);
	return result;
}

CInt CVideo::GetScriptIntVariable(CChar* variableName)
{
	CInt value;
	lua_getglobal(m_lua, variableName);
	value = lua_tointeger(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CDouble CVideo::GetScriptDoubleVariable(CChar* variableName)
{
	CDouble value;
	lua_getglobal(m_lua, variableName);
	value = lua_tonumber(m_lua, -1);
	lua_pop(m_lua, 1);
	return value;
}

CVoid CVideo::SetScriptStringVariable(CChar* variableName, CChar* value)
{
	lua_pushstring(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CVideo::SetScriptBoolVariable(CChar* variableName, CBool value)
{
	lua_pushboolean(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CVideo::SetScriptIntVariable(CChar* variableName, CInt value)
{
	lua_pushinteger(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CVideo::SetScriptDoubleVariable(CChar* variableName, CDouble value)
{
	lua_pushnumber(m_lua, value);
	lua_setglobal(m_lua, variableName);
}

CVoid CVideo::InitScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;

		lua_getglobal(m_lua, "Init");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CVideo::UpdateScript()
{
	if (m_hasScript)
	{
		g_currentInstancePrefab = NULL;

		lua_getglobal(m_lua, "Update");
		if (lua_isfunction(m_lua, -1))
		{
			lua_pcall(m_lua, 0, 0, 0);
		}

		lua_settop(m_lua, 0);
	}
}

CVoid CVideo::SetLastName(CChar* name)
{
	Cpy(m_lastName, name);
}

CChar* CVideo::GetLastName()
{
	return m_lastName;
}
