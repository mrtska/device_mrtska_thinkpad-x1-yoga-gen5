
#pragma once

#include <hardware_legacy/wifi_hal.h>
#include <netlink/netlink.h>
#include <netlink/msg.h>
#include <netlink/attr.h>
#include <netlink/handlers.h>
#include <netlink/genl/genl.h>

#include <linux/nl80211.h>

#include <string>

#include "wifi_handle.h"

class nl_proxy_message {

private:
    struct nl_msg *message;
public:

    wifi_error create(int family, uint8_t cmd, int flags, int hdrlen);

    void destroy() {

        if (message != nullptr) {

            nlmsg_free(message);
        }
    }

    wifi_error put_u32(int attribute, uint32_t value) {

        return nla_put_u32(message, attribute, value) == 0 ? WIFI_SUCCESS : WIFI_ERROR_UNKNOWN;
    };
    
    wifi_error put_string(int attribute, const char *value) {

        return nla_put_string(message, attribute, value) == 0 ? WIFI_SUCCESS : WIFI_ERROR_UNKNOWN;
    };

    struct nl_msg* get_raw_message() {

        return this->message;
    }
};



class nl_proxy {

private:


    nl_proxy_message *message = new nl_proxy_message();

    intel_wifi_handle *handle;

public:

    nl_proxy(intel_wifi_handle *handle) {

        this->handle = handle;
    }

    /*
     * Create libnl message.
     */
    wifi_error createMessage(int family, uint8_t cmd, int flags, int hdrlen);

    wifi_error run_cmd_new_interface(const char* ifname, wifi_interface_type iface_type);








};









