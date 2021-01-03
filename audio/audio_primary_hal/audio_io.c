
#define LOG_TAG "THINKPAD-AUDIO-HAL"

#include "audio_io.h"


#include <log/log.h>


struct pcm_config pcm_config_out = {

    .channels = 2,
    .rate = 48000,
    .period_size = 512,
    .period_count = 8,
    .format = PCM_FORMAT_S16_LE,
    .start_threshold = 512 * 8,
};


uint32_t out_get_sample_rate(const struct audio_stream *stream) {

    const struct stream_out *out = (const struct stream_out *)stream;

    // ALOGV("%s called. sample_rate: %d", __func__, out->sample_rate);
    return out->sample_rate;
}

int out_set_sample_rate(struct audio_stream *stream, uint32_t rate) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

size_t out_get_buffer_size(const struct audio_stream *stream) {

    const struct stream_out *out = (const struct stream_out *)stream;

    size_t buffer_size = out->frame_count * audio_stream_out_frame_size(&out->stream);
    // ALOGD("%s called. buffer size: %d", __func__, buffer_size);
    return buffer_size;
}

audio_channel_mask_t out_get_channels(const struct audio_stream *stream) {

    const struct stream_out *out = (const struct stream_out *)stream;

    // ALOGD("%s called. channel_mask: %d", __func__, out->channel_mask);
    return out->channel_mask;
}

audio_format_t out_get_format(const struct audio_stream *stream) {

    const struct stream_out *out = (const struct stream_out *)stream;

    // ALOGD("%s called. format: %d", __func__, out->format);
    return out->format;
}

int out_set_format(struct audio_stream *stream, audio_format_t format) {

    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

int out_standby(struct audio_stream *stream) {

    struct stream_out *out = (const struct stream_out *)stream;

    if (!out->standby) {

        pthread_mutex_lock(&out->lock);

        if (out->pcm) {

            pcm_close(out->pcm);
            out->pcm = NULL;
        }
        out->standby = true;

        pthread_mutex_unlock(&out->lock);
    }

    ALOGD("%s called.", __func__);
    return 0;
}

int out_dump(const struct audio_stream *stream, int fd) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

int out_set_parameters(struct audio_stream *stream, const char *kvpairs) {


    ALOGE("%s called. kvpairs: %s", __func__, kvpairs);
    return -ENOSYS;
}

char* out_get_parameters(const struct audio_stream *stream, const char *keys) {

    ALOGE("%s called. keys: %s", __func__, keys);
    return strdup("");
}

uint32_t out_get_latency(const struct audio_stream_out *stream) {

    ALOGD("%s called.", __func__);
    return 10;
}

int out_set_volume(struct audio_stream_out *stream, float left, float right) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

ssize_t out_write(struct audio_stream_out *stream, const void* buffer, size_t bytes) {

    struct stream_out *out = (const struct stream_out *)stream;

    size_t frame_size = audio_stream_out_frame_size(stream);
    int16_t *in_buffer = (int16_t *)buffer;
    const size_t frames =  bytes / frame_size;

    pthread_mutex_lock(&out->device->lock);
    pthread_mutex_lock(&out->lock);

    if (out->standby) {

        out->pcm = pcm_open(SOUNDCARD_ID, SOUNDCARD_DEVICE_ID, PCM_OUT | PCM_NORESTART, &pcm_config_out);
        
        out->standby = false;
    }

    int ret = pcm_write(out->pcm, in_buffer, frame_size * frames);

    pthread_mutex_unlock(&out->lock);
    pthread_mutex_unlock(&out->device->lock);

    // ALOGE("%s called. buf: %p, bytes: %d, ret: %d", __func__, buffer, bytes, ret);

    if (ret == -EPIPE) {

        return 0;
    }

    return bytes;
}

int out_get_render_position(const struct audio_stream_out *stream, uint32_t *dsp_frames) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

int out_get_next_write_timestamp(const struct audio_stream_out *stream, int64_t *timestamp) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}



uint32_t in_get_sample_rate(const struct audio_stream *stream) {

    const struct stream_in *in = (const struct stream_in *)stream;

    ALOGD("%s called. sample_rate: %d", __func__, in->sample_rate);
    return in->sample_rate;
}

int in_set_sample_rate(struct audio_stream *stream, uint32_t rate) {

    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

size_t in_get_buffer_size(const struct audio_stream *stream) {

    const struct stream_in *in = (const struct stream_in *)stream;

    size_t buffer_size = in->frame_count * audio_stream_in_frame_size(&in->stream);

    ALOGD("%s called. buffer_size: %d", __func__, buffer_size);
    return buffer_size;
}

audio_channel_mask_t in_get_channels(const struct audio_stream *stream) {

    const struct stream_in *in = (const struct stream_in *)stream;

    ALOGD("%s called. channel_mask: %d", __func__, in->channel_mask);
    return in->channel_mask;
}

audio_format_t in_get_format(const struct audio_stream *stream) {

    const struct stream_in *in = (const struct stream_in *)stream;

    ALOGD("%s called. format: %d", __func__, in->format);
    return in->format;
}

int in_set_format(struct audio_stream *stream, audio_format_t format) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

int in_standby(struct audio_stream *stream) {

    struct stream_in *in = (struct stream_in *)stream;

    if (!in->standby) {

        pthread_mutex_lock(&in->lock);

        in->standby = true;

        pthread_mutex_unlock(&in->lock);
    }
    ALOGD("%s called.", __func__);

    return 0;
}

int in_dump(const struct audio_stream *stream, int fd) {

    const struct stream_in *in = (const struct stream_in *)stream;

    ALOGD("%s called.", __func__);

    dprintf(fd, "Standby: %d\n", in->standby);

    return 0;
}

int in_set_parameters(struct audio_stream *stream, const char *kvpairs) {

    ALOGE("%s called. kvpairs: %s", __func__, kvpairs);

    return -ENOSYS;
}

char* in_get_parameters(const struct audio_stream *stream, const char *keys) {

    ALOGE("%s called. keys: %s", __func__, keys);
    return strdup("");
}

int in_set_gain(struct audio_stream_in *stream, float gain) {

    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

ssize_t in_read(struct audio_stream_in *stream, void* buffer, size_t bytes) {

    ALOGE("%s called.", __func__);
    return 0;
}

uint32_t in_get_input_frames_lost(struct audio_stream_in *stream) {


    ALOGE("%s called.", __func__);
    return 0;
}

int in_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

int in_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect) {


    ALOGE("%s called.", __func__);
    return -ENOSYS;
}
 
void in_update_sink_metadata(struct audio_stream_in *stream, const struct sink_metadata* sink_metadata) {

    ALOGE("%s called. count: %d", __func__, sink_metadata->track_count);
}
