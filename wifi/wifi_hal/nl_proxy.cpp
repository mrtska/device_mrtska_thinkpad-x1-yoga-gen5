
#define LOG_TAG "INTEL-WIFI-HAL nl_proxy"

#include "nl_proxy.h"
#include <log/log.h>


wifi_error nl_proxy_message::create(int family, uint8_t cmd, int flags, int hdrlen) {

    if (message != nullptr) {

        nlmsg_free(message);
    }

    message = nlmsg_alloc();
    if (message == nullptr) {

        return WIFI_ERROR_OUT_OF_MEMORY;
    } else {

        genlmsg_put(message, NL_AUTO_PORT, NL_AUTO_SEQ, family, hdrlen, flags, cmd, 0);
        return WIFI_SUCCESS;
    }
}


wifi_error nl_proxy::createMessage(int family, uint8_t cmd, int flags, int hdrlen) {

    return message->create(family, cmd, flags, hdrlen);
}

static int error_handler(struct sockaddr_nl *nla, struct nlmsgerr *nlerr, void *arg) {

    int *status = (int*) arg;

    *status = nlerr->error;
    ALOGE("error_handle called.");
    return NL_STOP;
}

static int ack_handler(struct nl_msg *msg, void *arg) {

    int *status = (int*) arg;
    *status = 0;

    ALOGE("ack_handler called.");
    return NL_STOP;
}

static int finish_handler(struct nl_msg *msg, void *arg) {

    int *status = (int*) arg;

    *status = 0;

    ALOGE("finish_handler called.");
    return NL_STOP;
}

wifi_error nl_proxy::run_cmd_new_interface(const char* ifname, wifi_interface_type iface_type) {

    wifi_error result = createMessage(0, NL80211_CMD_NEW_INTERFACE, 0, 0);
    if (result != WIFI_SUCCESS) {

        ALOGE("createMessage failed. result: %d", result);
        return result;
    }

    nl80211_iftype type;
    switch (iface_type) {
        case WIFI_INTERFACE_STA:
            type = NL80211_IFTYPE_STATION;
            break;
        case WIFI_INTERFACE_TYPE_AP:
            type = NL80211_IFTYPE_AP;
            break;
        case WIFI_INTERFACE_TYPE_P2P:
            type = NL80211_IFTYPE_P2P_DEVICE;
            break;
        case WIFI_INTERFACE_TYPE_NAN:
            type = NL80211_IFTYPE_NAN;
            break;
        default:
            ALOGE("Unexpected interface type specified. %d", iface_type);
            return WIFI_ERROR_UNKNOWN;
    }

    message->put_u32(NL80211_ATTR_IFINDEX, if_nametoindex(ifname));
    message->put_string(NL80211_ATTR_IFNAME, ifname);
    message->put_u32(NL80211_ATTR_IFTYPE, type);

    struct nl_cb *callback = nl_cb_alloc(NL_CB_DEFAULT);
    if (callback == nullptr) {

        return WIFI_ERROR_OUT_OF_MEMORY;
    }

    int status = nl_send_auto_complete(handle->socket, message->get_raw_message());
    if (status < 0) {

        ALOGE("Failed to set auto complete to message. status: %d", status);
        return WIFI_ERROR_UNKNOWN;
    }

    status = 1;

    nl_cb_err(callback, NL_CB_CUSTOM, error_handler, &status);
    nl_cb_set(callback, NL_CB_FINISH, NL_CB_CUSTOM, ack_handler, &status);
    nl_cb_set(callback, NL_CB_ACK, NL_CB_CUSTOM, finish_handler, &status);

    while (status > 0) {

        nl_recvmsgs(handle->socket, callback);
    }

    if (status < 0) {

        ALOGE("Error occrred when recvmsgs ended. status: %d", status);
        return WIFI_ERROR_UNKNOWN;
    }

    message->destroy();

    return result;
}
