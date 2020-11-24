# Copyright 2020 mrtska

LOCAL_PATH := device/mrtska/thinkpad-x1-yoga-gen5

#DEVICE_MANIFEST_FILE := $(LOCAL_PATH)/manifest.xml


PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/fstab.hardware:$(TARGET_COPY_OUT_RAMDISK)/fstab.thinkpad


PRODUCT_PACKAGES += \
    init_system \
    init_vendor