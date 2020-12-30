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
    external/mesa3d

PRODUCT_PACKAGES := \
    init_system \
	init_vendor \
	android.hardware.configstore@1.1-service \
	android.hardware.cas@1.2 \
	vndservicemanager \
	libminijail

PRODUCT_PACKAGES += \
    libEGL_swiftshader \
    libGLESv1_CM_swiftshader \
    libGLESv2_swiftshader 

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/fstab.hardware:$(TARGET_COPY_OUT_RAMDISK)/fstab.thinkpad \
    $(LOCAL_PATH)/fstab.hardware:$(TARGET_COPY_OUT_VENDOR)/etc/fstab.thinkpad \
	$(LOCAL_PATH)/init.hardware.rc:$(TARGET_COPY_OUT_VENDOR)/etc/init/hw/init.thinkpad.rc \
	$(LOCAL_PATH)/init.sh:$(TARGET_COPY_OUT_SYSTEM)/etc/init.sh

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
    ro.hardware.egl=mesa \
	ro.hardware.hwcomposer=drm

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


# Audio HAL
PRODUCT_PACKAGES += \
    android.hardware.audio@2.0-impl \
	android.hardware.audio@6.0-impl \
    android.hardware.audio.effect@6.0-impl \
    android.hardware.audio.service
PRODUCT_COPY_FILES += \
    frameworks/av/services/audiopolicy/config/primary_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_configuration.xml \
    frameworks/av/media/libeffects/data/audio_effects.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_effects.xml

# HWComposer HAL
PRODUCT_PACKAGES += \
    android.hardware.graphics.composer@2.3-impl \
    android.hardware.graphics.composer@2.3-service \
	hwcomposer.drm
# Avoid blink background layer.
PRODUCT_PROPERTY_OVERRIDES += \
   vendor.hwc.backend_override=client

# Graphics HAL
PRODUCT_PACKAGES += \
    android.hardware.graphics.allocator@4.0-service.minigbm \
    android.hardware.graphics.mapper@4.0-impl.minigbm \
    libGLES_mesa

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

# Power HAL
PRODUCT_PACKAGES += \
    android.hardware.power-service.example

# Power Stats HAL
PRODUCT_PACKAGES += \
    android.hardware.power.stats@1.0-service.mock

# USB Gadget HAL
#RODUCT_PACKAGES += \
    android.hardware.usb.gadget@1.1-service
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
#PRODUCT_PACKAGES += \
    android.hardware.sensors@1.0-impl \
    android.hardware.sensors@1.0-service

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
#PRODUCT_PACKAGES += \
    android.hardware.bluetooth@1.1-service \
    android.hardware.bluetooth@1.0-impl

# Wifi HAL
PRODUCT_PACKAGES += \
    android.hardware.wifi@1.0-service \
    libwpa_client \
    hostapd \
    wpa_supplicant
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.wifi.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.wifi.xml \
    $(LOCAL_PATH)/wifi/wpa_supplicant.conf:$(TARGET_COPY_OUT_VENDOR)/etc/wifi/wpa_supplicant.conf

# Ethernet
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.ethernet.xml:$(TARGET_COPY_OUT_VENDOR)/etc/permissions/android.hardware.ethernet.xml

