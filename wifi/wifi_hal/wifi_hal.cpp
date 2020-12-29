
#define LOG_TAG "INTEL_WIFI_HAL"

#include <iostream>

#include <log/log.h>

#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

#include "wifi_handle.h"
#include "nl_proxy.h"

class nl_proxy *nl_proxy;

/*
 * init wi-fi backend. 
 */
wifi_error wifi_initialize(wifi_handle* _handle) {

    ALOGI("Wi-Fi Initializing...");

    intel_wifi_handle *handle = new intel_wifi_handle();

    struct nl_sock* socket = nl_socket_alloc();
    if (socket == nullptr) {

        return WIFI_ERROR_OUT_OF_MEMORY;
    }

    nl_socket_set_local_port(socket, 644);

    if (nl_connect(socket, NETLINK_GENERIC)) {

        ALOGE("nl_connect failed.");
        nl_socket_free(socket);
        return WIFI_ERROR_UNINITIALIZED;
    }

    handle->socket = socket;

    // check the wireless driver is loaded successfully.
    if (access("sys/class/net/wlan0", R_OK) != 0) {

        return WIFI_ERROR_UNINITIALIZED;
    }

    interface_info *info = new interface_info();
    if (info == nullptr) {

        return WIFI_ERROR_OUT_OF_MEMORY;
    }

    info->handle = (wifi_handle) handle;
    info->id = if_nametoindex("wlan0");
    std::string("wlan0").copy(info->name, sizeof(info->name));

    handle->interfaces = new interface_info*[1];
    handle->interfaces[0] = info;

    // hardcoded number of interfaces is 1.
    handle->num_interfaces = 1;


    *_handle = (wifi_handle) handle;

    nl_proxy = new class nl_proxy(handle);

    ALOGI("Wi-Fi Initialized");

    return WIFI_SUCCESS;
}

/*
 * Ensure kernel driver state is ready.
 */
wifi_error wifi_wait_for_driver_ready(void) {

    int fd;
    do {
        if ((fd = open("sys/class/net/wlan0", O_RDONLY)) > 2) {

            close(fd);
            return WIFI_SUCCESS;
        }

        // wait 0.1 seconds for next polling.
        usleep(100000);
        ALOGW("Wait for initializing wireless lan.");
    } while (true);

    return WIFI_ERROR_UNKNOWN;
}

void wifi_cleanup(wifi_handle handle, wifi_cleaned_up_handler handler) {


    ALOGE("%s called.", __FUNCTION__);
}

/*
 * infinite loop for execute event.
 */
void wifi_event_loop(wifi_handle _handle) {

    ALOGE("%s called.", __FUNCTION__);

    intel_wifi_handle *handle = (intel_wifi_handle*) _handle;

    struct pollfd fds[2];
    fds[0].fd = nl_socket_get_fd(handle->socket);
    fds[0].events = POLLIN;

    while (true) {

        fds[0].revents = 0;

        int status = poll(fds, 1, -1);

        if (status < 0) {

            ALOGE("event loop error. code: %d", status);
            continue;
        }

        ALOGE("event loop called. revents: %d", fds[0].revents);

    }




}

void wifi_get_error_info(wifi_error error, const char** errorInfo) {


    ALOGE("%s called.", __FUNCTION__);
}

wifi_error wifi_get_supported_feature_set(wifi_interface_handle interfaceHandle, feature_set* featureSet) {

    
    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_concurrency_matrix(wifi_interface_handle, int, feature_set *, int *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_scanning_mac_oui(wifi_interface_handle, unsigned char *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_supported_channels(wifi_handle, int *, wifi_channel *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_is_epr_supported(wifi_handle) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

/*
 * return interface handles.
 */
wifi_error wifi_get_ifaces(wifi_handle _handle, int *num, wifi_interface_handle **interfaces) {

    intel_wifi_handle* handle = (intel_wifi_handle*) _handle;

    *interfaces = (wifi_interface_handle*) handle->interfaces;
    *num = handle->num_interfaces;

    return WIFI_SUCCESS;
}

/*
 * return interface name such as wlan0 by specified interface handle.
 */
wifi_error wifi_get_iface_name(wifi_interface_handle handle, char *name, size_t size) {

    interface_info* info = (interface_info*) handle;
    strlcpy(name, info->name, size);

    return WIFI_SUCCESS;
}

wifi_error wifi_set_iface_event_handler(wifi_request_id,wifi_interface_handle , wifi_event_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_iface_event_handler(wifi_request_id, wifi_interface_handle) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_start_gscan(wifi_request_id, wifi_interface_handle, wifi_scan_cmd_params, wifi_scan_result_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_stop_gscan(wifi_request_id, wifi_interface_handle) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_cached_gscan_results(wifi_interface_handle, byte, int, wifi_cached_scan_results *, int *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_bssid_hotlist(wifi_request_id, wifi_interface_handle, wifi_bssid_hotlist_params, wifi_hotlist_ap_found_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_bssid_hotlist(wifi_request_id, wifi_interface_handle) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_significant_change_handler(wifi_request_id, wifi_interface_handle, wifi_significant_change_params, wifi_significant_change_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_significant_change_handler(wifi_request_id, wifi_interface_handle) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_gscan_capabilities(wifi_interface_handle, wifi_gscan_capabilities *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_link_stats(wifi_interface_handle, wifi_link_layer_params) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_link_stats(wifi_request_id,wifi_interface_handle, wifi_stats_result_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_clear_link_stats(wifi_interface_handle,u32, u32 *, u8, u8 *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_valid_channels(wifi_interface_handle,int, int, wifi_channel *, int *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_rtt_range_request(wifi_request_id, wifi_interface_handle, unsigned, wifi_rtt_config[], wifi_rtt_event_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_rtt_range_cancel(wifi_request_id,  wifi_interface_handle, unsigned, mac_addr[]) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_rtt_capabilities(wifi_interface_handle, wifi_rtt_capabilities *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_rtt_get_responder_info(wifi_interface_handle iface, wifi_rtt_responder *responder_info) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_enable_responder(wifi_request_id id, wifi_interface_handle iface, wifi_channel_info channel_hint, unsigned max_duration_seconds, wifi_rtt_responder *responder_info) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_disable_responder(wifi_request_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_nodfs_flag(wifi_interface_handle, u32) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_start_logging(wifi_interface_handle, u32, u32, u32, u32, char *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_epno_list(wifi_request_id, wifi_interface_handle, const wifi_epno_params *, wifi_epno_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_epno_list(wifi_request_id, wifi_interface_handle) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_country_code(wifi_interface_handle, const char *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_firmware_memory_dump( wifi_interface_handle iface, wifi_firmware_memory_dump_handler handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_log_handler(wifi_request_id id, wifi_interface_handle iface, wifi_ring_buffer_data_handler handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_log_handler(wifi_request_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_alert_handler(wifi_request_id id, wifi_interface_handle iface, wifi_alert_handler handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_alert_handler(wifi_request_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_firmware_version(wifi_interface_handle iface, char *buffer, int buffer_size) {

    // temporary solution...
    strlcpy(buffer, "1.0", buffer_size);
    ALOGE("%s called.", __FUNCTION__);
    return WIFI_SUCCESS;
}

wifi_error wifi_get_ring_buffers_status(wifi_interface_handle iface, u32 *num_rings, wifi_ring_buffer_status *status) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_logger_supported_feature_set(wifi_interface_handle iface, unsigned int *support) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_ring_data(wifi_interface_handle iface, char *ring_name) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_enable_tdls(wifi_interface_handle, mac_addr, wifi_tdls_params *, wifi_tdls_handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_disable_tdls(wifi_interface_handle, mac_addr) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_tdls_status(wifi_interface_handle, mac_addr, wifi_tdls_status *) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_tdls_capabilities(wifi_interface_handle iface, wifi_tdls_capabilities *capabilities) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_driver_version(wifi_interface_handle iface, char *buffer, int buffer_size) {

    strlcpy(buffer, "1.0", buffer_size);
    ALOGE("%s called.", __FUNCTION__);
    return WIFI_SUCCESS;
}

wifi_error wifi_set_passpoint_list(wifi_request_id id, wifi_interface_handle iface, int num, wifi_passpoint_network *networks, wifi_passpoint_event_handler handler) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_passpoint_list(wifi_request_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_lci(wifi_request_id id, wifi_interface_handle iface, wifi_lci_information *lci) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_lcr(wifi_request_id id, wifi_interface_handle iface, wifi_lcr_information *lcr) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_start_sending_offloaded_packet(wifi_request_id id, wifi_interface_handle iface, u16 ether_type, u8 *ip_packet, u16 ip_packet_len, u8 *src_mac_addr, u8 *dst_mac_addr, u32 period_msec) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_stop_sending_offloaded_packet(wifi_request_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_start_rssi_monitoring(wifi_request_id id, wifi_interface_handle iface, s8 max_rssi, s8 min_rssi, wifi_rssi_event_handler eh) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_stop_rssi_monitoring(wifi_request_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_wake_reason_stats(wifi_interface_handle iface, WLAN_DRIVER_WAKE_REASON_CNT *wifi_wake_reason_cnt) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_configure_nd_offload(wifi_interface_handle iface, u8 enable) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_driver_memory_dump(wifi_interface_handle iface, wifi_driver_memory_dump_callbacks callbacks) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_start_pkt_fate_monitoring(wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_tx_pkt_fates(wifi_interface_handle handle, wifi_tx_report *tx_report_bufs, size_t n_requested_fates, size_t *n_provided_fates) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_rx_pkt_fates(wifi_interface_handle handle, wifi_rx_report *rx_report_bufs, size_t n_requested_fates, size_t *n_provided_fates) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_enable_request(transaction_id id, wifi_interface_handle iface, NanEnableRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_disable_request(transaction_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_publish_request(transaction_id id, wifi_interface_handle iface, NanPublishRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_publish_cancel_request(transaction_id id, wifi_interface_handle iface, NanPublishCancelRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_subscribe_request(transaction_id id, wifi_interface_handle iface, NanSubscribeRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_subscribe_cancel_request(transaction_id id, wifi_interface_handle iface, NanSubscribeCancelRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_transmit_followup_request(transaction_id id, wifi_interface_handle iface, NanTransmitFollowupRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_stats_request(transaction_id id, wifi_interface_handle iface, NanStatsRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_config_request(transaction_id id, wifi_interface_handle iface, NanConfigRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_tca_request(transaction_id id, wifi_interface_handle iface, NanTCARequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_beacon_sdf_payload_request(transaction_id id, wifi_interface_handle iface, NanBeaconSdfPayloadRequest* msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_register_handler(wifi_interface_handle iface, NanCallbackHandler handlers) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_get_version(wifi_handle handle, NanVersion* version) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_get_capabilities(transaction_id id, wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_data_interface_create(transaction_id id, wifi_interface_handle iface, char *iface_name) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_data_interface_delete(transaction_id id, wifi_interface_handle iface, char *iface_name) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_data_request_initiator(transaction_id id, wifi_interface_handle iface, NanDataPathInitiatorRequest *msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_data_indication_response(transaction_id id, wifi_interface_handle iface, NanDataPathIndicationResponse *msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_nan_data_end(transaction_id id, wifi_interface_handle iface, NanDataPathEndRequest *msg) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_select_tx_power_scenario(wifi_interface_handle iface, wifi_power_scenario scenario) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_tx_power_scenario(wifi_interface_handle iface) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_packet_filter_capabilities(wifi_interface_handle handle, u32 *version, u32 *max_len) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_packet_filter(wifi_interface_handle handle, const u8 *program, u32 len) {


    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_read_packet_filter(wifi_interface_handle handle, u32 src_offset, u8 *host_dst, u32 length) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_get_roaming_capabilities(wifi_interface_handle handle, wifi_roaming_capabilities *caps) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_enable_firmware_roaming(wifi_interface_handle handle, fw_roaming_state_t state) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_configure_roaming(wifi_interface_handle handle, wifi_roaming_config *roaming_config) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_radio_mode_change_handler(wifi_request_id id, wifi_interface_handle iface, wifi_radio_mode_change_handler eh) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_latency_mode(wifi_interface_handle iface, wifi_latency_mode mode) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_set_thermal_mitigation_mode(wifi_handle handle, wifi_thermal_mode mode, u32 completion_window) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_map_dscp_access_category(wifi_handle handle, u32 start, u32 end, u32 access_category) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_reset_dscp_mapping(wifi_handle handle) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error wifi_virtual_interface_create(wifi_handle handle, const char* ifname, wifi_interface_type iface_type) {

    ALOGE("%s called. ifname: %s, type: %d", __FUNCTION__, ifname, iface_type);
    auto result = nl_proxy->run_cmd_new_interface(ifname, iface_type);
    ALOGE("%s ended. result: %d", __FUNCTION__, result);

    return result;
}

wifi_error wifi_virtual_interface_delete(wifi_handle handle, const char* ifname) {

    ALOGE("%s called.", __FUNCTION__);
    return WIFI_ERROR_NOT_SUPPORTED;
}

wifi_error init_wifi_vendor_hal_func_table(wifi_hal_fn* fn) {

    if (fn == NULL) {
        return WIFI_ERROR_UNKNOWN;
    }

    fn->wifi_initialize = wifi_initialize;
    fn->wifi_wait_for_driver_ready = wifi_wait_for_driver_ready;
    fn->wifi_cleanup = wifi_cleanup;
    fn->wifi_event_loop = wifi_event_loop;
    fn->wifi_get_supported_feature_set = wifi_get_supported_feature_set;
    fn->wifi_get_concurrency_matrix = wifi_get_concurrency_matrix;
    fn->wifi_set_scanning_mac_oui =  wifi_set_scanning_mac_oui;
    fn->wifi_get_ifaces = wifi_get_ifaces;
    fn->wifi_get_iface_name = wifi_get_iface_name;
    fn->wifi_set_iface_event_handler = wifi_set_iface_event_handler;
    fn->wifi_reset_iface_event_handler = wifi_reset_iface_event_handler;
    fn->wifi_start_gscan = wifi_start_gscan;
    fn->wifi_stop_gscan = wifi_stop_gscan;
    fn->wifi_get_cached_gscan_results = wifi_get_cached_gscan_results;
    fn->wifi_set_bssid_hotlist = wifi_set_bssid_hotlist;
    fn->wifi_reset_bssid_hotlist = wifi_reset_bssid_hotlist;
    fn->wifi_set_significant_change_handler = wifi_set_significant_change_handler;
    fn->wifi_reset_significant_change_handler = wifi_reset_significant_change_handler;
    fn->wifi_get_gscan_capabilities = wifi_get_gscan_capabilities;
    fn->wifi_set_link_stats = wifi_set_link_stats;
    fn->wifi_get_link_stats = wifi_get_link_stats;
    fn->wifi_clear_link_stats = wifi_clear_link_stats;
    fn->wifi_get_valid_channels = wifi_get_valid_channels;
    fn->wifi_rtt_range_request = wifi_rtt_range_request;
    fn->wifi_rtt_range_cancel = wifi_rtt_range_cancel;
    fn->wifi_get_rtt_capabilities = wifi_get_rtt_capabilities;
    fn->wifi_rtt_get_responder_info = wifi_rtt_get_responder_info;
    fn->wifi_enable_responder = wifi_enable_responder;
    fn->wifi_disable_responder = wifi_disable_responder;
    fn->wifi_set_nodfs_flag = wifi_set_nodfs_flag;
    fn->wifi_start_logging = wifi_start_logging;
    fn->wifi_set_epno_list = wifi_set_epno_list;
    fn->wifi_reset_epno_list = wifi_reset_epno_list;
    fn->wifi_set_country_code = wifi_set_country_code;
    fn->wifi_enable_tdls = wifi_enable_tdls;
    fn->wifi_disable_tdls = wifi_disable_tdls;
    fn->wifi_get_tdls_status = wifi_get_tdls_status;
    fn->wifi_get_tdls_capabilities = wifi_get_tdls_capabilities;
    fn->wifi_get_firmware_memory_dump = wifi_get_firmware_memory_dump;
    fn->wifi_set_log_handler = wifi_set_log_handler;
    fn->wifi_reset_log_handler = wifi_reset_log_handler;
    fn->wifi_set_alert_handler = wifi_set_alert_handler;
    fn->wifi_reset_alert_handler = wifi_reset_alert_handler;
    fn->wifi_get_firmware_version = wifi_get_firmware_version;
    fn->wifi_get_ring_buffers_status = wifi_get_ring_buffers_status;
    fn->wifi_get_logger_supported_feature_set = wifi_get_logger_supported_feature_set;
    fn->wifi_get_ring_data = wifi_get_ring_data;
    fn->wifi_get_driver_version = wifi_get_driver_version;
    fn->wifi_set_passpoint_list = wifi_set_passpoint_list;
    fn->wifi_reset_passpoint_list = wifi_reset_passpoint_list;
    fn->wifi_set_lci = wifi_set_lci;
    fn->wifi_set_lcr = wifi_set_lcr;
    fn->wifi_start_sending_offloaded_packet = wifi_start_sending_offloaded_packet;
    fn->wifi_stop_sending_offloaded_packet = wifi_stop_sending_offloaded_packet;
    fn->wifi_start_rssi_monitoring = wifi_start_rssi_monitoring;
    fn->wifi_stop_rssi_monitoring = wifi_stop_rssi_monitoring;
    fn->wifi_nan_enable_request = wifi_nan_enable_request;
    fn->wifi_nan_disable_request = wifi_nan_disable_request;
    fn->wifi_nan_publish_request = wifi_nan_publish_request;
    fn->wifi_nan_publish_cancel_request = wifi_nan_publish_cancel_request;
    fn->wifi_nan_subscribe_request = wifi_nan_subscribe_request;
    fn->wifi_nan_subscribe_cancel_request = wifi_nan_subscribe_cancel_request;
    fn->wifi_nan_transmit_followup_request = wifi_nan_transmit_followup_request;
    fn->wifi_nan_stats_request = wifi_nan_stats_request;
    fn->wifi_nan_config_request = wifi_nan_config_request;
    fn->wifi_nan_tca_request = wifi_nan_tca_request;
    fn->wifi_nan_beacon_sdf_payload_request = wifi_nan_beacon_sdf_payload_request;
    fn->wifi_nan_register_handler = wifi_nan_register_handler;
    fn->wifi_nan_get_version = wifi_nan_get_version;
    fn->wifi_set_packet_filter = wifi_set_packet_filter;
    fn->wifi_get_packet_filter_capabilities = wifi_get_packet_filter_capabilities;
    fn->wifi_read_packet_filter = wifi_read_packet_filter;
    fn->wifi_nan_get_capabilities = wifi_nan_get_capabilities;
    fn->wifi_nan_data_interface_create = wifi_nan_data_interface_create;
    fn->wifi_nan_data_interface_delete = wifi_nan_data_interface_delete;
    fn->wifi_nan_data_request_initiator = wifi_nan_data_request_initiator;
    fn->wifi_nan_data_indication_response = wifi_nan_data_indication_response;
    fn->wifi_nan_data_end = wifi_nan_data_end;
    fn->wifi_configure_nd_offload = wifi_configure_nd_offload;
    fn->wifi_get_driver_memory_dump = wifi_get_driver_memory_dump;
    fn->wifi_get_wake_reason_stats = wifi_get_wake_reason_stats;
    fn->wifi_start_pkt_fate_monitoring = wifi_start_pkt_fate_monitoring;
    fn->wifi_get_tx_pkt_fates = wifi_get_tx_pkt_fates;
    fn->wifi_get_rx_pkt_fates = wifi_get_rx_pkt_fates;
    fn->wifi_get_roaming_capabilities = wifi_get_roaming_capabilities;
    fn->wifi_configure_roaming = wifi_configure_roaming;
    fn->wifi_enable_firmware_roaming = wifi_enable_firmware_roaming;
    fn->wifi_select_tx_power_scenario = wifi_select_tx_power_scenario;
    fn->wifi_reset_tx_power_scenario = wifi_reset_tx_power_scenario;
    //fn->wifi_set_radio_mode_change_handler = wifi_set_radio_mode_change_handler;
    fn->wifi_virtual_interface_create = wifi_virtual_interface_create;
    fn->wifi_virtual_interface_delete = wifi_virtual_interface_delete;
    fn->wifi_set_latency_mode = wifi_set_latency_mode;
    fn->wifi_set_thermal_mitigation_mode = wifi_set_thermal_mitigation_mode;

    return WIFI_SUCCESS;
}


