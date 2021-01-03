
#pragma once

#include <pthread.h>

#include <hardware/audio.h>


struct audio_device {

    struct audio_hw_device device;

    pthread_mutex_t lock;

    // audio mode
    audio_mode_t mode;

    bool mic_muted;

    float voice_volume;

};
