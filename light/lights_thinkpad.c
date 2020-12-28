

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <log/log.h>
#include <hardware/lights.h>


const char* BACKLIGHT_MAX_BRIGHTNESS = "/sys/class/backlight/intel_backlight/max_brightness";
const char* BACKLIGHT_BRIGHTNESS = "/sys/class/backlight/intel_backlight/brightness";

int backlight_max_brightness = 0;

static int rgb_to_brightness(struct light_state_t const* state) {

    int color = state->color & 0x00ffffff;
    return ((77*((color>>16)&0x00ff)) + (150*((color>>8)&0x00ff)) + (29*(color&0x00ff))) >> 8;
}

static int set_light_backlight(struct light_device_t* dev, struct light_state_t const* state) {

    int brightness = rgb_to_brightness(state);
    int mul = backlight_max_brightness / 255;

    int value = brightness * mul;

    int fd = open(BACKLIGHT_BRIGHTNESS, O_WRONLY);
    if (fd <= 0) {

        ALOGE("Could not open backlight file. %s\n", BACKLIGHT_BRIGHTNESS);
        return -1;
    }

    char buf[10];
    size_t bytes = snprintf(buf, sizeof(buf), "%d\n", value);

    ssize_t result = write(fd, buf, bytes);
    close(fd);

    if (result == -1) {

        return -errno;
    }

    return 0;
}

static int close_lights(struct light_device_t *dev) {

    if (dev) {
        free(dev);
    }
    return 0;
}

static int open_lights(const struct hw_module_t* module, const char* name, struct hw_device_t** device) {

    ALOGE("open_lights called. %s\n", name);

    int (*set_light)(struct light_device_t* dev, struct light_state_t const* state);

    if (strcmp(LIGHT_ID_BACKLIGHT, name) == 0) {

        set_light = set_light_backlight;

        // get max brightness value.
        int fd = open(BACKLIGHT_MAX_BRIGHTNESS, O_RDONLY);
        if (fd <= 0) {

            ALOGE("Could not open max backlight brightness file. %s\n", BACKLIGHT_MAX_BRIGHTNESS);
            return -EINVAL;
        }
        char buf[10];
        ssize_t result = read(fd, buf, sizeof(buf));
        if (result < 0) {

            ALOGE("Could not read max backlight brightness value.\n");
            return -EINVAL;
        }

        backlight_max_brightness = atoi(buf);
        close(fd);
    } else {

        return -ENODEV;
    }

    struct light_device_t *dev = malloc(sizeof(struct light_device_t));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = LIGHTS_DEVICE_API_VERSION_2_0;
    dev->common.module = (struct hw_module_t*)module;
    dev->common.close = (int (*)(struct hw_device_t*))close_lights;
    dev->set_light = set_light;

    *device = (struct hw_device_t*)dev;

    return 0;
}


static struct hw_module_methods_t lights_module_methods = {
    .open =  open_lights,
};

/*
 * The lights Module
 */
struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = LIGHTS_HARDWARE_MODULE_ID,
    .name = "lights module",
    .author = "mrtska",
    .methods = &lights_module_methods,
};
