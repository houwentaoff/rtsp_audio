/*
 * test_audio.c
 *
 * History:
 *	2008/06/27 - [Cao Rongrong] created file
 *	2008/11/14 - [Cao Rongrong] support PAUSE and RESUME
 *	2009/02/24 - [Cao Rongrong] add duplex,
 *                                                     playback support more format
 *	2009/03/02 - [Cao Rongrong] add xrun
 *
 * Copyright (C) 2007-2008, Ambarella, Inc.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *
 *  This program will record the sound data to a file. It will run almost infinite,
 *  you can type "CTRL + C" to terminate it.
 *
 *  When the file is recorded, you can play it by "aplay". But you should pay
 *  attention to the option of "aplay", if the option is incorrect, you may hear
 *  noise rather than the sound you record just now.
 */


#include <alsa/asoundlib.h>
#include <assert.h>
#include <sys/signal.h>
#include <basetypes.h>
#include <string.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include "iav_drv.h"
#include "iav_drv_ex.h"

#include "audio_encode.h"

/* The sound format you want to record */
#define DEFAULT_FORMAT      SND_PCM_FORMAT_A_LAW//SND_PCM_FORMAT_S16_LE //  SND_PCM_FORMAT_MU_LAW//
#define DEFAULT_RATE         8000
#define DEFAULT_CHANNELS    1

/* global data */
char pcm_name[256];
static snd_pcm_t *handle = NULL;
//static u_char *buf_rx;
static u_char *buf_tmp;
static size_t chunk_bytes;
static snd_pcm_uframes_t chunk_size;


static struct {
	snd_pcm_format_t format;
	unsigned int channels;
	unsigned int rate;
} hwparams;

/*
 * When DEFAULT_CHANNELS is 1 ("mono"), channel_id is used to
 * choose which channel to record (Channel 0 or Channel 1 ?)
 */
static int channel_id = 1;

static size_t bits_per_sample, bits_per_frame;

static int fd = -1;
//add by yjc 2012/06/21
static int set_audio_clk_freq(unsigned int audio_clk_freq);

static snd_pcm_uframes_t set_params(snd_pcm_t *handle, snd_pcm_stream_t stream)
{
	snd_pcm_hw_params_t *params;
	snd_pcm_sw_params_t *swparams;
	snd_pcm_uframes_t buffer_size;
	snd_pcm_uframes_t chunk_size = 0;
	snd_pcm_uframes_t start_threshold;
	unsigned period_time = 0;
	unsigned buffer_time = 0;
	size_t chunk_bytes = 0;
	int err;

	snd_pcm_hw_params_alloca(&params);
	snd_pcm_sw_params_alloca(&swparams);

	err = snd_pcm_hw_params_any(handle, params);
	if (err < 0) {
		printf("Broken configuration for this PCM: no configurations available");
		exit(EXIT_FAILURE);
	}

	err = snd_pcm_hw_params_set_access(handle, params,
						   SND_PCM_ACCESS_RW_INTERLEAVED);
	if (err < 0) {
		printf("Access type not available");
		exit(EXIT_FAILURE);
	}

    printf("format = %s, channels = %d, rate = %d\n",
            snd_pcm_format_name(hwparams.format),hwparams.channels,hwparams.rate);

	//err = snd_pcm_hw_params_set_format(handle, params, hwparams.format);
    err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
	if (err < 0) {
		printf("Sample format non available");
		exit(EXIT_FAILURE);
	}

	//err = snd_pcm_hw_params_set_channels(handle, params, hwparams.channels);
    err = snd_pcm_hw_params_set_channels(handle, params, 2);
	if (err < 0) {
		printf("Channels count non available");
		exit(EXIT_FAILURE);
	}

#if 0
	//add by yjc 2012/08/21
	err = set_audio_clk_freq(hwparams.rate);
	if (err < 0){
		printf("set_audio_clk_freq fail..........\n");
		exit(EXIT_FAILURE);
	}
#endif

	err = snd_pcm_hw_params_set_rate(handle, params, hwparams.rate, 0);
    if (err < 0) {
		printf("Rate non available");
		exit(EXIT_FAILURE);
	}


	err = snd_pcm_hw_params_get_buffer_time_max(params,
						    &buffer_time, 0);
	assert(err >= 0);
	if (buffer_time > 500000)
		buffer_time = 500000;


	period_time = buffer_time / 4;

	err = snd_pcm_hw_params_set_period_time_near(handle, params,
		                        &period_time, 0);
	assert(err >= 0);

	err = snd_pcm_hw_params_set_buffer_time_near(handle, params,
							     &buffer_time, 0);

	assert(err >= 0);

	err = snd_pcm_hw_params(handle, params);
	if (err < 0) {
		printf("Unable to install hw params:");
		exit(EXIT_FAILURE);
	}
	snd_pcm_hw_params_get_period_size(params, &chunk_size, 0);
	snd_pcm_hw_params_get_buffer_size(params, &buffer_size);
	if (chunk_size == buffer_size) {
		printf("Can't use period equal to buffer size (%lu == %lu)",
		      chunk_size, buffer_size);
		exit(EXIT_FAILURE);
	}

	snd_pcm_sw_params_current(handle, swparams);

	err = snd_pcm_sw_params_set_avail_min(handle, swparams, chunk_size);

	if(stream == SND_PCM_STREAM_PLAYBACK)
		start_threshold = (buffer_size / chunk_size) * chunk_size;
	else
		start_threshold = 1;
	err = snd_pcm_sw_params_set_start_threshold(handle, swparams, start_threshold);
	assert(err >= 0);

	err = snd_pcm_sw_params_set_stop_threshold(handle, swparams, buffer_size);
	assert(err >= 0);

	if (snd_pcm_sw_params(handle, swparams) < 0) {
		printf("unable to install sw params:");
		exit(EXIT_FAILURE);
	}

	//bits_per_sample = snd_pcm_format_physical_width(hwparams.format);
    bits_per_sample = snd_pcm_format_physical_width(SND_PCM_FORMAT_S16_LE);
	//bits_per_frame = bits_per_sample * hwparams.channels;
	bits_per_frame = bits_per_sample * 2;
	chunk_bytes = chunk_size * bits_per_frame / 8;

    printf("chunk_size = %d,chunk_bytes = %d,buffer_size = %d\n\n",
        (int)chunk_size,chunk_bytes,(int)buffer_size);

	return chunk_size;

}


/* I/O error handler */
static void xrun(snd_pcm_stream_t stream)
{
	snd_pcm_status_t *status;
	int res;

	snd_pcm_status_alloca(&status);
	if ((res = snd_pcm_status(handle, status))<0) {
		printf("status error: %s\n", snd_strerror(res));
		exit(EXIT_FAILURE);
	}
	if (snd_pcm_status_get_state(status) == SND_PCM_STATE_XRUN) {
		struct timeval now, diff, tstamp;
		gettimeofday(&now, 0);
		snd_pcm_status_get_trigger_tstamp(status, &tstamp);
		timersub(&now, &tstamp, &diff);
		fprintf(stderr, "%s!!! (at least %.3f ms long)\n",
			stream == SND_PCM_STREAM_PLAYBACK ? "underrun" : "overrun",
			diff.tv_sec * 1000 + diff.tv_usec / 1000.0);

		if ((res = snd_pcm_prepare(handle))<0) {
			printf("xrun: prepare error: %s\n", snd_strerror(res));
			exit(EXIT_FAILURE);
		}
		return;		/* ok, data should be accepted again */
	} if (snd_pcm_status_get_state(status) == SND_PCM_STATE_DRAINING) {
		printf("draining!!!\n");
		if (stream == SND_PCM_STREAM_CAPTURE) {
			fprintf(stderr, "capture stream format change? attempting recover...\n");
			if ((res = snd_pcm_prepare(handle))<0) {
				printf("xrun(DRAINING): prepare error: %s", snd_strerror(res));
				exit(EXIT_FAILURE);
			}
			return;
		}
	}

	exit(EXIT_FAILURE);
}

static size_t pcm_read(snd_pcm_uframes_t chunk_size, u_char *data, size_t rcount)
{
	ssize_t r;
	size_t result = 0;
	size_t count = rcount;

	if (count != chunk_size) {
		count = chunk_size;
	}

	while (count > 0) {
		r = snd_pcm_readi(handle, data, count);
		if (r == -EAGAIN || (r >= 0 && (size_t)r < count)) {
			snd_pcm_wait(handle, 1000);
		}else if (r == -EPIPE){
			xrun(SND_PCM_STREAM_CAPTURE);
		}else if (r < 0) {
			printf("read error: %s", snd_strerror(r));
			exit(EXIT_FAILURE);
		}

		if (r > 0) {
			result += r;
			count -= r;
			data += r * bits_per_frame / 8;
		}
	}

	return result;
}

static size_t handle_data_cp(snd_pcm_uframes_t chunk_size, u_char *data, u_char *tmp)
{
    size_t tmp_cnt, i, bfcount, chunk_bytes;

	chunk_bytes = chunk_size * bits_per_frame / 8;

    if(hwparams.channels == 1) {

        tmp_cnt = chunk_bytes >> 1;

        for(i = 0;i < tmp_cnt; i++){
			if(channel_id)
				*((u_short *)tmp + i) = *((u_short *)data + i * 2 + 1);
			else
				*((u_short *)tmp + i) = *((u_short *)data + i * 2);
        }
    }
    else {
		if(hwparams.format != SND_PCM_FORMAT_S16_LE){
			printf("MU_LAW and A_LAW only support mono\n");
			exit(EXIT_FAILURE);
		}
        tmp_cnt = chunk_bytes;
    }

    switch(hwparams.format)
    {
        case SND_PCM_FORMAT_A_LAW:
            bfcount = G711::ALawEncode(data, (s16 *)tmp, tmp_cnt);
            break;
        case SND_PCM_FORMAT_MU_LAW:
            bfcount = G711::ULawEncode(data, (s16 *)tmp, tmp_cnt);
            break;
        case SND_PCM_FORMAT_S16_LE:
			if(hwparams.channels == 1){
				memcpy(data, tmp, tmp_cnt);
			}
            bfcount = tmp_cnt;
            break;
        default:
            printf("Not supported format!\n");
            exit(EXIT_FAILURE);
    }

    return bfcount;

}

int audioOpen(void) {
    int err;
	snd_pcm_stream_t stream = SND_PCM_STREAM_CAPTURE;
    printf("enter func : %s\n", __func__);

	chunk_size = -1;
	hwparams.format = DEFAULT_FORMAT;
	hwparams.rate = DEFAULT_RATE;
	hwparams.channels = DEFAULT_CHANNELS;
    strcpy(pcm_name, "default");

    err = snd_pcm_open(&handle, pcm_name, stream, 0);
    if (err < 0) {
        printf("audio open error: %s", snd_strerror(err));
        return 1;
    }

    chunk_size = set_params(handle, stream);

	chunk_bytes = chunk_size * bits_per_frame / 8;

	//buf_rx = (u_char *)malloc(chunk_bytes);
	buf_tmp = (u_char *)malloc(chunk_bytes);
	//if (buf_tmp == NULL || buf_rx == NULL) {
	if (buf_tmp == NULL) {
		printf("not enough memory");
		exit(EXIT_FAILURE);
	}

    printf("end func : %s\n", __func__);
    return 0;
}

int audioClose(void) {
    printf("enter func : %s\n", __func__);
	snd_pcm_close(handle);
	close(fd);
	free(buf_tmp);
	//free(buf_rx);

    printf("end func : %s\n", __func__);
    return 0;
}

int audioGetOneFrame(unsigned char *buf, unsigned int *size) {
    ssize_t c = chunk_bytes;
    size_t f = c * 8 / bits_per_frame;
    if (pcm_read(chunk_size, buf, f) != f)
        printf("pcm_read err!!\n");
    *size = handle_data_cp(chunk_size, buf, buf_tmp);
    //printf("chunk_size:%d, c:%d\n", chunk_size, c);
    //memcpy(buf, buf_rx, c);

    return 0;
}

//add by yjc 2012/06/21
static int set_audio_clk_freq(unsigned int audio_clk_freq)
{
	int fd_iav = -1;
	int ret = -1;

	if ((fd_iav = open("/dev/iav", O_RDWR, 0)) < 0) {
		printf("open /dev/iav fail");
		goto errExit;
	}
	if (ioctl(fd_iav, IAV_IOC_SET_AUDIO_CLK_FREQ_EX, audio_clk_freq) < 0) {
		printf("IAV_IOC_SET_AUDIO_CLK_FREQ_EX fail\n");
		goto errExit;
	}
	//set success flag
	ret = 0;

errExit:

	if (fd_iav >= 0)
	{
		close(fd_iav);
		fd_iav = -1;
	}

	return ret;
}

#if 0
int main(int argc, char *argv[])
{
	const char *name = "test111.g711";	/* current filename */
    unsigned char buf[4096];
    unsigned int size;
	int rest;		/* number of bytes to capture */

	rest = 40000;

	/* open a new file to write */
	remove(name);
	if ((fd = open(name, O_WRONLY | O_CREAT, 0644)) == -1) {
		perror(name);
		exit(EXIT_FAILURE);
    }

    audioOpen();

    while(rest > 0) {
        audioGetOneFrame(buf, &size);
        if (write(fd, buf, size) != size) {
            printf("write err!!\n");
            exit(EXIT_FAILURE);
        }

        rest -= size;
    }
    

    audioClose();

	return EXIT_SUCCESS;
}
#else
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "G711AudioStreamServerMediaSubsession.hh"

UsageEnvironment* env;

// To make the second and subsequent client for each stream reuse the same
// input stream as the first client (rather than playing the file from the
// start for each client), change the following "False" to "True":
Boolean reuseFirstSource = True;

// To stream *only* MPEG-1 or 2 video "I" frames
// (e.g., to reduce network bandwidth),
// change the following "False" to "True":
Boolean iFramesOnly = False;

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName); // fwd

//add 2012/11/13 by yjc, add rtsp audio port
#define PROTO_CONFIG_FILE       ("/etc/ambaipcam/mediaserver/proto.cfg")
#define DEFAULT_RTSP_AUDIO_PORT        (30004)

static int get_rtsp_audio_port_from_cfg(const char* cfg)
{
	FILE *fp = NULL;
	int rtsp_audio_port = DEFAULT_RTSP_AUDIO_PORT;
	char line[256] = {0};
	int port_proto_ver = 2; 

	fp = fopen(cfg, "rb");
	if (NULL == fp)
	{
		printf("%s,open %s fail..................\n", __func__, cfg);
		goto errExit;
	}

	while (NULL != fgets(line, sizeof(line) - 1, fp))
	{
		if (1 == sscanf(line, "port_proto_ver = %d", &port_proto_ver))
		{
			break;
		}
	}//endof while (NULL != fgets(line, sizeof(line) - 1, fp))

	if (1 == port_proto_ver)
	{
		//old rtsp_audio_port is 8554
		rtsp_audio_port = 8554;
		goto errExit;
	}
	else
	{
		rewind(fp);
	}

	while (NULL != fgets(line, sizeof(line) - 1, fp))
	{
		if (1 == sscanf(line, "camera_server_port = %d", &rtsp_audio_port))
		{
			rtsp_audio_port += 4; //rtsp_audio_port=camera_server_port+4 
			break;
		}
	}//endof while (NULL != fgets(line, sizeof(line) - 1, fp))

errExit:

	if (NULL != fp)
	{
		fclose(fp);
		fp = NULL;
	}

	printf("%s,rtsp_audio_port=%d..............\n", __func__, rtsp_audio_port);

	return rtsp_audio_port;
}

int main(int argc, char** argv) {
  // Begin by setting up our usage environment:
  TaskScheduler* scheduler = BasicTaskScheduler::createNew();
  env = BasicUsageEnvironment::createNew(*scheduler);

  UserAuthenticationDatabase* authDB = NULL;
#ifdef ACCESS_CONTROL
  // To implement client access control to the RTSP server, do the following:
  authDB = new UserAuthenticationDatabase;
  authDB->addUserRecord("username1", "password1"); // replace these with real strings
  // Repeat the above with each <username>, <password> that you wish to allow
  // access to the server.
#endif

  //add 2012/11/13 by yjc, add rtsp audio port
  int rtsp_audio_port = get_rtsp_audio_port_from_cfg(PROTO_CONFIG_FILE);
  // Create the RTSP server:
  RTSPServer* rtspServer = RTSPServer::createNew(*env, rtsp_audio_port, authDB);
  if (rtspServer == NULL) {
    *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
    exit(1);
  }

  char const* descriptionString
    = "Session streamed by \"testOnDemandRTSPServer\"";

  // Set up each of the possible streams that can be served by the
  // RTSP server.  Each such stream is implemented using a
  // "ServerMediaSession" object, plus one or more
  // "ServerMediaSubsession" objects for each audio/video substream.

  // A G711 audio stream:
  {
    char const* streamName = "astream1";
    ServerMediaSession* sms
      = ServerMediaSession::createNew(*env, streamName, streamName,
				      descriptionString);
	
    sms->addSubsession(G711AudioStreamServerMediaSubsession
		       ::createNew(*env, reuseFirstSource));
    rtspServer->addServerMediaSession(sms);

    announceStream(rtspServer, sms, streamName, streamName);
  }

#if 0
  // An AMR audio stream:
  {
    char const* streamName = "amrAudioTest";
    char const* inputFileName = "/tmp/fifo.amr";
    ServerMediaSession* sms
      = ServerMediaSession::createNew(*env, streamName, streamName,
				      descriptionString);
    sms->addSubsession(AMRAudioFileServerMediaSubsession
		       ::createNew(*env, inputFileName, reuseFirstSource));
    rtspServer->addServerMediaSession(sms);

    announceStream(rtspServer, sms, streamName, inputFileName);
  }
#endif

  env->taskScheduler().doEventLoop(); // does not return

  return 0; // only to prevent compiler warning
}

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName) {
  char* url = rtspServer->rtspURL(sms);
  UsageEnvironment& env = rtspServer->envir();
  env << "\n\"" << streamName << "\" stream, from the file \""
      << inputFileName << "\"\n";
  env << "Play this stream using the URL \"" << url << "\"\n";
  delete[] url;
}
#endif
