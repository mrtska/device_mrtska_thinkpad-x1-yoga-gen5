PRODUCT_SHIPPING_API_LEVEL := 30
PRODUCT_PRODUCT_VNDK_VERSION := current

$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/mainline_system.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/handheld_vendor.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/telephony_vendor.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/handheld_system_ext.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/telephony_system_ext.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/developer_gsi_keys.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_product.mk)

$(call inherit-product, frameworks/native/build/phone-xhdpi-6144-dalvik-heap.mk)

$(call inherit-product, $(LOCAL_PATH)/device-x1_yoga_gen5.mk)

PRODUCT_MANUFACTURER := mrtska
PRODUCT_BRAND := Android
PRODUCT_NAME := aosp_x1_yoga_gen5
PRODUCT_DEVICE := thinkpad-20ub
PRODUCT_MODEL := AOSP on ThinkPad X1 Yoga Gen5

GAPPS_VARIANT := pico
$(call inherit-product-if-exists, vendor/opengapps/build/opengapps-packages.mk)

#$(call inherit-product-if-exists, vendor/nativebridge/nativebridge.mk)
$(call inherit-product-if-exists, vendor/nativebridge_houdini/nativebridge.mk)
