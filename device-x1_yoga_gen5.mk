# Copyright 2020 mrtska

LOCAL_PATH := device/mrtska/thinkpad-x1-yoga-gen5


# Use super partitions.
PRODUCT_USE_DYNAMIC_PARTITIONS := true
BOARD_BUILD_SUPER_IMAGE_BY_DEFAULT := true
BOARD_SUPER_PARTITION_SIZE := 2147483648

BOARD_SUPER_PARTITION_GROUPS := thinkpad_x1_yoga
BOARD_THINKPAD_X1_YOGA_SIZE := 2143289344
BOARD_THINKPAD_X1_YOGA_PARTITION_LIST := system system_ext vendor product

TARGET_NO_VENDOR_BOOT := true

PRODUCT_ENFORCE_VINTF_MANIFEST_OVERRIDE := false

PRODUCT_FULL_TREBLE_OVERRIDE := true
PRODUCT_USE_VNDK := true

DEVICE_MANIFEST_FILE := $(LOCAL_PATH)/manifest.xml
#DEVICE_MATRIX_FILE := $(LOCAL_PATH)/compatibility_matrix.xml

# PRODUCT_PACKAGES := \
#     hwcomposer.drm  \
#     gralloc.drm     \
#     gralloc.gbm     \
#     libGLES_mesa    \
#     libtxc_dxtn     

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


PRODUCT_PROPERTY_OVERRIDES += \
    ro.hardware.egl=mesa \
	ro.hardware.gralloc=default \
	ro.hardware.hwcomposer=drm

#PRODUCT_PROPERTY_OVERRIDES += \
    ro.opengles.version = 196608 \
    ro.hardware.vulkan.level = 1 \
    ro.hardware.vulkan.version = 4194307

PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.vulkan.level-1.xml:system/etc/permissions/android.hardware.vulkan.level.xml \
    frameworks/native/data/etc/android.hardware.vulkan.version-1_0_3.xml:system/etc/permissions/android.hardware.vulkan.version.xml

USE_XML_AUDIO_POLICY_CONF := 1

PRODUCT_COPY_FILES += \
    frameworks/av/services/audiopolicy/config/primary_audio_policy_configuration.xml:$(TARGET_COPY_OUT_VENDOR)/etc/audio_policy_configuration.xml


# Install kernel modules.

# Audio HAL
PRODUCT_PACKAGES += \
    android.hardware.audio@2.0-impl \
	android.hardware.audio@6.0-impl \
    android.hardware.soundtrigger@2.0-impl \
    android.hardware.soundtrigger@2.3-impl \
    android.hardware.audio.effect@6.0-impl \
    android.hardware.audio.service

# HWComposer HAL
PRODUCT_PACKAGES += \
    android.hardware.graphics.composer@2.1-impl \
    android.hardware.graphics.composer@2.1-service \
	hwcomposer.drm \
	gralloc.minigbm_intel

# Graphics HAL
PRODUCT_PACKAGES += \
    android.hardware.graphics.mapper@2.0-impl-2.1 \
	android.hardware.graphics.mapper@4.0-service \
    android.hardware.graphics.allocator@2.0-impl \
	android.hardware.graphics.allocator@2.0-service

PRODUCT_PACKAGES += \
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
    android.hardware.power@1.0-impl \
    android.hardware.power@1.0-service

# Power Stats HAL
PRODUCT_PACKAGES += \
    android.hardware.power.stats@1.0-service.mock

# USB Gadget HAL
#RODUCT_PACKAGES += \
    android.hardware.usb.gadget@1.1-service

# Memtrack HAL
PRODUCT_PACKAGES += \
    memtrack.default \
    android.hardware.memtrack@1.0-impl \
    android.hardware.memtrack@1.0-service

# Light HAL
PRODUCT_PACKAGES += \
    android.hardware.light@2.0-impl \
    android.hardware.light@2.0-service

# Sensors HAL
#PRODUCT_PACKAGES += \
    android.hardware.sensors@1.0-impl \
    android.hardware.sensors@1.0-service

# Vibrator HAL
PRODUCT_PACKAGES += \
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