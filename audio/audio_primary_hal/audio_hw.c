

#define LOG_TAG "THINKPAD-AUDIO-HAL"

#include <pthread.h>
#include <stdlib.h>

#include <log/log.h>

#include "audio_hw.h"
#include "audio_io.h"

static pthread_mutex_t adev_init_lock = PTHREAD_MUTEX_INITIALIZER;
static struct audio_device *audio_device = NULL;



static int adev_init_check(const struct audio_hw_device *dev __unused) {

    // no-op.
    return 0;
}

static int adev_set_voice_volume(struct audio_hw_device *dev, float volume) {

    struct audio_device *adev = (struct audio_device *)dev;

    pthread_mutex_lock(&adev->lock);
    
    adev->voice_volume = volume;
    
    pthread_mutex_unlock(&adev->lock);

    ALOGD("%s called. volume: %f", __func__, volume);
    return 0;
}

static int adev_set_master_volume(struct audio_hw_device *dev __unused, float volume) {

    ALOGD("%s called. volume: %f", __func__, volume);
    return -ENOSYS;
}

static int adev_get_master_volume(struct audio_hw_device *dev __unused, float *volume __unused) {

    ALOGD("%s called.", __func__);
    return -ENOSYS;
}

static int adev_set_master_mute(struct audio_hw_device *dev __unused, bool muted) {

    ALOGD("%s called. mute: %d", __func__, muted);
    return -ENOSYS;
}

static int adev_get_master_mute(struct audio_hw_device *dev __unused, bool *muted __unused) {

    ALOGD("%s called.", __func__);
    return -ENOSYS;
}

static int adev_set_mode(struct audio_hw_device *dev, audio_mode_t mode) {

    struct audio_device *adev = (struct audio_device *)dev;

    pthread_mutex_lock(&adev->lock);
    
    if (adev->mode != mode) {

        adev->mode = mode;
    }
    
    pthread_mutex_unlock(&adev->lock);

    ALOGE("%s called. mode: %d", __func__, mode);
    return 0;
}


static int adev_set_mic_mute(struct audio_hw_device *dev, bool state) {
  
    struct audio_device *adev = (struct audio_device *)dev;

    pthread_mutex_lock(&adev->lock);
    
    adev->mic_muted = state;
    
    pthread_mutex_unlock(&adev->lock);
    
    ALOGD("%s called. state: %d", __func__, state);
    return 0;
}

static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state) {
    
    struct audio_device *adev = (struct audio_device *)dev;

    *state = adev->mic_muted;

    ALOGD("%s called.", __func__);
    return 0;
}

static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs) {

    ALOGE("%s called. kvpairs: %s", __func__, kvpairs);
    return -ENOSYS;
}

static char* adev_get_parameters(const struct audio_hw_device *dev, const char *keys) {

    ALOGE("%s called. keys: %s", __func__, keys);
    return strdup("");
}

static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev __unused, const struct audio_config *config) {

    ALOGE("%s called.", __func__);
    return 0;
}

static int adev_open_output_stream(struct audio_hw_device *dev, audio_io_handle_t handle, audio_devices_t devices, audio_output_flags_t flags, struct audio_config *config, struct audio_stream_out **stream_out, const char *address __unused) {

    struct stream_out *out = malloc(sizeof(struct stream_out));
    if (out == NULL) {

        return -ENOMEM;
    }

    out->stream.common.get_sample_rate = out_get_sample_rate;
    out->stream.common.set_sample_rate = out_set_sample_rate;
    out->stream.common.get_buffer_size = out_get_buffer_size;
    out->stream.common.get_channels = out_get_channels;
    out->stream.common.get_format = out_get_format;
    out->stream.common.set_format = out_set_format;
    out->stream.common.standby = out_standby;
    out->stream.common.dump = out_dump;
    out->stream.common.set_parameters = out_set_parameters;
    out->stream.common.get_parameters = out_get_parameters;
    out->stream.common.add_audio_effect = out_add_audio_effect;
    out->stream.common.remove_audio_effect = out_remove_audio_effect;
    out->stream.get_latency = out_get_latency;
    out->stream.set_volume = out_set_volume;
    out->stream.write = out_write;
    out->stream.get_render_position = out_get_render_position;
    out->stream.get_next_write_timestamp = out_get_next_write_timestamp;

    out->sample_rate = config->sample_rate;
    out->channel_mask = config->channel_mask;
    out->format = config->format;
    out->frame_count = samples_per_milliseconds(10, out->sample_rate, 1);

    pthread_mutex_init(&out->lock, (const pthread_mutexattr_t*) NULL);

    ALOGD("%s called. channel_mask: %d, format: %d, frame_count: %d, sample_rate: %d", __func__, config->channel_mask, config->format, config->frame_count, config->sample_rate);

    *stream_out = &out->stream;
    return 0;
}

static void adev_close_output_stream(struct audio_hw_device *dev __unused, struct audio_stream_out *stream) {

    ALOGD("%s called.", __func__);
    free(stream);
}

static int adev_open_input_stream(struct audio_hw_device *dev, audio_io_handle_t handle, audio_devices_t devices, struct audio_config *config, struct audio_stream_in **stream_in, audio_input_flags_t flags, const char *address __unused, audio_source_t source ) {

    struct stream_in *in = malloc(sizeof(struct stream_in));
    if (in == NULL) {

        return -ENOMEM;
    }
    
    in->stream.common.get_sample_rate = in_get_sample_rate;
    in->stream.common.set_sample_rate = in_set_sample_rate;
    in->stream.common.get_buffer_size = in_get_buffer_size;
    in->stream.common.get_channels = in_get_channels;
    in->stream.common.get_format = in_get_format;
    in->stream.common.set_format = in_set_format;
    in->stream.common.standby = in_standby;
    in->stream.common.dump = in_dump;
    in->stream.common.set_parameters = in_set_parameters;
    in->stream.common.get_parameters = in_get_parameters;
    in->stream.common.add_audio_effect = in_add_audio_effect;
    in->stream.common.remove_audio_effect = in_remove_audio_effect;
    in->stream.set_gain = in_set_gain;
    in->stream.read = in_read;
    in->stream.get_input_frames_lost = in_get_input_frames_lost;
    
    in->stream.update_sink_metadata = in_update_sink_metadata;

    in->sample_rate = config->sample_rate;
    in->channel_mask = config->channel_mask;
    in->format = config->format;
    in->frame_count = samples_per_milliseconds(10, in->sample_rate, 1);

    pthread_mutex_init(&in->lock, (const pthread_mutexattr_t*) NULL);

    ALOGD("%s called. channel_mask: %d, format: %d, frame_count: %d, sample_rate: %d", __func__, config->channel_mask, config->format, config->frame_count, config->sample_rate);
    
    *stream_in = &in->stream;

    return 0;
}

static void adev_close_input_stream(struct audio_hw_device *dev __unused, struct audio_stream_in *stream) {


    ALOGD("%s called.", __func__);
    free(stream);
}

static int adev_dump(const audio_hw_device_t *device __unused, int fd __unused) {


    ALOGE("%s called.", __func__);
    return 0;
}

static int adev_get_microphones(const struct audio_hw_device *dev, struct audio_microphone_characteristic_t *mic_array, size_t *mic_count) {

    
    ALOGE("%s called.", __func__);
    return -ENOSYS;
}

                                
static int adev_close(hw_device_t *device) {

    pthread_mutex_lock(&adev_init_lock);

    free(device);
    audio_device = NULL;

    pthread_mutex_unlock(&adev_init_lock);
    return 0;
}

static int adev_open(const hw_module_t *module, const char *name, hw_device_t **device) {

    ALOGI("adev_open called. %s", name);

    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0) {

        return -EINVAL;
    }

    pthread_mutex_lock(&adev_init_lock);

    audio_device = malloc(sizeof(struct audio_device));

    pthread_mutex_init(&audio_device->lock, (const pthread_mutexattr_t*) NULL);

    audio_device->device.common.tag = HARDWARE_DEVICE_TAG;
    audio_device->device.common.version = AUDIO_DEVICE_API_VERSION_2_0;
    audio_device->device.common.module = (struct hw_module_t *)module;
    audio_device->device.common.close = adev_close;

    audio_device->device.init_check = adev_init_check;
    audio_device->device.set_voice_volume = adev_set_voice_volume;
    audio_device->device.set_master_volume = adev_set_master_volume;
    audio_device->device.get_master_volume = adev_get_master_volume;
    audio_device->device.set_master_mute = adev_set_master_mute;
    audio_device->device.get_master_mute = adev_get_master_mute;
    audio_device->device.set_mode = adev_set_mode;
    audio_device->device.set_mic_mute = adev_set_mic_mute;
    audio_device->device.get_mic_mute = adev_get_mic_mute;
    audio_device->device.set_parameters = adev_set_parameters;
    audio_device->device.get_parameters = adev_get_parameters;
    audio_device->device.get_input_buffer_size = adev_get_input_buffer_size;
    audio_device->device.open_output_stream = adev_open_output_stream;
    audio_device->device.close_output_stream = adev_close_output_stream;
    audio_device->device.open_input_stream = adev_open_input_stream;
    audio_device->device.close_input_stream = adev_close_input_stream;
    audio_device->device.dump = adev_dump;
    audio_device->device.get_microphones = adev_get_microphones;
    
    *device = &audio_device->device.common;

    pthread_mutex_unlock(&adev_init_lock);

    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    .open = adev_open,
};

struct audio_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = AUDIO_MODULE_API_VERSION_0_1,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = AUDIO_HARDWARE_MODULE_ID,
        .name = "ThinkPad Audio HAL",
        .author = "mrtska",
        .methods = &hal_module_methods,
    },
};
