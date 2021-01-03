#pragma once

#include <pthread.h>

#include <hardware/audio.h>

#include "audio_hw.h"


struct stream_out {

    struct audio_stream_out stream;
    pthread_mutex_t lock;

    struct audio_device *device;

    uint32_t sample_rate;
    audio_channel_mask_t channel_mask;
    audio_format_t format;
    size_t frame_count;

    struct pcm *pcm;

    bool standby;
};

struct stream_in {

    struct audio_stream_in stream;
    pthread_mutex_t lock;

    struct audio_device *device;

    uint32_t sample_rate;
    audio_channel_mask_t channel_mask;
    audio_format_t format;
    size_t frame_count;

    bool standby;
};

static inline size_t samples_per_milliseconds(size_t milliseconds, uint32_t sample_rate, size_t channel_count) {
    
    return milliseconds * sample_rate * channel_count / 1000;
}

// stream output functions.
uint32_t out_get_sample_rate(const struct audio_stream *stream);
int out_set_sample_rate(struct audio_stream *stream, uint32_t rate);
size_t out_get_buffer_size(const struct audio_stream *stream);
audio_channel_mask_t out_get_channels(const struct audio_stream *stream);
audio_format_t out_get_format(const struct audio_stream *stream);
int out_set_format(struct audio_stream *stream, audio_format_t format);
int out_standby(struct audio_stream *stream);
int out_dump(const struct audio_stream *stream, int fd);
int out_set_parameters(struct audio_stream *stream, const char *kvpairs);
char* out_get_parameters(const struct audio_stream *stream, const char *keys);
uint32_t out_get_latency(const struct audio_stream_out *stream);
int out_set_volume(struct audio_stream_out *stream, float left, float right);
ssize_t out_write(struct audio_stream_out *stream, const void* buffer, size_t bytes);
int out_get_render_position(const struct audio_stream_out *stream, uint32_t *dsp_frames);
int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect);
int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect);
int out_get_next_write_timestamp(const struct audio_stream_out *stream, int64_t *timestamp);

// stream input functions.
uint32_t in_get_sample_rate(const struct audio_stream *stream);
int in_set_sample_rate(struct audio_stream *stream, uint32_t rate);
size_t in_get_buffer_size(const struct audio_stream *stream);
audio_channel_mask_t in_get_channels(const struct audio_stream *stream);
audio_format_t in_get_format(const struct audio_stream *stream);
int in_set_format(struct audio_stream *stream, audio_format_t format);
int in_standby(struct audio_stream *stream);
int in_dump(const struct audio_stream *stream, int fd);
int in_set_parameters(struct audio_stream *stream, const char *kvpairs);
char * in_get_parameters(const struct audio_stream *stream, const char *keys);
int in_set_gain(struct audio_stream_in *stream, float gain);
ssize_t in_read(struct audio_stream_in *stream, void* buffer, size_t bytes);
uint32_t in_get_input_frames_lost(struct audio_stream_in *stream);
int in_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect);
int in_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect);
void in_update_sink_metadata(struct audio_stream_in *stream, const struct sink_metadata* sink_metadata);


