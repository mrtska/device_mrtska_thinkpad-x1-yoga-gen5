#pragma once

#include <hardware_legacy/wifi_hal.h>
#include <netlink/netlink.h>

typedef struct {
    wifi_handle handle;                             // handle to wifi data
    char name[IFNAMSIZ+1];                          // interface name + trailing null
    int  id;                                        // id to use when talking to driver
} interface_info;

typedef struct intel_wifi_handle_s {

    struct nl_sock* socket;

    // wifi interfaces.
    interface_info** interfaces;
    int num_interfaces;

} intel_wifi_handle;

