
#pragma once

#include <pthread.h>

#include <hardware/audio.h>
#include <tinyalsa/asoundlib.h>

#define SOUNDCARD_ID 1
#define SOUNDCARD_DEVICE_ID 0


struct audio_device {

    struct audio_hw_device device;

    pthread_mutex_t lock;

    // audio mode
    audio_mode_t mode;

    bool mic_muted;

    float voice_volume;

    struct mixer *mixer;
};
