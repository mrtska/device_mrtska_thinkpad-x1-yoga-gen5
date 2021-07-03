LOCAL_PATH := device/mrtska/thinkpad-20ub

PRODUCT_CHARACTERISTICS := tablet,nosdcard

# Use super partitions.
PRODUCT_USE_DYNAMIC_PARTITIONS := true
BOARD_BUILD_SUPER_IMAGE_BY_DEFAULT := true
BOARD_SUPER_PARTITION_SIZE := 8589934592 #2147483648

BOARD_SUPER_PARTITION_GROUPS := thinkpad_x1_yoga
BOARD_THINKPAD_X1_YOGA_SIZE := 8588934592 #2143289344
BOARD_THINKPAD_X1_YOGA_PARTITION_LIST := system system_ext vendor product

TARGET_NO_VENDOR_BOOT := true

#PRODUCT_ENFORCE_VINTF_MANIFEST_OVERRIDE := false

LOCAL_KERNEL := kernel/common/out/arch/x86/boot/bzImage
PRODUCT_COPY_FILES += \
    $(LOCAL_KERNEL):kernel

PRODUCT_FULL_TREBLE_OVERRIDE := true
PRODUCT_USE_VNDK := true

DEVICE_MANIFEST_FILE := $(LOCAL_PATH)/manifest.xml
DEVICE_MATRIX_FILE := $(LOCAL_PATH)/compatibility_matrix.xml
PRODUCT_OTA_ENFORCE_VINTF_KERNEL_REQUIREMENTS := false

PRODUCT_SOONG_NAMESPACES += $(LOCAL_PATH) \
    #frameworks/libs/native_bridge_support/overriding

#PRODUCT_PROPERTY_OVERRIDES += \
    ro.build.fingerprint=Android/aosp_x1_yoga_gen5/thinkpad-20ub:11/RP1A.201005.004.A1/mrtska12261106:eng/test-keys

PRODUCT_PACKAGES += \
    init_system \
	init_vendor \
	android.hardware.configstore@1.1-service \
	android.hardware.cas@1.2 \
	vndservicemanager \
	libminijail \
    NavigationBarMode2ButtonOverlay

PRODUCT_PACKAGES += \
    libEGL_swiftshader \
    libGLESv1_CM_swiftshader \
    libGLESv2_swiftshader 

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/fstab.hardware:$(TARGET_COPY_OUT_RAMDISK)/fstab.thinkpad \
    $(LOCAL_PATH)/fstab.hardware:$(TARGET_COPY_OUT_VENDOR)/etc/fstab.thinkpad \
	$(LOCAL_PATH)/init.hardware.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/hw/init.thinkpad.rc \
	$(LOCAL_PATH)/init.hardware.usb.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/hw/init.thinkpad.usb.rc \
	$(LOCAL_PATH)/init.sh:$(TARGET_COPY_OUT_VENDOR)/etc/init/hw/init.sh \
	$(LOCAL_PATH)/ueventd.rc:$(TARGET_COPY_OUT_VENDOR)/ueventd.rc

# copy linux firmwares.
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/firmware/iwlwifi-QuZ-a0-hr-b0-59.ucode:$(TARGET_COPY_OUT_RAMDISK)/lib/firmware/iwlwifi-QuZ-a0-hr-b0-59.ucode \
    $(LOCAL_PATH)/firmware/i915/kbl_dmc_ver1_04.bin:$(TARGET_COPY_OUT_RAMDISK)/lib/firmware/i915/kbl_dmc_ver1_04.bin \
    $(LOCAL_PATH)/firmware/intel/ibt-19-0-4.sfi:$(TARGET_COPY_OUT_RAMDISK)/lib/firmware/intel/ibt-19-0-4.sfi \
    $(LOCAL_PATH)/firmware/intel/ibt-19-0-4.ddc:$(TARGET_COPY_OUT_RAMDISK)/lib/firmware/intel/ibt-19-0-4.ddc
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/firmware/iwlwifi-QuZ-a0-hr-b0-59.ucode:$(TARGET_COPY_OUT_VENDOR)/firmware/iwlwifi-QuZ-a0-hr-b0-59.ucode \
    $(LOCAL_PATH)/firmware/i915/kbl_dmc_ver1_04.bin:$(TARGET_COPY_OUT_VENDOR)/firmware/i915/kbl_dmc_ver1_04.bin \
    $(LOCAL_PATH)/firmware/intel/ibt-19-0-4.sfi:$(TARGET_COPY_OUT_VENDOR)/firmware/intel/ibt-19-0-4.sfi \
    $(LOCAL_PATH)/firmware/intel/ibt-19-0-4.ddc:$(TARGET_COPY_OUT_VENDOR)/firmware/intel/ibt-19-0-4.ddc

PRODUCT_PROPERTY_OVERRIDES += \
    service.adb.tcp.port=5555 \
    persist.adb.tcp.port=5555 \
    ro.secure=0 \
 #   ro.boot.quiescent=1

#PRODUCT_PROPERTY_OVERRIDES += \
    ro.opengles.version = 196608 \
    ro.hardware.vulkan.level = 1 \
    ro.hardware.vulkan.version = 4194307

PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.vulkan.level-1.xml:system/etc/permissions/android.hardware.vulkan.level.xml \
    frameworks/native/data/etc/android.hardware.vulkan.version-1_0_3.xml:system/etc/permissions/android.hardware.vulkan.version.xml

USE_XML_AUDIO_POLICY_CONF := 1

#PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/tablet_core_hardware.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/tablet_core_hardware.xml \

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/thinkpad_hardware.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/thinkpad_hardware.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.software.freeform_window_management.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.software.freeform_window_management.xml

DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Audio HAL
PRODUCT_PACKAGES += \
    android.hardware.audio@6.0-impl \
    android.hardware.audio.effect@6.0-impl \
    android.hardware.soundtrigger@2.3-impl \
    android.hardware.audio.service \
    audio.usb.default \
    audio.r_submix.default \
    libaudio-resampler \
    audio.primary.thinkpad \
    audio.hdmi.thinkpad \
    audio.usb.thinkpad \
    tinyplay \
    audio_policy_engine_criteria.xml
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/audio/audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_configuration.xml \
    $(LOCAL_PATH)/audio/mixer_paths_1.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths_1.xml \
    $(LOCAL_PATH)/audio/mixer_paths_ehl.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths_ehl.xml \
    $(LOCAL_PATH)/audio/mixer_paths_usb.xml:$(TARGET_COPY_OUT_VENDOR)/etc/mixer_paths_usb.xml \
    $(LOCAL_PATH)/audio/audio_policy_engine_criterion_types.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_engine_criterion_types.xml \
    $(LOCAL_PATH)/audio/audio_policy_engine_product_strategies.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_engine_product_strategies.xml \
    frameworks/av/services/audiopolicy/config/a2dp_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/a2dp_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/audio_policy_volumes.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_volumes.xml \
    frameworks/av/services/audiopolicy/config/default_volume_tables.xml:$(TARGET_COPY_OUT_VENDOR)/etc/default_volume_tables.xml \
    frameworks/av/services/audiopolicy/config/r_submix_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/r_submix_audio_policy_configuration.xml \
    frameworks/av/services/audiopolicy/config/usb_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/usb_audio_policy_configuration.xml \
    frameworks/av/media/libeffects/data/audio_effects.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_effects.xml \
    frameworks/native/data/etc/android.hardware.audio.output.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.audio.output.xml \
    frameworks/native/data/etc/android.hardware.audio.low_latency.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.audio.low_latency.xml
#    $(LOCAL_PATH)/audio/audio_policy_engine_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_engine_configuration.xml \

# Media Codec HAL
PRODUCT_PACKAGES += \
    android.hardware.media.omx@1.0-service \
    libstagefrighthw \
    libmfx_omx_core \
    libmfx_omx_components_hw \
    i965_drv_video
PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_c2.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_c2.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_c2_audio.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_c2_audio.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_c2_video.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_c2_video.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_video.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_google_video.xml \
    $(LOCAL_PATH)/media/media_codecs.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs.xml \
    $(LOCAL_PATH)/media/media_codecs_performance.xml:$(TARGET_COPY_OUT_VENDOR)/etc/media_codecs_performance.xml \
    $(LOCAL_PATH)/media/mfx_omxil_core.conf:$(TARGET_COPY_OUT_VENDOR)/etc/mfx_omxil_core.conf \
    $(LOCAL_PATH)/seccomp_policy/mediacodec.policy:$(TARGET_COPY_OUT_VENDOR)/etc/seccomp_policy/mediacodec.policy \
    $(LOCAL_PATH)/seccomp_policy/mediaswcodec.policy:$(TARGET_COPY_OUT_VENDOR)/etc/seccomp_policy/mediaswcodec.policy

# HWComposer HAL
PRODUCT_PACKAGES += \
    android.hardware.graphics.composer@2.3-impl \
    android.hardware.graphics.composer@2.3-service \
	hwcomposer.thinkpad
PRODUCT_PROPERTY_OVERRIDES += \
   vendor.hwc.backend_override=client \
    ro.hardware.egl=mesa \
    ro.opengles.version = 196610 \
	ro.hardware.hwcomposer=thinkpad \
    ro.hardware.gralloc=intel
PRODUCT_COPY_FILES += \
    vendor/intel/IA-Hardware-Composer/hwc_display.ini:$(TARGET_COPY_OUT_VENDOR)/etc/hwc_display.ini

# Graphics HAL
PRODUCT_PACKAGES += \
    android.hardware.graphics.allocator@2.0-impl \
    android.hardware.graphics.allocator@2.0-service \
    android.hardware.graphics.mapper@2.0-impl-2.1 \
    gralloc.intel \
    libGLES_mesa \
    vulkan.thinkpad
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.vulkan.level-1.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.vulkan.level-1.xml \
    frameworks/native/data/etc/android.hardware.vulkan.version-1_1.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.vulkan.version-1_1.xml

# Keymaster HAL
PRODUCT_PACKAGES += \
    android.hardware.keymaster@4.1-impl \
    android.hardware.keymaster@4.1-service

# Health HAL
PRODUCT_PACKAGES += \
    android.hardware.health@2.1-impl \
    android.hardware.health@2.1-service

# Gatekeeper HAL
PRODUCT_PACKAGES += \
    android.hardware.gatekeeper@1.0-impl \
    android.hardware.gatekeeper@1.0-service.software

# Fingerprint HAL
PRODUCT_PACKAGES += \
    android.hardware.biometrics.fingerprint@2.1-service \
    fingerprint.synaptics
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.fingerprint.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.fingerprint.xml
PRODUCT_PROPERTY_OVERRIDES += \
    ro.hardware.fingerprint=synaptics

# NFC HAL
PRODUCT_PACKAGES += \
    android.hardware.nfc@1.2-service \
#    android.hardware.secure_element@1.1-service
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.nfc.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/native/data/etc/android.hardware.nfc.hcef.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.nfc.hcef.xml \
    frameworks/native/data/etc/com.nxp.mifare.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/com.nxp.mifare.xml \
    $(LOCAL_PATH)/nfc/libnfc-nxp.conf:$(TARGET_COPY_OUT_VENDOR)/etc/libnfc-nxp.conf

# Camera HAL
#PRODUCT_PACKAGES += \

PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.camera.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.xml \
    frameworks/native/data/etc/android.hardware.camera.external.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.camera.external.xml

# GPS HAL
#PRODUCT_PACKAGES += \

PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.location.gps.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.location.gps.xml

# Power HAL
PRODUCT_PACKAGES += \
    android.hardware.power-service.example

# Power Stats HAL
PRODUCT_PACKAGES += \
    android.hardware.power.stats@1.0-service.mock

# USB HAL
PRODUCT_PACKAGES += \
    android.hardware.usb@1.0-service
#    android.hardware.usb.gadget@1.1-service
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.usb.host.xml

# Memtrack HAL
PRODUCT_PACKAGES += \
    memtrack.default \
    android.hardware.memtrack@1.0-impl \
    android.hardware.memtrack@1.0-service

# Light HAL
PRODUCT_PACKAGES += \
    android.hardware.light@2.0-impl \
    android.hardware.light@2.0-service \
    lights.thinkpad
PRODUCT_PROPERTY_OVERRIDES += \
    ro.hardware.lights=thinkpad

# Sensors HAL
PRODUCT_PACKAGES += \
    android.hardware.sensors@1.0-impl \
    android.hardware.sensors@1.0-service \
    sensors.thinkpad
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.sensor.proximity.xml
PRODUCT_PROPERTY_OVERRIDES += \
    ro.hardware.sensors=thinkpad
# Vibrator HAL
#PRODUCT_PACKAGES += \
	android.hardware.vibrator-service.example

# DRM HAL
PRODUCT_PACKAGES += \
    android.hardware.drm@1.0-impl \
    android.hardware.drm@1.0-service \
    android.hardware.drm@1.3-service.clearkey \
    android.hardware.drm@1.3-service.widevine

# RenderScript HAL
PRODUCT_PACKAGES += \
    android.hardware.renderscript@1.0-impl

# Bluetooth HAL
PRODUCT_PACKAGES += \
    android.hardware.bluetooth@1.0-service.vbt \
    android.hardware.bluetooth.audio@2.0-impl \
    android.hardware.bluetooth.a2dp@1.0-impl.mock \
    audio.bluetooth.default \
    audio.a2dp.default \
    libbt-vendor
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.bluetooth.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.bluetooth.xml \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.bluetooth_le.xml

# Wifi HAL
PRODUCT_PACKAGES += \
    android.hardware.wifi@1.0-service \
    libwpa_client \
    hostapd \
    wpa_supplicant
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.wifi.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.xml \
    $(LOCAL_PATH)/wifi/wpa_supplicant.conf:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/wpa_supplicant.conf

# Radio HAL
ENABLE_VENDOR_RIL_SERVICE := true
PRODUCT_PACKAGES += \
    android.hardware.radio@1.5-radio-service.l860gl
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.hardware.telephony.ims.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.telephony.ims.xml \
    device/sample/etc/apns-full-conf.xml:$(TARGET_COPY_OUT_SYSTEM)/etc/apns-conf.xml

# Ethernet
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.ethernet.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.ethernet.xml

