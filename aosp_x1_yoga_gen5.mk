# Copyright 2020 mrtska

#
# All components inherited here go to system image
#

PRODUCT_SHIPPING_API_LEVEL := 30

$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/mainline_system.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/handheld_vendor.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/handheld_system_ext.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/telephony_system_ext.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/developer_gsi_keys.mk)

$(call inherit-product, $(LOCAL_PATH)/device-x1_yoga_gen5.mk)

PRODUCT_MANUFACTURER := mrtska
PRODUCT_BRAND := Android
PRODUCT_NAME := aosp_x1_yoga_gen5
PRODUCT_DEVICE := thinkpad-x1-yoga-gen5
PRODUCT_MODEL := AOSP on x1_yoga_gen5

