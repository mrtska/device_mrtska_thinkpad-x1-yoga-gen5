


#define LOG_TAG "RIL"

#include <log/log.h>

#include <telephony/ril.h>




void onRequest(int request, void *data, size_t datalen, RIL_Token t) {

    RLOGE("%s called. request: %d", __func__, request);

}

RIL_RadioState currentState() {

    RLOGE("%s called.", __func__);
    return RADIO_STATE_UNAVAILABLE;
}

int onSupports(int requestCode) {

    RLOGE("%s called.", __func__);
    return 0;
}

void onCancel(RIL_Token t) {

    RLOGE("%s called.", __func__);

}

const char *getVersion() {

    RLOGE("%s called.", __func__);
    return "1.0";
}

static const RIL_RadioFunctions FUNCTIONS = {
    RIL_VERSION,
    onRequest,
    currentState,
    onSupports,
    onCancel,
    getVersion
};

const RIL_RadioFunctions *RIL_Init(const struct RIL_Env *env, int argc, char **argv) {

    RLOGE("%s called!!, argc: %d, argv: %s, %s", __func__, argc, argv[1], argv[2]);

    return &FUNCTIONS;
}










