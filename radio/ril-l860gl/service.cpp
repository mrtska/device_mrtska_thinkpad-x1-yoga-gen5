
#define LOG_TAG "android.hardware.radio@1.5-radio-service.l860gl"

#include <log/log.h>


#include <android/hardware/radio/1.5/IRadioResponse.h>
#include <android/hardware/radio/1.5/IRadioIndication.h>
#include <android/hardware/radio/1.5/types.h>

#include "radio.h"

#include <hidl/HidlTransportSupport.h>

using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::hardware::radio::V1_5::IRadio;
using android::sp;
using android::status_t;

int main() {

    configureRpcThreadpool(1, true);

    RLOGI("service starting.");

    sp<IRadio> radio = new RadioImpl;
    status_t status = radio->registerAsService("slot1");

    if (status != android::OK) {
    
        RLOGE("Failed to register service. status: %d", status);
    }

    joinRpcThreadpool();
    RLOGI("service exiting...");

    return 0;
}

