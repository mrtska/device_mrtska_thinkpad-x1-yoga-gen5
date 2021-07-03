#pragma once

#include <android/hardware/radio/1.5/IRadio.h>
#include <android/hardware/radio/1.5/IRadioResponse.h>
#include <android/hardware/radio/1.5/IRadioIndication.h>
#include <android/hardware/radio/1.5/types.h>
#include <hidl/Status.h>

using namespace android::hardware::radio;

using ::android::hardware::Void;
using ::android::hardware::hidl_vec;
using ::android::hardware::hidl_string;
using ::android::hardware::Return;
using android::sp;

struct RadioImpl : public V1_5::IRadio {

    sp<V1_5::IRadioResponse> radioResponse;
    sp<V1_5::IRadioIndication> radioIndication;

    /**
     * Set response functions for radio requests & radio indications.
     *
     * @param radioResponse Object containing response functions
     * @param radioIndication Object containing radio indications
     */
    Return<void> setResponseFunctions(const ::android::sp<::android::hardware::radio::V1_0::IRadioResponse>& radioResponse, const ::android::sp<::android::hardware::radio::V1_0::IRadioIndication>& radioIndication) override;

    /**
     * Requests status of the ICC card
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getIccCardStatusResponse()
     *
     */
    Return<void> getIccCardStatus(int32_t serial) override;

    /**
     * Supplies ICC PIN. Only called if CardStatus has AppState.PIN state
     *
     * @param serial Serial number of request.
     * @param pin PIN value
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *
     * Response function is IRadioResponse.supplyIccPinForAppResponse()
     *
     */
    Return<void> supplyIccPinForApp(int32_t serial, const ::android::hardware::hidl_string& pin, const ::android::hardware::hidl_string& aid) override;

    /**
     * Supplies ICC PUK and new PIN.
     *
     * @param serial Serial number of request.
     * @param puk PUK value
     * @param pin New PIN value
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *
     * Response function is IRadioResponse.supplyIccPukForAppResponse()
     *
     */
    Return<void> supplyIccPukForApp(int32_t serial, const ::android::hardware::hidl_string& puk, const ::android::hardware::hidl_string& pin, const ::android::hardware::hidl_string& aid) override;

    /**
     * Supplies ICC PIN2. Only called following operation where SIM_PIN2 was
     * returned as a a failure from a previous operation.
     *
     * @param serial Serial number of request.
     * @param pin2 PIN2 value
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *
     * Response function is IRadioResponse.supplyIccPin2ForAppResponse()
     *
     */
    Return<void> supplyIccPin2ForApp(int32_t serial, const ::android::hardware::hidl_string& pin2, const ::android::hardware::hidl_string& aid) override;

    /**
     * Supplies ICC PUK2 and new PIN2.
     *
     * @param serial Serial number of request.
     * @param puk2 PUK2 value
     * @param pin2 New PIN2 value
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *
     * Response function is IRadioResponse.supplyIccPuk2ForAppResponse()
     *
     */
    Return<void> supplyIccPuk2ForApp(int32_t serial, const ::android::hardware::hidl_string& puk2, const ::android::hardware::hidl_string& pin2, const ::android::hardware::hidl_string& aid) override;

    /**
     * Supplies old ICC PIN and new PIN.
     *
     * @param serial Serial number of request.
     * @param oldPin Old pin value
     * @param newPin New pin value
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *
     * Response function is IRadioResponse.changeIccPinForAppResponse()
     *
     */
    Return<void> changeIccPinForApp(int32_t serial, const ::android::hardware::hidl_string& oldPin, const ::android::hardware::hidl_string& newPin, const ::android::hardware::hidl_string& aid) override;

    /**
     * Supplies old ICC PIN2 and new PIN2.
     *
     * @param serial Serial number of request.
     * @param oldPin2 Old pin2 value
     * @param newPin2 New pin2 value
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *
     * Response function is IRadioResponse.changeIccPin2ForAppResponse()
     *
     */
    Return<void> changeIccPin2ForApp(int32_t serial, const ::android::hardware::hidl_string& oldPin2, const ::android::hardware::hidl_string& newPin2, const ::android::hardware::hidl_string& aid) override;

    /**
     * Requests that network personalization be deactivated
     *
     * @param serial Serial number of request.
     * @param netPin Network depersonlization code
     *
     * Response function is IRadioResponse.supplyNetworkDepersonalizationResponse()
     *
     */
    Return<void> supplyNetworkDepersonalization(int32_t serial, const ::android::hardware::hidl_string& netPin) override;

    /**
     * Requests current call list
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getCurrentCallsResponse()
     *
     */
    Return<void> getCurrentCalls(int32_t serial) override;

    /**
     * Initiate voice call.
     * This method is never used for supplementary service codes
     *
     * @param serial Serial number of request.
     * @param dialInfo Dial struct
     *
     * Response function is IRadioResponse.dialResponse()
     *
     */
    Return<void> dial(int32_t serial, const ::android::hardware::radio::V1_0::Dial& dialInfo) override;

    /**
     * Get the SIM IMSI
     * Only valid when radio state is "RADIO_STATE_ON"
     *
     * @param serial Serial number of request.
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *
     * Response function is IRadioResponse.getImsiForAppResponse()
     *
     */
    Return<void> getImsiForApp(int32_t serial, const ::android::hardware::hidl_string& aid) override;

    /**
     * Hang up a specific line (like AT+CHLD=1x)
     * After this HANGUP request returns, Radio must show the connection is NOT
     * active anymore in next requestGetCurrentCalls query.
     *
     * @param serial Serial number of request.
     * @param gsmIndex Connection index (value of 'x' in CHLD above)
     *
     * Response function is IRadioResponse.hangupResponse()
     *
     */
    Return<void> hangup(int32_t serial, int32_t gsmIndex) override;

    /**
     * Hang up waiting or held (like AT+CHLD=0)
     * After this HANGUP request returns, Radio must show the connection is NOT
     * active anymore in next getCurrentCalls() query.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.hangupWaitingOrBackgroundResponse()
     *
     */
    Return<void> hangupWaitingOrBackground(int32_t serial) override;

    /**
     * Hang up waiting or held (like AT+CHLD=1)
     * After this HANGUP request returns, Radio must show the connection is NOT
     * active anymore in next getCurrentCalls query.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.hangupForegroundResumeBackgroundResponse()
     *
     */
    Return<void> hangupForegroundResumeBackground(int32_t serial) override;

    /**
     * Switch waiting or holding call and active call (like AT+CHLD=2)
     * State transitions must be as follows:
     *
     * Call transitions must happen as shown below.
     *
     *   BEFORE                               AFTER
     * Call 1   Call 2                 Call 1       Call 2
     * ACTIVE   HOLDING                HOLDING     ACTIVE
     * ACTIVE   WAITING                HOLDING     ACTIVE
     * HOLDING  WAITING                HOLDING     ACTIVE
     * ACTIVE   IDLE                   HOLDING     IDLE
     * IDLE     IDLE                   IDLE        IDLE
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.switchWaitingOrHoldingAndActiveResponse()
     *
     */
    Return<void> switchWaitingOrHoldingAndActive(int32_t serial) override;

    /**
     * Conference holding and active (like AT+CHLD=3)
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.conferenceResponse()
     *
     */
    Return<void> conference(int32_t serial) override;

    /**
     * Send UDUB (user determined user busy) to ringing or
     * waiting call answer)
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.rejectCallResponse()
     *
     */
    Return<void> rejectCall(int32_t serial) override;

    /**
     * Requests the failure cause code for the most recently terminated call.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getLastCallFailCauseResponse()
     *
     */
    Return<void> getLastCallFailCause(int32_t serial) override;

    /**
     * Requests current signal strength and associated information.
     * Must succeed if radio is on.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getSignalStrengthResponse()
     */
    Return<void> getSignalStrength(int32_t serial) override;

    /**
     * Request current voice registration state
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getVoiceRegistrationStateResponse()
     */
    Return<void> getVoiceRegistrationState(int32_t serial) override;

    /**
     * Request current data registration state
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getDataRegistrationStateResponse()
     */
    Return<void> getDataRegistrationState(int32_t serial) override;

    /**
     * Request current operator ONS or EONS
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getOperatorResponse()
     */
    Return<void> getOperator(int32_t serial) override;

    /**
     * Toggle radio on and off (for "airplane" mode)
     * If the radio is turned off/on the radio modem subsystem
     * is expected return to an initialized state. For instance,
     * any voice and data calls must be terminated and all associated
     * lists emptied.
     *
     * @param serial Serial number of request.
     * @param on To turn on radio -> on = true, to turn off radio -> on = false.
     *
     * Response function is IRadioResponse.setRadioPowerResponse()
     */
    Return<void> setRadioPower(int32_t serial, bool on) override;

    /**
     * Send a DTMF tone
     *
     * If the implementation is currently playing a tone requested via
     * startDtmf(), that tone must be cancelled and the new tone
     * must be played instead
     *
     * @param serial Serial number of request.
     * @param s string with single char having one of 12 values: 0-9, *, #
     *
     * Response function is IRadioResponse.sendDtmfResponse()
     */
    Return<void> sendDtmf(int32_t serial, const ::android::hardware::hidl_string& s) override;

    /**
     * Send an SMS message
     *
     * @param serial Serial number of request.
     * @param message GsmSmsMessage as defined in types.hal
     *
     * Response function is IRadioResponse.sendSmsResponse()
     *
     * Based on the return error, caller decides to resend if sending sms
     * fails. RadioError:SMS_SEND_FAIL_RETRY means retry (i.e. error cause is 332)
     * and RadioError:GENERIC_FAILURE means no retry (i.e. error cause is 500)
     */
    Return<void> sendSms(int32_t serial, const ::android::hardware::radio::V1_0::GsmSmsMessage& message) override;

    /**
     * Send an SMS message. Identical to sendSms,
     * except that more messages are expected to be sent soon. If possible,
     * keep SMS relay protocol link open (eg TS 27.005 AT+CMMS command)
     *
     * @param serial Serial number of request.
     * @param message GsmSmsMessage as defined in types.hal
     *
     * Response function is IRadioResponse.sendSMSExpectMoreResponse()
     *
     * Based on the return error, caller decides to resend if sending sms
     * fails. RadioError:SMS_SEND_FAIL_RETRY means retry (i.e. error cause is 332)
     * and RadioError:GENERIC_FAILURE means no retry (i.e. error cause is 500)
     */
    Return<void> sendSMSExpectMore(int32_t serial, const ::android::hardware::radio::V1_0::GsmSmsMessage& message) override;

    /**
     * Setup a packet data connection. If DataCallResponse.status
     * return DataCallFailCause:NONE it is added to the list of data calls and a
     * unsolDataCallListChanged() is sent. The call remains in the
     * list until deactivateDataCall() is issued or the
     * radio is powered off/on. This list is returned by getDataCallList()
     * and dataCallListChanged().
     *
     * The Radio is expected to:
     *  - Create one data call context.
     *  - Create and configure a dedicated interface for the context
     *  - The interface must be point to point.
     *  - The interface is configured with one or more addresses and
     *    is capable of sending and receiving packets. The prefix length
     *    of the addresses must be /32 for IPv4 and /128 for IPv6.
     *  - Must NOT change the linux routing table.
     *  - Support up to getDataRegistrationState response[5]
     *    number of simultaneous data call contexts.
     *
     * @param serial Serial number of request.
     * @param radioTechnology Radio technology to use.
     * @param dataProfileInfo data profile info.
     * @param modemCognitive Indicating this profile was sent to the modem through setDataProfile
     *                       earlier.
     * @param roamingAllowed Indicating data roaming is allowed or not by the user.
     * @param isRoaming Indicating the device is roaming or not. The 'protocol' parameter in the old
     *                  RIL API must be filled accordingly based on the roaming condition.
     *                  Note this is for backward compatibility with the old radio modem. The modem
     *                  must not use this param for any other reason.
     *
     * Response function is IRadioResponse.setupDataCallResponse()
     */
    Return<void> setupDataCall(int32_t serial, ::android::hardware::radio::V1_0::RadioTechnology radioTechnology, const ::android::hardware::radio::V1_0::DataProfileInfo& dataProfileInfo, bool modemCognitive, bool roamingAllowed, bool isRoaming) override;

    /**
     * Request ICC I/O operation.
     * This is similar to the TS 27.007 "restricted SIM" operation
     * where it assumes all of the EF selection must be done by the
     * callee
     *
     * Arguments and responses that are unused for certain
     * values of "command" must be ignored or set to empty string
     *
     * @param serial Serial number of request.
     * @param iccIo IccIo
     *
     * Please note that IccIo has a "PIN2" field which may be empty string,
     * or may specify a PIN2 for operations that require a PIN2 (eg
     * updating FDN records)
     *
     * Response function is IRadioResponse.iccIOForAppResponse()
     */
    Return<void> iccIOForApp(int32_t serial, const ::android::hardware::radio::V1_0::IccIo& iccIo) override;

    /**
     * Send a USSD message.
     *
     * If a USSD session already exists, the message must be sent in the
     * context of that session. Otherwise, a new session must be created.
     *
     * The network reply must be reported via unsolOnUssd
     *
     * Only one USSD session must exist at a time, and the session is assumed
     * to exist until:
     * a) The android system invokes cancelUssd()
     * b) The implementation sends a unsolOnUssd() with a type code
     * of "0" (USSD-Notify/no further action) or "2" (session terminated)
     *
     * @param serial Serial number of request.
     * @param ussd string containing the USSD request in UTF-8 format
     *
     * Response function is IRadioResponse.sendUssdResponse()
     *
     * See also requestCancelUssd, unsolOnUssd
     */
    Return<void> sendUssd(int32_t serial, const ::android::hardware::hidl_string& ussd) override;

    /**
     * Cancel the current USSD session if one exists.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.cancelPendingUssdResponse()
     */
    Return<void> cancelPendingUssd(int32_t serial) override;

    /**
     * Gets current CLIR status
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getClirResponse()
     */
    Return<void> getClir(int32_t serial) override;

    /**
     * Set current CLIR status
     *
     * @param serial Serial number of request.
     * @param status "n" parameter from TS 27.007 7.7
     *
     * Response function is IRadioResponse.setClirResponse()
     */
    Return<void> setClir(int32_t serial, int32_t status) override;

    /**
     * Request call forward status.
     *
     * @param serial Serial number of request.
     * @param callInfo CallForwardInfo
     *
     * Response function is IRadioResponse.getCallForwardStatusResponse()
     */
    Return<void> getCallForwardStatus(int32_t serial, const ::android::hardware::radio::V1_0::CallForwardInfo& callInfo) override;

    /**
     * Configure call forward rule
     *
     * @param serial Serial number of request.
     * @param callInfo CallForwardInfo
     *
     * Response function is IRadioResponse.setCallForwardResponse()
     */
    Return<void> setCallForward(int32_t serial, const ::android::hardware::radio::V1_0::CallForwardInfo& callInfo) override;

    /**
     * Query current call waiting state
     *
     * @param serial Serial number of request.
     * @param serviceClass Service class is the TS 27.007 service class to query
     *
     * Response function is IRadioResponse.getCallWaitingResponse()
     */
    Return<void> getCallWaiting(int32_t serial, int32_t serviceClass) override;

    /**
     * Configure current call waiting state
     *
     * @param serial Serial number of request.
     * @param enable is false for "disabled" and true for "enabled"
     * @param serviceClass is the TS 27.007 service class bit vector of services to modify
     *
     * Response function is IRadioResponse.setCallWaitingResponse()
     */
    Return<void> setCallWaiting(int32_t serial, bool enable, int32_t serviceClass) override;

    /**
     * Acknowledge successful or failed receipt of SMS previously indicated
     * via unsolResponseNewSms
     *
     * @param serial Serial number of request.
     * @param success is true on successful receipt
     *        (basically, AT+CNMA=1 from TS 27.005 is 0 on failed receipt
     *        (basically, AT+CNMA=2 from TS 27.005)
     * @param cause: if success is false, this contains the failure cause as defined
     *        in TS 23.040, 9.2.3.22.
     *
     * Response function is IRadioResponse.acknowledgeLastIncomingGsmSmsResponse()
     */
    Return<void> acknowledgeLastIncomingGsmSms(int32_t serial, bool success, ::android::hardware::radio::V1_0::SmsAcknowledgeFailCause cause) override;

    /**
     * Answer incoming call
     * Must not be called for WAITING calls.
     * switchWaitingOrHoldingAndActive() must be used in this case
     * instead
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.acceptCallResponse()
     */
    Return<void> acceptCall(int32_t serial) override;

    /**
     * Deactivate packet data connection and remove from the
     * data call list if RadioError:NONE is returned. Any other return
     * values must also try to remove the call from the list. An
     * unsolDataCallListChanged must be
     * issued because of an deactivateDataCall.
     *
     * @param serial Serial number of request.
     * @param cid Indicates CID
     * @param reasonRadioShutDown Indicates Disconnect Reason
     *        false => No specific reason specified
     *        true => Radio shutdown requested
     *
     * Response function is IRadioResponse.deactivateDataCallResponse()
     */
    Return<void> deactivateDataCall(int32_t serial, int32_t cid, bool reasonRadioShutDown) override;

    /**
     * Query the status of a facility lock state
     *
     * @param serial Serial number of request.
     * @param facility is the facility string code from TS 27.007 7.4
     *        (eg "AO" for BAOC, "SC" for SIM lock)
     * @param password is the password, or "" if not required
     * @param serviceClass is the TS 27.007 service class bit vector of services to query
     * @param appId is AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *        This is only applicable in the case of Fixed Dialing Numbers (FDN) requests.
     *
     * Response function is IRadioResponse.getFacilityLockForAppResponse()
     */
    Return<void> getFacilityLockForApp(int32_t serial, const ::android::hardware::hidl_string& facility, const ::android::hardware::hidl_string& password, int32_t serviceClass, const ::android::hardware::hidl_string& appId) override;

    /**
     * Enable/disable one facility lock
     *
     * @param serial Serial number of request.
     * @param facility is the facility string code from TS 27.007 7.4 (eg "AO" for BAOC)
     * @param lockState false for "unlock" and true for "lock"
     * @param password is the password
     * @param serviceClass is string representation of decimal TS 27.007
     *        service class bit vector. Eg, the string
     *        "1" means "set this facility for voice services"
     * @param appId is AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value.
     *        This is only applicable in the case of Fixed Dialing Numbers (FDN) requests.
     *
     * Response function is IRadioResponse.setFacilityLockForAppResponse()
     */
    Return<void> setFacilityLockForApp(int32_t serial, const ::android::hardware::hidl_string& facility, bool lockState, const ::android::hardware::hidl_string& password, int32_t serviceClass, const ::android::hardware::hidl_string& appId) override;

    /**
     * Change call barring facility password
     *
     * @param serial Serial number of request.
     * @param facility facility string code from TS 27.007 7.4 (eg "AO" for BAOC)
     * @param oldPassword old password
     * @param newPassword new password
     *
     * Response function is IRadioResponse.setBarringPasswordResponse()
     */
    Return<void> setBarringPassword(int32_t serial, const ::android::hardware::hidl_string& facility, const ::android::hardware::hidl_string& oldPassword, const ::android::hardware::hidl_string& newPassword) override;

    /**
     * Query current network selection mode
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getNetworkSelectionModeResponse()
     */
    Return<void> getNetworkSelectionMode(int32_t serial) override;

    /**
     * Specify that the network must be selected automatically.
     * This request must not respond until the new operator is selected and registered.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.setNetworkSelectionModeAutomaticResponse()
     */
    Return<void> setNetworkSelectionModeAutomatic(int32_t serial) override;

    /**
     * Manually select a specified network.
     * This request must not respond until the new operator is selected and registered.
     *
     * @param serial Serial number of request.
     * @param operatorNumeric string specifying MCCMNC of network to select (eg "310170")
     *
     * Response function is IRadioResponse.setNetworkSelectionModeManualResponse()
     */
    Return<void> setNetworkSelectionModeManual(int32_t serial, const ::android::hardware::hidl_string& operatorNumeric) override;

    /**
     * Scans for available networks
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getAvailableNetworksResponse()
     */
    Return<void> getAvailableNetworks(int32_t serial) override;

    /**
     * Start playing a DTMF tone. Continue playing DTMF tone until
     * stopDtmf is received.
     * If a startDtmf() is received while a tone is currently playing,
     * it must cancel the previous tone and play the new one.
     *
     * @param serial Serial number of request.
     * @param s string having a single character with one of 12 values: 0-9,*,#
     *
     * Response function is IRadioResponse.startDtmfResponse()
     */
    Return<void> startDtmf(int32_t serial, const ::android::hardware::hidl_string& s) override;

    /**
     * Stop playing a currently playing DTMF tone.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.stopDtmfResponse()
     */
    Return<void> stopDtmf(int32_t serial) override;

    /**
     * Return string value indicating baseband version, eg response from AT+CGMR
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getBasebandVersionResponse()
     */
    Return<void> getBasebandVersion(int32_t serial) override;

    /**
     * Separate a party from a multiparty call placing the multiparty call
     * (less the specified party) on hold and leaving the specified party
     * as the only other member of the current (active) call
     *
     * Like AT+CHLD=2x
     *
     * See TS 22.084 1.3.8.2 (iii)
     * TS 22.030 6.5.5 "Entering "2X followed by send"
     * TS 27.007 "AT+CHLD=2x"
     *
     * @param serial Serial number of request.
     * @param gsmIndex contains Connection index (value of 'x' in CHLD above)
     *
     * Response function is IRadioResponse.separateConnectionResponse()
     */
    Return<void> separateConnection(int32_t serial, int32_t gsmIndex) override;

    /**
     * Turn on or off uplink (microphone) mute.
     * Must only be sent while voice call is active.
     * Must always be reset to "disable mute" when a new voice call is initiated
     *
     * @param serial Serial number of request.
     * @param enable true for "enable mute" and false for "disable mute"
     *
     * Response function is IRadioResponse.setMuteResponse()
     */
    Return<void> setMute(int32_t serial, bool enable) override;

    /**
     * Queries the current state of the uplink mute setting
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getMuteResponse()
     */
    Return<void> getMute(int32_t serial) override;

    /**
     * Queries the status of the CLIP supplementary service
     * (for MMI code "*#30#")
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getClipResponse()
     */
    Return<void> getClip(int32_t serial) override;

    /**
     * Returns the data call list. An entry is added when a
     * setupDataCall() is issued and removed on a
     * deactivateDataCall(). The list is emptied when
     * setRadioPower() off/on is issued.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getDataCallListResponse()
     */
    Return<void> getDataCallList(int32_t serial) override;

    /**
     * Enables/disables supplementary service related notifications from the network.
     * Notifications are reported via unsolSuppSvcNotification().
     *
     * @param serial Serial number of request.
     * @param enable true = notifications enabled, false = notifications disabled.
     *
     * Response function is IRadioResponse.setSuppServiceNotificationsResponse()
     */
    Return<void> setSuppServiceNotifications(int32_t serial, bool enable) override;

    /**
     * Stores a SMS message to SIM memory.
     *
     * @param serial Serial number of request.
     * @param smsWriteArgs SmsWriteArgs defined in types.hal
     *
     * Response function is IRadioResponse.writeSmsToSimResponse()
     */
    Return<void> writeSmsToSim(int32_t serial, const ::android::hardware::radio::V1_0::SmsWriteArgs& smsWriteArgs) override;

    /**
     * Deletes a SMS message from SIM memory.
     *
     * @param serial Serial number of request.
     * @param index Record index of the message to delete.
     *
     * Response function is IRadioResponse.deleteSmsOnSimResponse()
     */
    Return<void> deleteSmsOnSim(int32_t serial, int32_t index) override;

    /**
     * Assign a specified band for RF configuration.
     *
     * @param serial Serial number of request.
     * @param mode RadioBandMode defined in types.hal
     *
     * Response function is IRadioResponse.setBandModeResponse()
     */
    Return<void> setBandMode(int32_t serial, ::android::hardware::radio::V1_0::RadioBandMode mode) override;

    /**
     * Get the list of band modes supported by RF.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getAvailableBandModesResponse()
     */
    Return<void> getAvailableBandModes(int32_t serial) override;

    /**
     * Requests to send a SAT/USAT envelope command to SIM.
     * The SAT/USAT envelope command refers to 3GPP TS 11.14 and 3GPP TS 31.111
     *
     * @param serial Serial number of request.
     * @param command SAT/USAT command in hexadecimal format string starting with command tag
     *
     * Response function is IRadioResponse.sendEnvelopeResponse()
     */
    Return<void> sendEnvelope(int32_t serial, const ::android::hardware::hidl_string& command) override;

    /**
     * Requests to send a terminal response to SIM for a received proactive command
     *
     * @param serial Serial number of request.
     * @param commandResponse SAT/USAT response in hexadecimal format string starting with
     *        first byte of response data
     *
     * Response function is IRadioResponse.sendTerminalResponseResponseToSim()
     */
    Return<void> sendTerminalResponseToSim(int32_t serial, const ::android::hardware::hidl_string& commandResponse) override;

    /**
     * When STK application gets stkCallSetup(), the call actually has
     * been initialized by mobile device already. (We could see the call has been in the 'call
     * list') So, STK application needs to accept/reject the call according to user
     * operations.
     *
     * @param serial Serial number of request.
     * @param accept true = accept the call setup, false = reject the call setup
     *
     * Response callback is IRadioResponse.handleStkCallSetupRequestFromSimResponse()
     */
    Return<void> handleStkCallSetupRequestFromSim(int32_t serial, bool accept) override;

    /**
     * Connects the two calls and disconnects the subscriber from both calls.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.explicitCallTransferResponse()
     */
    Return<void> explicitCallTransfer(int32_t serial) override;

    /**
     * Requests to set the preferred network type for searching and registering
     * (CS/PS domain, RAT, and operation mode)
     *
     * @param serial Serial number of request.
     * @param nwType PreferredNetworkType defined in types.hal
     *
     * Response callback is IRadioResponse.setPreferredNetworkTypeResponse()
     */
    Return<void> setPreferredNetworkType(int32_t serial, ::android::hardware::radio::V1_0::PreferredNetworkType nwType) override;

    /**
     * Query the preferred network type (CS/PS domain, RAT, and operation mode)
     * for searching and registering
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getPreferredNetworkTypeResponse()
     */
    Return<void> getPreferredNetworkType(int32_t serial) override;

    /**
     * Request neighboring cell id in GSM network
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getNeighboringCidsResponse()
     */
    Return<void> getNeighboringCids(int32_t serial) override;

    /**
     * Enables/disables network state change notifications due to changes in
     * LAC and/or CID (for GSM) or BID/SID/NID/latitude/longitude (for CDMA).
     * Basically +CREG=2 vs. +CREG=1 (TS 27.007).
     * Note:  The Radio implementation must default to "updates enabled"
     * when the screen is on and "updates disabled" when the screen is off.
     *
     * @param serial Serial number of request.
     * @param enable true = updates enabled (+CREG=2), false = updates disabled (+CREG=1)
     *
     * Response callback is IRadioResponse.setLocationUpdatesResponse()
     */
    Return<void> setLocationUpdates(int32_t serial, bool enable) override;

    /**
     * Request to set the location where the CDMA subscription shall
     * be retrieved
     *
     * @param serial Serial number of request.
     * @param cdmaSub CdmaSubscriptionSource
     *
     * Response callback is IRadioResponse.setCdmaSubscriptionSourceResponse()
     */
    Return<void> setCdmaSubscriptionSource(int32_t serial, ::android::hardware::radio::V1_0::CdmaSubscriptionSource cdmaSub) override;

    /**
     * Request to set the roaming preferences in CDMA
     *
     * @param serial Serial number of request.
     * @param type CdmaRoamingType defined in types.hal
     *
     * Response callback is IRadioResponse.setCdmaRoamingPreferenceResponse()
     */
    Return<void> setCdmaRoamingPreference(int32_t serial, ::android::hardware::radio::V1_0::CdmaRoamingType type) override;

    /**
     * Request the actual setting of the roaming preferences in CDMA in the modem
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getCdmaRoamingPreferenceResponse()
     */
    Return<void> getCdmaRoamingPreference(int32_t serial) override;

    /**
     * Request to set the TTY mode
     *
     * @param serial Serial number of request.
     * @param mode TtyMode
     *
     * Response callback is IRadioResponse.setTTYModeResponse()
     */
    Return<void> setTTYMode(int32_t serial, ::android::hardware::radio::V1_0::TtyMode mode) override;

    /**
     * Request the setting of TTY mode
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getTTYModeResponse()
     */
    Return<void> getTTYMode(int32_t serial) override;

    /**
     * Request to set the preferred voice privacy mode used in voice scrambling.
     *
     * @param serial Serial number of request.
     * @param enable false for Standard Privacy Mode (Public Long Code Mask)
     *        true for Enhanced Privacy Mode (Private Long Code Mask)
     *
     * Response callback is IRadioResponse.setPreferredVoicePrivacyResponse()
     */
    Return<void> setPreferredVoicePrivacy(int32_t serial, bool enable) override;

    /**
     * Request the setting of preferred voice privacy mode.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getPreferredVoicePrivacyResponse()
     */
    Return<void> getPreferredVoicePrivacy(int32_t serial) override;

    /**
     * Send FLASH command
     *
     * @param serial Serial number of request.
     * @param featureCode String associated with Flash command
     *
     * Response callback is IRadioResponse.sendCDMAFeatureCodeResponse()
     */
    Return<void> sendCDMAFeatureCode(int32_t serial, const ::android::hardware::hidl_string& featureCode) override;

    /**
     * Send DTMF string
     *
     * @param serial Serial number of request.
     * @param dtmf DTMF string
     * @param on DTMF ON length in milliseconds, or 0 to use default
     * @param off is the DTMF OFF length in milliseconds, or 0 to use default
     *
     * Response callback is IRadioResponse.sendBurstDtmfResponse()
     */
    Return<void> sendBurstDtmf(int32_t serial, const ::android::hardware::hidl_string& dtmf, int32_t on, int32_t off) override;

    /**
     * Send a CDMA SMS message
     *
     * @param serial Serial number of request.
     * @param sms Cdma Sms to be sent described by CdmaSmsMessage in types.hal
     *
     * Response callback is IRadioResponse.sendCdmaSmsResponse()
     */
    Return<void> sendCdmaSms(int32_t serial, const ::android::hardware::radio::V1_0::CdmaSmsMessage& sms) override;

    /**
     * Acknowledge the success or failure in the receipt of SMS
     * previously indicated via responseCdmaNewSms()
     *
     * @param serial Serial number of request.
     * @param smsAck Cdma Sms ack to be sent described by CdmaSmsAck in types.hal
     *
     * Response callback is IRadioResponse.acknowledgeLastIncomingCdmaSmsResponse()
     */
    Return<void> acknowledgeLastIncomingCdmaSms(int32_t serial, const ::android::hardware::radio::V1_0::CdmaSmsAck& smsAck) override;

    /**
     * Request the setting of GSM/WCDMA Cell Broadcast SMS config.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getGsmBroadcastConfigResponse()
     */
    Return<void> getGsmBroadcastConfig(int32_t serial) override;

    /**
     * Set GSM/WCDMA Cell Broadcast SMS config
     *
     * @param serial Serial number of request.
     * @param configInfo Setting of GSM/WCDMA Cell broadcast config
     *
     * Response callback is IRadioResponse.setGsmBroadcastConfigResponse()
     */
    Return<void> setGsmBroadcastConfig(int32_t serial, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_0::GsmBroadcastSmsConfigInfo>& configInfo) override;

    /**
     * Enable or disable the reception of GSM/WCDMA Cell Broadcast SMS
     *
     * @param serial Serial number of request.
     * @param activate indicates to activate or turn off the reception of GSM/WCDMA
     *        Cell Broadcast SMS. true = activate, false = turn off
     *
     * Response callback is IRadioResponse.setGsmBroadcastActivationResponse()
     */
    Return<void> setGsmBroadcastActivation(int32_t serial, bool activate) override;

    /**
     * Request the setting of CDMA Broadcast SMS config
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getCdmaBroadcastConfigResponse()
     */
    Return<void> getCdmaBroadcastConfig(int32_t serial) override;

    /**
     * Set CDMA Broadcast SMS config
     *
     * @param serial Serial number of request.
     * @param configInfo CDMA Broadcast SMS config to be set.
     *
     * Response callback is IRadioResponse.setCdmaBroadcastConfigResponse()
     */
    Return<void> setCdmaBroadcastConfig(int32_t serial, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_0::CdmaBroadcastSmsConfigInfo>& configInfo) override;

    /**
     * Enable or disable the reception of CDMA Cell Broadcast SMS
     *
     * @param serial Serial number of request.
     * @param activate indicates to activate or turn off the reception of CDMA
     *        Cell Broadcast SMS. true = activate, false = turn off
     *
     * Response callback is IRadioResponse.setCdmaBroadcastActivationResponse()
     */
    Return<void> setCdmaBroadcastActivation(int32_t serial, bool activate) override;

    /**
     * Request the device MDN / H_SID / H_NID.
     * The request is only allowed when CDMA subscription is available. When CDMA
     * subscription is changed, application layer must re-issue the request to
     * update the subscription information.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getCDMASubscriptionResponse()
     */
    Return<void> getCDMASubscription(int32_t serial) override;

    /**
     * Stores a CDMA SMS message to RUIM memory.
     *
     * @param serial Serial number of request.
     * @param cdmaSms CDMA message as defined by CdmaSmsWriteArgs in types.hal
     *
     * Response callback is IRadioResponse.writeSmsToRuimResponse()
     */
    Return<void> writeSmsToRuim(int32_t serial, const ::android::hardware::radio::V1_0::CdmaSmsWriteArgs& cdmaSms) override;

    /**
     * Deletes a CDMA SMS message from RUIM memory.
     *
     * @param serial Serial number of request.
     * @param index record index of the message to delete
     *
     * Response callback is IRadioResponse.deleteSmsOnRuimResponse()
     */
    Return<void> deleteSmsOnRuim(int32_t serial, int32_t index) override;

    /**
     * Request the device ESN / MEID / IMEI / IMEISV.
     * The request is always allowed and contains GSM and CDMA device identity.
     * When CDMA subscription is changed the ESN/MEID changes. The application
     * layer must re-issue the request to update the device identity in this case.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getDeviceIdentityResponse()
     */
    Return<void> getDeviceIdentity(int32_t serial) override;

    /**
     * Request the radio's system selection module to exit emergency
     * callback mode. Radio must not respond with SUCCESS until the modem has
     * completely exited from Emergency Callback Mode.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.exitEmergencyCallbackModeResponse()
     */
    Return<void> exitEmergencyCallbackMode(int32_t serial) override;

    /**
     * Get the default Short Message Service Center address on the device.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getSmscAddressResponse()
     */
    Return<void> getSmscAddress(int32_t serial) override;

    /**
     * Set the default Short Message Service Center address on the device.
     *
     * @param serial Serial number of request.
     * @param smsc Short Message Service Center address to set
     *
     * Response callback is IRadioResponse.setSmscAddressResponse()
     */
    Return<void> setSmscAddress(int32_t serial, const ::android::hardware::hidl_string& smsc) override;

    /**
     * Indicates whether there is storage available for new SMS messages.
     *
     * @param serial Serial number of request.
     * @param available true if memory is available for storing new messages,
     *        false if memory capacity is exceeded
     *
     * Response callback is IRadioResponse.reportSmsMemoryStatusResponse()
     */
    Return<void> reportSmsMemoryStatus(int32_t serial, bool available) override;

    /**
     * Indicates that the StkService is running and is
     * ready to receive unsolicited stkXXXXX commands.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.reportStkServiceIsRunningResponse()
     */
    Return<void> reportStkServiceIsRunning(int32_t serial) override;

    /**
     * Request to query the location where the CDMA subscription shall be retrieved.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getCdmaSubscriptionSourceResponse()
     */
    Return<void> getCdmaSubscriptionSource(int32_t serial) override;

    /**
     * Request the ISIM application on the UICC to perform AKA
     * challenge/response algorithm for IMS authentication
     *
     * @param serial Serial number of request.
     * @param challenge challenge string in Base64 format
     *
     * Response callback is IRadioResponse.requestIsimAuthenticationResponse()
     */
    Return<void> requestIsimAuthentication(int32_t serial, const ::android::hardware::hidl_string& challenge) override;

    /**
     * Acknowledge successful or failed receipt of SMS previously indicated
     * via unsol responseNewSms(), including acknowledgement TPDU to send
     * as the RP-User-Data element of the RP-ACK or RP-ERROR PDU.
     *
     * @param serial Serial number of request.
     * @param success true on successful receipt (send RP-ACK)
     *        false on failed receipt (send RP-ERROR)
     * @param ackPdu acknowledgement TPDU in hexadecimal format
     *
     * Response callback is IRadioResponse.acknowledgeIncomingGsmSmsWithPduResponse()
     */
    Return<void> acknowledgeIncomingGsmSmsWithPdu(int32_t serial, bool success, const ::android::hardware::hidl_string& ackPdu) override;

    /**
     * Requests to send a SAT/USAT envelope command to SIM.
     * The SAT/USAT envelope command refers to 3GPP TS 11.14 and 3GPP TS 31.111.
     *
     * This request has one difference from sendEnvelope():
     * the SW1 and SW2 status bytes from the UICC response are returned along with
     * the response data, using the same structure as iccIOForApp().
     *
     * The implementation must perform normal processing of a '91XX'
     * response in SW1/SW2 to retrieve the pending proactive command and send it
     * as an unsolicited response, as sendEnvelope() does.
     *
     * @param serial Serial number of request.
     * @param contents SAT/USAT command in hexadecimal format starting with command tag
     *
     * Response callback is IRadioResponse.sendEnvelopeWithStatusResponse()
     */
    Return<void> sendEnvelopeWithStatus(int32_t serial, const ::android::hardware::hidl_string& contents) override;

    /**
     * Query the radio technology type (3GPP/3GPP2) used for voice. Query is valid only
     * when radio state is not RADIO_STATE_UNAVAILABLE
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getVoiceRadioTechnologyResponse()
     */
    Return<void> getVoiceRadioTechnology(int32_t serial) override;

    /**
     * Request all of the current cell information known to the radio. The radio
     * must return list of all current cells, including the neighboring cells. If for a particular
     * cell information isn't known then the appropriate unknown value will be returned.
     * This does not cause or change the rate of unsolicited cellInfoList().
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getCellInfoListResponse()
     */
    Return<void> getCellInfoList(int32_t serial) override;

    /**
     * Sets the minimum time between when unsolicited cellInfoList() must be invoked.
     * A value of 0, means invoke cellInfoList() when any of the reported
     * information changes. Setting the value to INT_MAX(0x7fffffff) means never issue
     * a unsolicited cellInfoList().
     *
     * @param serial Serial number of request.
     * @param rate minimum time in milliseconds to indicate time between unsolicited cellInfoList()
     *
     * Response callback is IRadioResponse.setCellInfoListRateResponse()
     */
    Return<void> setCellInfoListRate(int32_t serial, int32_t rate) override;

    /**
     * Set an apn to initial attach network
     *
     * @param serial Serial number of request.
     * @param dataProfileInfo data profile containing APN settings
     * @param modemCognitive indicating the data profile was sent to the modem through
     *                       setDataProfile earlier.
     * @param isRoaming Indicating the device is roaming or not. The 'protocol' parameter in the old
     *                  RIL_InitialAttachApn must be filled accordingly based on the roaming
     *                  condition. Note this is for backward compatibility with the old radio modem.
     *                  The modem must not use this param for any other reason.
     *
     * Response callback is IRadioResponse.setInitialAttachApnResponse()
     */
    Return<void> setInitialAttachApn(int32_t serial, const ::android::hardware::radio::V1_0::DataProfileInfo& dataProfileInfo, bool modemCognitive, bool isRoaming) override;

    /**
     * Request current IMS registration state
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getImsRegistrationStateResponse()
     */
    Return<void> getImsRegistrationState(int32_t serial) override;

    /**
     * Send a SMS message over IMS.
     * Based on the return error, caller decides to resend if sending sms
     * fails. SMS_SEND_FAIL_RETRY means retry, and other errors means no retry.
     * In case of retry, data is encoded based on Voice Technology available.
     *
     * @param serial Serial number of request.
     * @param message ImsSmsMessage as defined in types.hal to be sent
     *
     * Response callback is IRadioResponse.sendImsSmsResponse()
     */
    Return<void> sendImsSms(int32_t serial, const ::android::hardware::radio::V1_0::ImsSmsMessage& message) override;

    /**
     * Request APDU exchange on the basic channel. This command reflects TS 27.007
     * "generic SIM access" operation (+CSIM). The modem must ensure proper function
     * of GSM/CDMA, and filter commands appropriately. It must filter
     * channel management and SELECT by DF name commands.
     * "sessionid" field must be ignored.
     *
     * @param serial Serial number of request.
     * @param message SimApdu as defined in types.hal to be sent
     *
     * Response callback is IRadioResponse.iccTransmitApduBasicChannelResponse()
     */
    Return<void> iccTransmitApduBasicChannel(int32_t serial, const ::android::hardware::radio::V1_0::SimApdu& message) override;

    /**
     * Open a new logical channel and select the given application. This command
     * reflects TS 27.007 "open logical channel" operation (+CCHO).
     *
     * @param serial Serial number of request.
     * @param aid AID value, See ETSI 102.221 and 101.220.
     * @param p2 P2 value, described in ISO 7816-4. Ignore if equal to P2Constant:NO_P2
     *
     * Response callback is IRadioResponse.iccOpenLogicalChannelResponse()
     */
    Return<void> iccOpenLogicalChannel(int32_t serial, const ::android::hardware::hidl_string& aid, int32_t p2) override;

    /**
     * Close a previously opened logical channel. This command reflects TS 27.007
     * "close logical channel" operation (+CCHC).
     *
     * @param serial Serial number of request.
     * @param channelId session id of the logical channel (+CCHC).
     *
     * Response callback is IRadioResponse.iccCloseLogicalChannelResponse()
     */
    Return<void> iccCloseLogicalChannel(int32_t serial, int32_t channelId) override;

    /**
     * Exchange APDUs with a UICC over a previously opened logical channel. This
     * command reflects TS 27.007 "generic logical channel access" operation
     * (+CGLA). The modem must filter channel management and SELECT by DF name
     * commands.
     *
     * @param serial Serial number of request.
     * @param message SimApdu as defined in types.hal to be sent
     *
     * Response callback is IRadioResponse.iccTransmitApduLogicalChannelResponse()
     */
    Return<void> iccTransmitApduLogicalChannel(int32_t serial, const ::android::hardware::radio::V1_0::SimApdu& message) override;

    /**
     * Read one of the radio NV items.
     * This is used for device configuration by some CDMA operators.
     *
     * @param serial Serial number of request.
     * @param itemId NvItem is radio NV item as defined in types.hal
     *
     * Response callback is IRadioResponse.nvReadItemResponse()
     */
    Return<void> nvReadItem(int32_t serial, ::android::hardware::radio::V1_0::NvItem itemId) override;

    /**
     * Write one of the radio NV items.
     * This is used for device configuration by some CDMA operators.
     *
     * @param serial Serial number of request.
     * @param item NvWriteItem as defined in types.hal
     *
     * Response callback is IRadioResponse.nvWriteItemResponse()
     */
    Return<void> nvWriteItem(int32_t serial, const ::android::hardware::radio::V1_0::NvWriteItem& item) override;

    /**
     * Update the CDMA Preferred Roaming List (PRL) in the radio NV storage.
     * This is used for device configuration by some CDMA operators.
     *
     * @param serial Serial number of request.
     * @param prl PRL as a byte array
     *
     * Response callback is IRadioResponse.nvWriteCdmaPrlResponse()
     */
    Return<void> nvWriteCdmaPrl(int32_t serial, const ::android::hardware::hidl_vec<uint8_t>& prl) override;

    /**
     * Reset the radio NV configuration to the factory state.
     * This is used for device configuration by some CDMA operators.
     *
     * @param serial Serial number of request.
     * @param resetType ResetNvType as defined in types.hal
     *
     * Response callback is IRadioResponse.nvResetConfigResponse()
     */
    Return<void> nvResetConfig(int32_t serial, ::android::hardware::radio::V1_0::ResetNvType resetType) override;

    /**
     * Selection/de-selection of a subscription from a SIM card
     *
     * @param serial Serial number of request.
     * @param uiccSub SelectUiccSub as defined in types.hal
     *
     * Response callback is IRadioResponse.setUiccSubscriptionResponse()
     */
    Return<void> setUiccSubscription(int32_t serial, const ::android::hardware::radio::V1_0::SelectUiccSub& uiccSub) override;

    /**
     * Tells the modem whether data calls are allowed or not
     *
     * @param serial Serial number of request.
     * @param allow true to allow data calls, false to disallow data calls
     *
     * Response callback is IRadioResponse.setDataAllowedResponse()
     */
    Return<void> setDataAllowed(int32_t serial, bool allow) override;

    /**
     * Request all of the current hardware (modem and sim) associated with Radio.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getHardwareConfigResponse()
     */
    Return<void> getHardwareConfig(int32_t serial) override;

    /**
     * Returns the response of SIM Authentication through Radio challenge request.
     *
     * @param serial Serial number of request.
     * @param authContext P2 value of authentication command, see P2 parameter in
     *        3GPP TS 31.102 7.1.2
     * @param authData the challenge string in Base64 format, see 3GPP TS 31.102 7.1.2
     * @param aid AID value, See ETSI 102.221 8.1 and 101.220 4, empty string if no value
     *
     * Response callback is IRadioResponse.requestIccSimAuthenticationResponse()
     */
    Return<void> requestIccSimAuthentication(int32_t serial, int32_t authContext, const ::android::hardware::hidl_string& authData, const ::android::hardware::hidl_string& aid) override;

    /**
     * Set data profile in modem.
     * Modem must erase existed profiles from framework, and apply new profiles
     *
     * @param serial Serial number of request.
     * @param profiles Array of DataProfiles to set.
     * @param isRoaming Indicating the device is roaming or not. The 'protocol' parameter in the old
     *                  RIL API RIL_DataProfileInfo must be filled accordingly based on the
     *                  roaming condition. Note this is for backward compatibility with the old
     *                  radio modem. The modem must not use this param for any other reason.
     *
     * Response callback is IRadioResponse.setDataProfileResponse()
     */
    Return<void> setDataProfile(int32_t serial, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_0::DataProfileInfo>& profiles, bool isRoaming) override;

    /**
     * Device is shutting down. All further commands are ignored
     * and RADIO_NOT_AVAILABLE must be returned.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.requestShutdownResponse()
     */
    Return<void> requestShutdown(int32_t serial) override;

    /**
     * Used to get phone radio capability.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getRadioCapabilityResponse()
     */
    Return<void> getRadioCapability(int32_t serial) override;

    /**
     * Used to set the phones radio capability. Be VERY careful
     * using this request as it may cause some vendor modems to reset. Because
     * of the possible modem reset any radio commands after this one may not be
     * processed.
     *
     * @param serial Serial number of request.
     * @param rc RadioCapability structure to be set
     *
     * Response callback is IRadioResponse.setRadioCapabilityResponse()
     */
    Return<void> setRadioCapability(int32_t serial, const ::android::hardware::radio::V1_0::RadioCapability& rc) override;

    /**
     * Start Link Capacity Estimate (LCE) service if supported by the radio.
     *
     * @param serial Serial number of request.
     * @param reportInterval desired reporting interval (ms).
     * @param pullMode LCE service mode. true: PULL; false: PUSH.
     *
     * Response callback is IRadioResponse.startLceServiceResponse()
     */
    Return<void> startLceService(int32_t serial, int32_t reportInterval, bool pullMode) override;

    /**
     * Stop Link Capacity Estimate (LCE) service, the STOP operation must be
     * idempotent for the radio modem.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.stopLceServiceResponse()
     */
    Return<void> stopLceService(int32_t serial) override;

    /**
     * Pull LCE service for capacity information.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.pullLceDataResponse()
     */
    Return<void> pullLceData(int32_t serial) override;

    /**
     * Get modem activity information for power consumption estimation.
     * Request clear-on-read statistics information that is used for
     * estimating the per-millisecond power consumption of the cellular
     * modem.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getModemActivityInfoResponse()
     */
    Return<void> getModemActivityInfo(int32_t serial) override;

    /**
     * Set carrier restrictions. Expected modem behavior:
     *  If never receives this command
     *  - Must allow all carriers
     *  Receives this command with allAllowed true
     *  - Must allow all carriers. If a previously allowed SIM is present, modem must not reload
     *    the SIM. If a previously disallowed SIM is present, reload the SIM and notify Android.
     *  Receives this command with a list of carriers & allAllowed = false
     *  - Only allow specified carriers, persist across power cycles and FDR. If a present SIM
     *    is in the allowed list, modem must not reload the SIM. If a present SIM is *not* in
     *    the allowed list, modem must detach from the registered network and only keep emergency
     *    service, and notify Android SIM refresh reset with new SIM state being
     *    CardState:RESTRICTED. Emergency service must be enabled.
     *
     * @param serial Serial number of request.
     * @param allAllowed true only when all carriers are allowed. Ignore "carriers" struct.
     *        If false, consider "carriers" struct
     * @param carriers CarrierRestrictions consisting allowed and excluded carriers as defined
     *        in types.hal
     *
     * Response callback is IRadioResponse.setAllowedCarriersResponse()
     */
    Return<void> setAllowedCarriers(int32_t serial, bool allAllowed, const ::android::hardware::radio::V1_0::CarrierRestrictions& carriers) override;

    /**
     * Get carrier restrictions.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getAllowedCarriersResponse()
     */
    Return<void> getAllowedCarriers(int32_t serial) override;

    /**
     * Send the updated device state.
     * This is providing the device state information for the modem to perform power saving
     * strategies.
     *
     * @param serial Serial number of request.
     * @param deviceStateType The updated device state type.
     * @param state The updated state. See the definition of state at DeviceStateType.
     *
     * Response callback is IRadioResponse.sendDeviceStateResponse()
     */
    Return<void> sendDeviceState(int32_t serial, ::android::hardware::radio::V1_0::DeviceStateType deviceStateType, bool state) override;

    /**
     * Set the indication filter.
     * This is used to prevent unnecessary application processor wake up for power saving purposes
     * by suppressing the indications in certain scenarios.
     *
     * @param serial Serial number of request.
     * @param indicationFilter 32-bit bitmap of IndicationFilter. Bits set to 1 indicate the
     *        indications are enabled. See IndicationFilter for the definition of each bit.
     *
     * Response callback is IRadioResponse.setIndicationFilterResponse()
     */
    Return<void> setIndicationFilter(int32_t serial, ::android::hardware::hidl_bitfield<::android::hardware::radio::V1_0::IndicationFilter> indicationFilter) override;

    /**
     * Set SIM card power state.
     * Request is equivalent to inserting or removing the card.
     *
     * The radio modem must generate IRadioIndication.simStatusChanged() as if the SIM had been
     * inserted or removed.
     *
     * @param serial Serial number of request
     * @param powerUp True if powering up the sim card
     *
     * Response callback is IRadioResponse.setSimCardPowerResponse()
     */
    Return<void> setSimCardPower(int32_t serial, bool powerUp) override;

    /**
     * When response type received from a radio indication or radio response is
     * RadioIndicationType:UNSOLICITED_ACK_EXP or RadioResponseType:SOLICITED_ACK_EXP respectively,
     * acknowledge the receipt of those messages by sending responseAcknowledgement().
     *
     */
    Return<void> responseAcknowledgement() override;

    /**
     * Provide Carrier specific information to the modem that must be used to
     * encrypt the IMSI and IMPI. Sent by the framework during boot, carrier
     * switch and everytime the framework receives a new certificate.
     *
     * @param serial Serial number of request.
     * @param message ImsiEncryptionInfo as defined in types.hal.
     *
     *
     * Response callback is
     * IRadioResponse.setCarrierInfoForImsiEncryptionResponse()
     */
    Return<void> setCarrierInfoForImsiEncryption(int32_t serial, const ::android::hardware::radio::V1_1::ImsiEncryptionInfo& imsiEncryptionInfo) override;

    /**
     * Set SIM card power state.
     * Request is equivalent to inserting or removing the card.
     *
     * The radio modem must generate IRadioIndication.simStatusChanged() as if the SIM had been
     * inserted or removed.
     *
     * @param serial Serial number of request
     * @param powerUp POWER_DOWN if powering down the SIM card,
     *                POWER_UP if powering up the SIM card,
     *                POWER_UP_PASS_THROUGH if powering up the SIM card in pass through mode.
     * When SIM card is in POWER_UP_PASS_THROUGH, the modem does not send any command to it
     * (for example SELECT of MF, or TERMINAL CAPABILITY), and the SIM card is controlled
     * completely by Telephony sending APDUs directly. The SIM card state must be
     * RIL_CARDSTATE_PRESENT and the number of card apps will be 0.
     * No new error code is generated. Emergency calls are supported in the same way as if the
     * SIM card is absent.
     * POWER_UP_PASS_THROUGH mode is valid only for the specific card session where it is activated,
     * and normal behavior occurs at the next SIM initialization, unless POWER_UP_PASS_THROUGH mode
     * is requested again.
     * The device is required to power down the SIM card before it can switch the mode between
     * POWER_UP and POWER_UP_PASS_THROUGH.
     * At device power up, the SIM interface is powered up automatically. Each subsequent request
     * to this method is processed only after the completion of the previous one.
     *
     * Response callback is IRadioResponse.setSimCardPowerResponse_1_1()
     */
    Return<void> setSimCardPower_1_1(int32_t serial, ::android::hardware::radio::V1_1::CardPowerState powerUp) override;

    /**
     * Starts a network scan
     *
     * @param serial Serial number of request.
     * @param request Defines the radio networks/bands/channels which need to be scanned.
     *
     * Response function is IRadioResponse.startNetworkScanResponse()
     */
    Return<void> startNetworkScan(int32_t serial, const ::android::hardware::radio::V1_1::NetworkScanRequest& request) override;

    /**
     * Stops ongoing network scan
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.stopNetworkScanResponse()
     */
    Return<void> stopNetworkScan(int32_t serial) override;

    /**
     * Start a Keepalive session (for IPsec)
     *
     * @param serial Serial number of request.
     * @param keepalive A request structure containing all necessary info to describe a keepalive
     *
     * Response function is IRadioResponse.startKeepaliveResponse()
     */
    Return<void> startKeepalive(int32_t serial, const ::android::hardware::radio::V1_1::KeepaliveRequest& keepalive) override;

    /**
     * Stop an ongoing Keepalive session (for IPsec)
     *
     * @param serial Serial number of request.
     * @param sessionHandle The handle that was provided by IRadioResponse.startKeepaliveResponse
     *
     * Response function is IRadioResponse.stopKeepaliveResponse()
     */
    Return<void> stopKeepalive(int32_t serial, int32_t sessionHandle) override;

    /**
     * Starts a network scan
     *
     * @param serial Serial number of request.
     * @param request Defines the radio networks/bands/channels which need to be scanned.
     *
     * Response function is IRadioResponse.startNetworkScanResponse()
     */
    Return<void> startNetworkScan_1_2(int32_t serial, const ::android::hardware::radio::V1_2::NetworkScanRequest& request) override;

    /**
     * Sets the indication filter.
     *
     * Prevents the reporting of specified unsolicited indications from the radio. This is used
     * for power saving in instances when those indications are not needed. If unset, defaults to
     * @1.2::IndicationFilter:ALL.
     *
     * @param serial Serial number of request.
     * @param indicationFilter 32-bit bitmap of IndicationFilter. Bits set to 1 indicate the
     *     indications are enabled. See @1.2::IndicationFilter for the definition of each bit.
     *
     * Response callback is IRadioResponse.setIndicationFilterResponse()
     */
    Return<void> setIndicationFilter_1_2(int32_t serial, ::android::hardware::hidl_bitfield<::android::hardware::radio::V1_2::IndicationFilter> indicationFilter) override;

    /**
     * Sets the signal strength reporting criteria.
     *
     * The resulting reporting rules are the AND of all the supplied criteria. For each RAN
     * The thresholdsDbm and hysteresisDb apply to only the following measured quantities:
     * -GERAN    - RSSI
     * -CDMA2000 - RSSI
     * -UTRAN    - RSCP
     * -EUTRAN   - RSRP
     *
     * Note: Reporting criteria must be individually set for each RAN. For any unset reporting
     * criteria, the value is implementation-defined.
     *
     * Note: As this mechanism generally only constrains reports based on one measured quantity per
     * RAN, if multiple measured quantities must be used to trigger a report for a given RAN, the
     * only valid field may be hysteresisMs: hysteresisDb and thresholdsDbm must be set to zero and
     * length zero respectively. If either hysteresisDb or thresholdsDbm is set, then reports shall
     * only be triggered by the respective measured quantity, subject to the applied constraints.
     *
     * Response callback is IRadioResponse.setSignalStrengthReportingCriteriaResponse()
     *
     * @param serial Serial number of request.
     * @param hysteresisMs A hysteresis time in milliseconds to prevent flapping. A value of 0
     *     disables hysteresis.
     * @param hysteresisDb An interval in dB defining the required magnitude change between reports.
     *     hysteresisDb must be smaller than the smallest threshold delta. An interval value of 0
     *     disables hysteresis.
     * @param thresholdsDbm A vector of trigger thresholds in dBm. A vector size of 0 disables the
     *     use of thresholds for reporting.
     * @param accessNetwork The type of network for which to apply these thresholds.
     */
    Return<void> setSignalStrengthReportingCriteria(int32_t serial, int32_t hysteresisMs, int32_t hysteresisDb, const ::android::hardware::hidl_vec<int32_t>& thresholdsDbm, ::android::hardware::radio::V1_2::AccessNetwork accessNetwork) override;

    /**
     * Sets the link capacity reporting criteria.
     *
     * The resulting reporting criteria are the AND of all the supplied criteria.
     *
     * Note: Reporting criteria must be individually set for each RAN. If unset, reporting criteria
     * for that RAN are implementation-defined.
     *
     * Response callback is IRadioResponse.setLinkCapacityReportingCriteriaResponse().
     *
     * @param serial Serial number of request.
     * @param hysteresisMs A hysteresis time in milliseconds to prevent flapping. A value of 0
     *     disables hysteresis.
     * @param hysteresisDlKbps An interval in kbps defining the required magnitude change between DL
     *     reports. hysteresisDlKbps must be smaller than the smallest threshold delta. A value of 0
     *     disables hysteresis.
     * @param hysteresisUlKbps An interval in kbps defining the required magnitude change between UL
     *     reports. hysteresisUlKbps must be smaller than the smallest threshold delta. A value of 0
     *     disables hysteresis.
     * @param thresholdsDownlinkKbps A vector of trigger thresholds in kbps for downlink reports. A
     *     vector size of 0 disables the use of DL thresholds for reporting.
     * @param thresholdsUplinkKbps A vector of trigger thresholds in kbps for uplink reports. A
     *     vector size of 0 disables the use of UL thresholds for reporting.
     * @param accessNetwork The type of network for which to apply these thresholds.
     */
    Return<void> setLinkCapacityReportingCriteria(int32_t serial, int32_t hysteresisMs, int32_t hysteresisDlKbps, int32_t hysteresisUlKbps, const ::android::hardware::hidl_vec<int32_t>& thresholdsDownlinkKbps, const ::android::hardware::hidl_vec<int32_t>& thresholdsUplinkKbps, ::android::hardware::radio::V1_2::AccessNetwork accessNetwork) override;

    /**
     * Setup a packet data connection. If DataCallResponse.status returns DataCallFailCause:NONE,
     * the data connection must be added to data calls and a unsolDataCallListChanged() must be
     * sent. The call remains until removed by subsequent unsolDataCallIstChanged(). It may be
     * lost due to many factors, including deactivateDataCall() being issued, the radio powered
     * off, reception lost or even transient factors like congestion. This data call list is
     * returned by getDataCallList() and dataCallListChanged().
     *
     * The Radio is expected to:
     *   - Create one data call context.
     *   - Create and configure a dedicated interface for the context.
     *   - The interface must be point to point.
     *   - The interface is configured with one or more addresses and is capable of sending and
     *     receiving packets. The prefix length of the addresses must be /32 for IPv4 and /128
     *     for IPv6.
     *   - Must not modify routing configuration related to this interface; routing management is
     *     exclusively within the purview of the Android OS.
     *   - Support simultaneous data call contexts up to DataRegStateResult.maxDataCalls specified
     *     in the response of getDataRegistrationState.
     *
     * @param serial Serial number of request.
     * @param accessNetwork The access network to setup the data call. If the data connection cannot
     *     be established on the specified access network, the setup request must be failed.
     * @param dataProfileInfo Data profile info.
     * @param modemCognitive Indicates that the requested profile has previously been provided via
     *     setDataProfile().
     * @param roamingAllowed Indicates whether or not data roaming is allowed by the user.
     * @param isRoaming Indicates whether or not the framework has requested this setupDataCall for
     *     a roaming network. The 'protocol' parameter in the old RIL API must be filled
     *     accordingly based on the roaming condition. Note this is for backward compatibility with
     *     the old radio modem. The modem must not use this param for any other reason.
     * @param reason The request reason. Must be DataRequestReason.NORMAL or
     *     DataRequestReason.HANDOVER.
     * @param addresses If the reason is DataRequestReason.HANDOVER, this indicates the list of link
     *     addresses of the existing data connection. The format is IP address with optional "/"
     *     prefix length (The format is defined in RFC-4291 section 2.3). For example, "192.0.1.3",
     *     "192.0.1.11/16", or "2001:db8::1/64". Typically one IPv4 or one IPv6 or one of each. If
     *     the prefix length is absent, then the addresses are assumed to be point to point with
     *     IPv4 with prefix length 32 or IPv6 with prefix length 128. This parameter must be ignored
     *     unless reason is DataRequestReason.HANDOVER.
     * @param dnses If the reason is DataRequestReason.HANDOVER, this indicates the list of DNS
     *     addresses of the existing data connection. The format is defined in RFC-4291 section
     *     2.2. For example, "192.0.1.3" or "2001:db8::1". This parameter must be ignored unless
     *     reason is DataRequestReason.HANDOVER.
     *
     * Response function is IRadioResponse.setupDataCallResponse()
     */
    Return<void> setupDataCall_1_2(int32_t serial, ::android::hardware::radio::V1_2::AccessNetwork accessNetwork, const ::android::hardware::radio::V1_0::DataProfileInfo& dataProfileInfo, bool modemCognitive, bool roamingAllowed, bool isRoaming, ::android::hardware::radio::V1_2::DataRequestReason reason, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& addresses, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& dnses) override;

    /**
     * Deactivate packet data connection and remove from the data call list. An
     * unsolDataCallListChanged() must be sent when data connection is deactivated.
     *
     * @param serial Serial number of request.
     * @param cid Data call id.
     * @param reason The request reason. Must be normal, handover, or shutdown.
     *
     * Response function is IRadioResponse.deactivateDataCallResponse()
     */
    Return<void> deactivateDataCall_1_2(int32_t serial, int32_t cid, ::android::hardware::radio::V1_2::DataRequestReason reason) override;

    /**
     * Specify which bands modem's background scan must act on.
     * If specifyChannels is true, it only scans bands specified in specifiers.
     * If specifyChannels is false, it scans all bands.
     *
     * For example, CBRS is only on LTE band 48. By specifying this band,
     * modem saves more power.
     *
     * @param serial Serial number of request.
     * @param specifyChannels whether to scan bands defined in specifiers.
     * @param specifiers which bands to scan. Only used if specifyChannels is true.
     *
     * Response callback is IRadioResponse.setSystemSelectionChannelsResponse()
     */
    Return<void> setSystemSelectionChannels(int32_t serial, bool specifyChannels, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_1::RadioAccessSpecifier>& specifiers) override;

    /**
     * Toggle logical modem on/off. This is similar to @1.0::IRadio.setRadioPower(), however that
     * does not enforce that radio power is toggled only for the corresponding radio and certain
     * vendor implementations do it for all radios. This new API should affect only the modem for
     * which it is called. A modem stack must be on/active only when both setRadioPower() and
     * enableModem() are set to on for it.
     *
     * SIM must be read if available even if modem is off/inactive.
     *
     * @param serial Serial number of request.
     * @param on True to turn on the logical modem, otherwise turn it off.
     *
     * Response function is IRadioResponse.enableModemResponse()
     */
    Return<void> enableModem(int32_t serial, bool on) override;

    /**
     * Request status of logical modem. It returns isEnabled=true if the logical modem is on.
     * This method is the getter method for enableModem.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getModemStackStatusResponse()
     */
    Return<void> getModemStackStatus(int32_t serial) override;

    /**
     * Setup a packet data connection. If DataCallResponse.status returns DataCallFailCause:NONE,
     * the data connection must be added to data calls and a unsolDataCallListChanged() must be
     * sent. The call remains until removed by subsequent unsolDataCallIstChanged(). It may be
     * lost due to many factors, including deactivateDataCall() being issued, the radio powered
     * off, reception lost or even transient factors like congestion. This data call list is
     * returned by getDataCallList() and dataCallListChanged().
     *
     * The Radio is expected to:
     *   - Create one data call context.
     *   - Create and configure a dedicated interface for the context.
     *   - The interface must be point to point.
     *   - The interface is configured with one or more addresses and is capable of sending and
     *     receiving packets. The prefix length of the addresses must be /32 for IPv4 and /128
     *     for IPv6.
     *   - Must not modify routing configuration related to this interface; routing management is
     *     exclusively within the purview of the Android OS.
     *   - Support simultaneous data call contexts up to DataRegStateResult.maxDataCalls specified
     *     in the response of getDataRegistrationState.
     *
     * @param serial Serial number of request.
     * @param accessNetwork The access network to setup the data call. If the data connection cannot
     *     be established on the specified access network, the setup request must be failed.
     * @param dataProfileInfo Data profile info.
     * @param roamingAllowed Indicates whether or not data roaming is allowed by the user.
     * @param reason The request reason. Must be DataRequestReason.NORMAL or
     *     DataRequestReason.HANDOVER.
     * @param addresses If the reason is DataRequestReason.HANDOVER, this indicates the list of link
     *     addresses of the existing data connection. The format is IP address with optional "/"
     *     prefix length (The format is defined in RFC-4291 section 2.3). For example, "192.0.1.3",
     *     "192.0.1.11/16", or "2001:db8::1/64". Typically one IPv4 or one IPv6 or one of each. If
     *     the prefix length is absent, then the addresses are assumed to be point to point with
     *     IPv4 with prefix length 32 or IPv6 with prefix length 128. This parameter must be ignored
     *     unless reason is DataRequestReason.HANDOVER.
     * @param dnses If the reason is DataRequestReason.HANDOVER, this indicates the list of DNS
     *     addresses of the existing data connection. The format is defined in RFC-4291 section
     *     2.2. For example, "192.0.1.3" or "2001:db8::1". This parameter must be ignored unless
     *     reason is DataRequestReason.HANDOVER.
     *
     * Response function is IRadioResponse.setupDataCallResponse()
     *
     * Note this API is same as 1.2 version except using the 1.4 AccessNetwork as the input param.
     */
    Return<void> setupDataCall_1_4(int32_t serial, ::android::hardware::radio::V1_4::AccessNetwork accessNetwork, const ::android::hardware::radio::V1_4::DataProfileInfo& dataProfileInfo, bool roamingAllowed, ::android::hardware::radio::V1_2::DataRequestReason reason, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& addresses, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& dnses) override;

    /**
     * Set an apn to initial attach network
     *
     * @param serial Serial number of request.
     * @param dataProfileInfo data profile containing APN settings
     *
     * Response callback is IRadioResponse.setInitialAttachApnResponse()
     */
    Return<void> setInitialAttachApn_1_4(int32_t serial, const ::android::hardware::radio::V1_4::DataProfileInfo& dataProfileInfo) override;

    /**
     * Send data profiles of the current carrier to the modem.
     *
     * @param serial Serial number of request.
     * @param profiles Array of DataProfile to set.
     *
     * Response callback is IRadioResponse.setDataProfileResponse()
     */
    Return<void> setDataProfile_1_4(int32_t serial, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_4::DataProfileInfo>& profiles) override;

    /**
     * Initiate emergency voice call, with zero or more emergency service category(s), zero or
     * more emergency Uniform Resource Names (URN), and routing information for handling the call.
     * Android uses this request to make its emergency call instead of using @1.0::IRadio.dial
     * if the 'address' in the 'dialInfo' field is identified as an emergency number by Android.
     *
     * In multi-sim scenario, if the emergency number is from a specific subscription, this radio
     * request is sent through the IRadio service that serves the subscription, no matter of the
     * PUK/PIN state of the subscription and the service state of the radio.
     *
     * Some countries or carriers require some emergency numbers that must be handled with normal
     * call routing if possible or emergency routing. 1) if the 'routing' field is specified as
     * @1.4::EmergencyNumberRouting#NORMAL, the implementation must try the full radio service to
     * use normal call routing to handle the call; if service cannot support normal routing, the
     * implementation must use emergency routing to handle the call. 2) if 'routing' is specified
     * as @1.4::EmergencyNumberRouting#EMERGENCY, the implementation must use emergency routing to
     * handle the call. 3) if 'routing' is specified as @1.4::EmergencyNumberRouting#UNKNOWN,
     * Android does not know how to handle the call.
     *
     * If the dialed emergency number does not have a specified emergency service category, the
     * 'categories' field is set to @1.4::EmergencyServiceCategory#UNSPECIFIED; if the dialed
     * emergency number does not have specified emergency Uniform Resource Names, the 'urns' field
     * is set to an empty list. If the underlying technology used to request emergency services
     * does not support the emergency service category or emergency uniform resource names, the
     * field 'categories' or 'urns' may be ignored.
     *
     * In the scenarios that the 'address' in the 'dialInfo' field has other functions besides the
     * emergency number function, if the 'hasKnownUserIntentEmergency' field is true, the user's
     * intent for this dial request is emergency call, and the modem must treat this as an actual
     * emergency dial; if the 'hasKnownUserIntentEmergency' field is false, Android does not know
     * user's intent for this call.
     *
     * If 'isTesting' is true, this request is for testing purpose, and must not be sent to a real
     * emergency service; otherwise it's for a real emergency call request.
     *
     * Reference: 3gpp 22.101, Section 10 - Emergency Calls;
     *            3gpp 23.167, Section 6 - Functional description;
     *            3gpp 24.503, Section 5.1.6.8.1 - General;
     *            RFC 5031
     *
     * @param serial Serial number of request.
     * @param dialInfo the same @1.0::Dial information used by @1.0::IRadio.dial.
     * @param categories bitfield<@1.4::EmergencyServiceCategory> the Emergency Service Category(s)
     *     of the call.
     * @param urns the emergency Uniform Resource Names (URN)
     * @param routing @1.4::EmergencyCallRouting the emergency call routing information.
     * @param hasKnownUserIntentEmergency Flag indicating if user's intent for the emergency call
     *     is known.
     * @param isTesting Flag indicating if this request is for testing purpose.
     *
     * Response function is IRadioResponse.emergencyDialResponse()
     */
    Return<void> emergencyDial(int32_t serial, const ::android::hardware::radio::V1_0::Dial& dialInfo, ::android::hardware::hidl_bitfield<::android::hardware::radio::V1_4::EmergencyServiceCategory> categories, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& urns, ::android::hardware::radio::V1_4::EmergencyCallRouting routing, bool hasKnownUserIntentEmergency, bool isTesting) override;

    /**
     * Starts a network scan
     *
     * @param serial Serial number of request.
     * @param request Defines the radio networks/bands/channels which need to be scanned.
     *
     * Same API as @1.2::IRadio.startNetworkScan_1_2, except using the
     * @1.4::IRadioResponse.startNetworkScanResponse_1_4 as the response.
     */
    Return<void> startNetworkScan_1_4(int32_t serial, const ::android::hardware::radio::V1_2::NetworkScanRequest& request) override;

    /**
     * Query the preferred network type bitmap.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getPreferredNetworkTypeBitmapResponse()
     */
    Return<void> getPreferredNetworkTypeBitmap(int32_t serial) override;

    /**
     * Requests to set the preferred network type for searching and registering.
     *
     * @param serial Serial number of request.
     * @param networkTypeBitmap a 32-bit bitmap of RadioAccessFamily.
     *
     * Response callback is IRadioResponse.setPreferredNetworkTypeBitmapResponse()
     */
    Return<void> setPreferredNetworkTypeBitmap(int32_t serial, ::android::hardware::hidl_bitfield<::android::hardware::radio::V1_4::RadioAccessFamily> networkTypeBitmap) override;

    /**
     * Set carrier restrictions. Expected modem behavior:
     *  If never receives this command:
     *  - Must allow all carriers
     *  Receives this command:
     *  - Only allow carriers specified in carriers. The restriction persists across power cycles
     *    and FDR. If a present SIM is allowed, modem must not reload the SIM. If a present SIM is
     *    *not* allowed, modem must detach from the registered network and only keep emergency
     *    service, and notify Android SIM refresh reset with new SIM state being
     *    CardState:RESTRICTED. Emergency service must be enabled.
     *
     * @param serial Serial number of request.
     * @param carriers CarrierRestrictionsWithPriority consisting allowed and excluded carriers
     *        as defined in types.hal
     * @param multiSimPolicy Policy to be used for devices with multiple SIMs.
     *
     * Response callback is IRadioResponse.setAllowedCarriersResponse_1_4()
     */
    Return<void> setAllowedCarriers_1_4(int32_t serial, const ::android::hardware::radio::V1_4::CarrierRestrictionsWithPriority& carriers, ::android::hardware::radio::V1_4::SimLockMultiSimPolicy multiSimPolicy) override;

    /**
     * Get carrier restrictions.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getAllowedCarriersResponse_1_4()
     */
    Return<void> getAllowedCarriers_1_4(int32_t serial) override;

    /**
     * Requests current signal strength and associated information.  Must succeed if radio is on.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getSignalStrengthResponse_1_4()
     */
    Return<void> getSignalStrength_1_4(int32_t serial) override;

    /**
     * Sets the signal strength reporting criteria.
     *
     * The resulting reporting rules are the AND of all the supplied criteria. For each RAN
     * The hysteresisDb and thresholds apply to only the following measured quantities:
     * -GERAN    - RSSI
     * -CDMA2000 - RSSI
     * -UTRAN    - RSCP
     * -EUTRAN   - RSRP/RSRQ/RSSNR
     * -NGRAN    - SSRSRP/SSRSRQ/SSSINR
     *
     * Note: Reporting criteria must be individually set for each RAN. For each RAN, if none of
     * reporting criteria of any measurement is set enabled
     * (see @1.5::SignalThresholdInfo.isEnabled), the reporting criteria for this RAN is
     * implementation-defined. For each RAN, if any of reporting criteria of any measure is set
     * enabled, the reporting criteria of the other measures in this RAN are set disabled
     * (see @1.5::SignalThresholdInfo.isEnabled) until they are set enabled.
     *
     * Response callback is
     * IRadioResponse.setSignalStrengthReportingCriteriaResponse_1_5()
     *
     * @param serial Serial number of request.
     * @param signalThresholdInfo Signal threshold info including the threshold values,
     *                            hysteresisDb, hysteresisMs and isEnabled.
     *                            See @1.5::SignalThresholdInfo for details.
     * @param accessNetwork The type of network for which to apply these thresholds.
     */
    Return<void> setSignalStrengthReportingCriteria_1_5(int32_t serial, const ::android::hardware::radio::V1_5::SignalThresholdInfo& signalThresholdInfo, ::android::hardware::radio::V1_5::AccessNetwork accessNetwork) override;

    /**
     * Sets the link capacity reporting criteria.
     *
     * The resulting reporting criteria are the AND of all the supplied criteria.
     *
     * Note: Reporting criteria must be individually set for each RAN. If unset, reporting criteria
     * for that RAN are implementation-defined.
     *
     * Response callback is IRadioResponse.setLinkCapacityReportingCriteriaResponse_1_5().
     *
     * @param serial Serial number of request.
     * @param hysteresisMs A hysteresis time in milliseconds to prevent flapping. A value of 0
     *     disables hysteresis.
     * @param hysteresisDlKbps An interval in kbps defining the required magnitude change between DL
     *     reports. hysteresisDlKbps must be smaller than the smallest threshold delta. A value of 0
     *     disables hysteresis.
     * @param hysteresisUlKbps An interval in kbps defining the required magnitude change between UL
     *     reports. hysteresisUlKbps must be smaller than the smallest threshold delta. A value of 0
     *     disables hysteresis.
     * @param thresholdsDownlinkKbps A vector of trigger thresholds in kbps for downlink reports. A
     *     vector size of 0 disables the use of DL thresholds for reporting.
     * @param thresholdsUplinkKbps A vector of trigger thresholds in kbps for uplink reports. A
     *     vector size of 0 disables the use of UL thresholds for reporting.
     * @param accessNetwork The type of network for which to apply these thresholds.
     */
    Return<void> setLinkCapacityReportingCriteria_1_5(int32_t serial, int32_t hysteresisMs, int32_t hysteresisDlKbps, int32_t hysteresisUlKbps, const ::android::hardware::hidl_vec<int32_t>& thresholdsDownlinkKbps, const ::android::hardware::hidl_vec<int32_t>& thresholdsUplinkKbps, ::android::hardware::radio::V1_5::AccessNetwork accessNetwork) override;

    /**
     * Enable or disable UiccApplications on the SIM. If disabled:
     *  - Modem will not register on any network.
     *  - SIM must be PRESENT, and the IccId of the SIM must still be accessible.
     *  - The corresponding modem stack is still functional, e.g. able to make emergency calls or
     *    do network scan.
     * By default if this API is not called, the uiccApplications must be enabled automatically.
     * It must work for both single SIM and DSDS cases for UX consistency.
     * The preference is per SIM, and must be remembered over power cycle, modem reboot, or SIM
     * insertion / unplug.
     *
     * @param serial Serial number of request.
     * @param enable true if to enable uiccApplications, false to disable.
     *
     * Response callback is IRadioResponse.enableUiccApplicationsResponse()
     */
    Return<void> enableUiccApplications(int32_t serial, bool enable) override;

    /**
     * Whether uiccApplications are enabled, or disabled.
     *
     * By default uiccApplications must be enabled, unless enableUiccApplications() with enable
     * being false is called.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.areUiccApplicationsEnabledResponse()
     */
    Return<void> areUiccApplicationsEnabled(int32_t serial) override;

    /**
     * Specify which bands modem's background scan must act on.
     * If specifyChannels is true, it only scans bands specified in specifiers.
     * If specifyChannels is false, it scans all bands.
     *
     * For example, CBRS is only on LTE band 48. By specifying this band,
     * modem saves more power.
     *
     * @param serial Serial number of request.
     * @param specifyChannels whether to scan bands defined in specifiers.
     * @param specifiers which bands to scan. Only used if specifyChannels is true.
     *
     * Response callback is IRadioResponse.setSystemSelectionChannelsResponse()
     */
    Return<void> setSystemSelectionChannels_1_5(int32_t serial, bool specifyChannels, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_5::RadioAccessSpecifier>& specifiers) override;

    /**
     * Starts a network scan.
     *
     * @param serial Serial number of request.
     * @param request Defines the radio networks/bands/channels which need to be scanned.
     *
     * Same API as @1.4::IRadio.startNetworkScan_1_4, except using the
     * 1.5 NetworkScanRequest as the input param.
     */
    Return<void> startNetworkScan_1_5(int32_t serial, const ::android::hardware::radio::V1_5::NetworkScanRequest& request) override;

    /**
     * Setup a packet data connection. If DataCallResponse.status returns DataCallFailCause:NONE,
     * the data connection must be added to data calls and a unsolDataCallListChanged() must be
     * sent. The call remains until removed by subsequent unsolDataCallIstChanged(). It may be
     * lost due to many factors, including deactivateDataCall() being issued, the radio powered
     * off, reception lost or even transient factors like congestion. This data call list is
     * returned by getDataCallList() and dataCallListChanged().
     *
     * The Radio is expected to:
     *   - Create one data call context.
     *   - Create and configure a dedicated interface for the context.
     *   - The interface must be point to point.
     *   - The interface is configured with one or more addresses and is capable of sending and
     *     receiving packets. The prefix length of the addresses must be /32 for IPv4 and /128
     *     for IPv6.
     *   - Must not modify routing configuration related to this interface; routing management is
     *     exclusively within the purview of the Android OS.
     *   - Support simultaneous data call contexts up to DataRegStateResult.maxDataCalls specified
     *     in the response of getDataRegistrationState.
     *
     * @param serial Serial number of request.
     * @param accessNetwork The access network to setup the data call. If the data connection cannot
     *     be established on the specified access network, the setup request must be failed.
     * @param dataProfileInfo Data profile info.
     * @param roamingAllowed Indicates whether or not data roaming is allowed by the user.
     * @param reason The request reason. Must be DataRequestReason.NORMAL or
     *     DataRequestReason.HANDOVER.
     * @param addresses If the reason is DataRequestReason.HANDOVER, this indicates the list of link
     *     addresses of the existing data connection. This parameter must be ignored unless reason
     *     is DataRequestReason.HANDOVER.
     * @param dnses If the reason is DataRequestReason.HANDOVER, this indicates the list of DNS
     *     addresses of the existing data connection. The format is defined in RFC-4291 section
     *     2.2. For example, "192.0.1.3" or "2001:db8::1". This parameter must be ignored unless
     *     reason is DataRequestReason.HANDOVER.
     *
     * Response function is IRadioResponse.setupDataCallResponse_1_5()
     *
     * Note this API is the same as the 1.4 version except using the
     * 1.5 AccessNetwork, DataProfileInto, and LinkAddress as the input param.
     */
    Return<void> setupDataCall_1_5(int32_t serial, ::android::hardware::radio::V1_5::AccessNetwork accessNetwork, const ::android::hardware::radio::V1_5::DataProfileInfo& dataProfileInfo, bool roamingAllowed, ::android::hardware::radio::V1_2::DataRequestReason reason, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_5::LinkAddress>& addresses, const ::android::hardware::hidl_vec<::android::hardware::hidl_string>& dnses) override;

    /**
     * Set an APN to initial attach network.
     *
     * @param serial Serial number of request.
     * @param dataProfileInfo data profile containing APN settings
     *
     * Response callback is IRadioResponse.setInitialAttachApnResponse_1_5()
     *
     * Note this API is the same as the 1.4 version except using the 1.5 DataProfileInfo
     * as the input param.
     */
    Return<void> setInitialAttachApn_1_5(int32_t serial, const ::android::hardware::radio::V1_5::DataProfileInfo& dataProfileInfo) override;

    /**
     * Send data profiles of the current carrier to the modem.
     *
     * @param serial Serial number of request.
     * @param profiles Array of DataProfileInfo to set.
     *
     * Response callback is IRadioResponse.setDataProfileResponse_1_5()
     *
     * Note this API is the same as the 1.4 version except using the 1.5 DataProfileInfo
     * as the input param.
     */
    Return<void> setDataProfile_1_5(int32_t serial, const ::android::hardware::hidl_vec<::android::hardware::radio::V1_5::DataProfileInfo>& profiles) override;

    /**
     * Toggle radio on and off (for "airplane" mode)
     * If the radio is turned off/on the radio modem subsystem
     * is expected return to an initialized state. For instance,
     * any voice and data calls must be terminated and all associated
     * lists emptied.
     *
     * When setting radio power on to exit from airplane mode to place an emergency call on this
     * logical modem, powerOn, forEmergencyCall and preferredForEmergencyCall must be true. In
     * this case, this modem is optimized to scan only emergency call bands, until:
     * 1) Emergency call is completed; or
     * 2) Another setRadioPower_1_5 is issued with forEmergencyCall being false or
     * preferredForEmergencyCall being false; or
     * 3) Timeout after 30 seconds if dial or emergencyDial is not called.
     * Once one of these conditions is reached, the modem should move into normal operation.
     *
     * @param serial Serial number of request.
     * @param powerOn To turn on radio -> on = true, to turn off radio -> on = false.
     * @param forEmergencyCall To indication to radio if this request is due to emergency call.
     *      No effect if powerOn is false.
     * @param preferredForEmergencyCall indicate whether the following emergency call will be sent
     *      on this modem or not. No effect if forEmergencyCall is false, or powerOn is false.
     *
     * Response callback is IRadioConfigResponse. setRadioPowerResponse_1_5.
     */
    Return<void> setRadioPower_1_5(int32_t serial, bool powerOn, bool forEmergencyCall, bool preferredForEmergencyCall) override;

    /**
     * Sets the indication filter.
     *
     * Prevents the reporting of specified unsolicited indications from the radio. This is used
     * for power saving in instances when those indications are not needed. If unset, defaults to
     * @1.5::IndicationFilter:ALL.
     *
     * @param serial Serial number of request.
     * @param indicationFilter 32-bit bitmap of IndicationFilter. Bits set to 1 indicate the
     *     indications are enabled. See @1.5::IndicationFilter for the definition of each bit.
     *
     * Response callback is IRadioResponse.setIndicationFilterResponse()
     */
    Return<void> setIndicationFilter_1_5(int32_t serial, ::android::hardware::hidl_bitfield<::android::hardware::radio::V1_5::IndicationFilter> indicationFilter) override;

    /**
     * Get all the barring info for the current camped cell applicable to the current user.
     *
     * @param serial Serial number of request.
     *
     * Response callback is IRadioResponse.getBarringInfoResponse()
     */
    Return<void> getBarringInfo(int32_t serial) override;

    /**
     * Request current voice registration state.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getVoiceRegistrationStateResponse_1_5()
     */
    Return<void> getVoiceRegistrationState_1_5(int32_t serial) override;

    /**
     * Request current data registration state.
     *
     * @param serial Serial number of request.
     *
     * Response function is IRadioResponse.getDataRegistrationStateResponse_1_5()
     */
    Return<void> getDataRegistrationState_1_5(int32_t serial) override;

    /*
     * Manually select a specified network.
     * This request must not respond until the new operator is selected and registered.
     * Per TS 23.122, the RAN is just the initial suggested value.
     * If registration fails, the RAN is not available afterwards, or the RAN is not within
     * the network types specified by IRadio::setPreferredNetworkTypeBitmap, then the modem
     * will need to select the next best RAN for network registration.
     *
     * @param serial Serial number of request.
     * @param operatorNumeric String specifying MCCMNC of network to select (eg "310170").
     * @param ran Initial suggested radio access network type. If value is UNKNOWN, the modem
     *     will select the next best RAN for network registration.
     *
     * Response function is IRadioResponse.setNetworkSelectionModeManualResponse_1_5()
     */
    Return<void> setNetworkSelectionModeManual_1_5(int32_t serial, const ::android::hardware::hidl_string& operatorNumeric, ::android::hardware::radio::V1_5::RadioAccessNetworks ran) override;

    /**
     * Send an SMS message. Identical to sendCdmaSms,
     * except that more messages are expected to be sent soon.
     *
     * @param serial Serial number of request.
     * @param sms Cdma Sms to be sent described by CdmaSmsMessage in types.hal
     *
     * Response callback is IRadioResponse.sendCdmaSMSExpectMoreResponse()
     */
    Return<void> sendCdmaSmsExpectMore(int32_t serial, const ::android::hardware::radio::V1_0::CdmaSmsMessage& sms) override;

    /**
     * Request that deactivates one category of device personalization. Device personalization
     * generally binds the device so it can only be used on one carrier or even one carrier subnet
     * (See TS 22.022). When the user has gained the rights to unbind the device (at the end of a
     * contract period or other event), the controlKey will be delivered to either the user for
     * manual entry or to a carrier app on the device for automatic entry.
     *
     * @param serial Serial number of request.
     * @param persoType SIM personalization type.
     * @param controlKey the unlock code for removing persoType personalization from this device
     *
     * Response function is IRadioResponse.supplySimDepersonalizationResponse()
     */
    Return<void> supplySimDepersonalization(int32_t serial, ::android::hardware::radio::V1_5::PersoSubstate persoType, const ::android::hardware::hidl_string& controlKey) override;
};



