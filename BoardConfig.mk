TARGET_BOARD_PLATFORM := thinkpad

TARGET_NO_BOOTLOADER := true

TARGET_CPU_ABI := x86_64
TARGET_ARCH := x86_64
TARGET_ARCH_VARIANT := x86_64
TARGET_CPU_VARIANT := x86_64

TARGET_2ND_CPU_ABI := x86
TARGET_2ND_ARCH := x86
TARGET_2ND_ARCH_VARIANT := x86_64
TARGET_2ND_CPU_VARIANT := x86_64

TARGET_NATIVE_BRIDGE_ARCH := arm64
TARGET_NATIVE_BRIDGE_ARCH_VARIANT := armv8-a
TARGET_NATIVE_BRIDGE_CPU_VARIANT := generic
TARGET_NATIVE_BRIDGE_ABI := arm64-v8a

TARGET_NATIVE_BRIDGE_2ND_ARCH := arm
TARGET_NATIVE_BRIDGE_2ND_ARCH_VARIANT := armv7-a-neon
TARGET_NATIVE_BRIDGE_2ND_CPU_VARIANT := generic
TARGET_NATIVE_BRIDGE_2ND_ABI := armeabi-v7a armeabi

BUILD_ARM_FOR_X86 := true

TARGET_USES_64_BIT_BINDER := true

BOARD_MALLOC_ALIGNMENT := 16

TARGET_NO_KERNEL := false
BOARD_USES_ALSA_AUDIO ?= true
BUILD_WITH_ALSA_UTILS ?= true

BOARD_PROPERTY_OVERRIDES_SPLIT_ENABLED := true
BOARD_VNDK_VERSION := current

# Don't build emulator.
BUILD_EMULATOR := false

# gpu settings.
USE_OPENGL_RENDERER := true
BOARD_GPU_DRIVERS := swrast i965 i915
BOARD_USES_GRALLOC1 := true
BOARD_USES_IA_HWCOMPOSER := true
TARGET_USES_HWC2 := true
INTEL_MINIGBM := vendor/intel/minigbm
BOARD_USE_CUSTOMIZED_MESA := true

# 10GB / 2 10737418240
BOARD_USERDATAIMAGE_PARTITION_SIZE := 5368709120

# partition names
TARGET_COPY_OUT_SYSTEM_EXT := system_ext
TARGET_COPY_OUT_VENDOR := vendor
TARGET_COPY_OUT_PRODUCT := product

# image settings
BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_SYSTEM_EXTIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_PRODUCTIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_VENDORIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_USERDATAIMAGE_FILE_SYSTEM_TYPE := f2fs
BOARD_USES_METADATA_PARTITION := true

# Use F2FS as user partition.
TARGET_USERIMAGES_USE_F2FS := true

# Don't use sparse images.
TARGET_USERIMAGES_SPARSE_EXT_DISABLED := true

TARGET_PRELINK_MODULE := false

# WI-FI settings.
WPA_SUPPLICANT_VERSION := VER_0_8_X
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
BOARD_HOSTAPD_DRIVER := NL80211
BOARD_WLAN_DEVICE := intel
WIFI_HIDL_UNIFIED_SUPPLICANT_SERVICE_RC_ENTRY := true

# Audio settings.
BOARD_USES_ALSA_AUDIO := true
BOARD_USES_TINY_ALSA_AUDIO := true
BOARD_USES_GENERIC_AUDIO := true
INTEL_AUDIO_HAL := audio

# Bluetooth settings.
BOARD_HAVE_BLUETOOTH := true
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := device/generic/common/bluetooth
BOARD_HAVE_BLUETOOTH_INTEL_ICNV := true

# Sensor settings.
USE_IIO_SENSOR_HAL := true

# Media settings.
INTEL_STAGEFRIGHT := true
BOARD_HAVE_MEDIASDK_OPEN_SOURCE := true
BOARD_HAVE_OMX_SRC := true

# default display density. 
TARGET_SCREEN_DENSITY := 320

# SELinux
BOARD_VENDOR_SEPOLICY_DIRS += device/mrtska/thinkpad-20ub/sepolicy/nonplat 
PRODUCT_PRIVATE_SEPOLICY_DIRS += device/mrtska/thinkpad-20ub/sepolicy/plat_private

BUILD_BROKEN_USES_BUILD_COPY_HEADERS := true
BUILD_BROKEN_USES_BUILD_HOST_STATIC_LIBRARY := true
