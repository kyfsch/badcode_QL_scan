#include <linux/fs.h> // for unregister_chrdev

// Assuming DEVICE_MAJOR was defined when you registered the device
// and DEVICE_NAME is a name you registered the device with
#define DEVICE_MAJOR 240
#define DEVICE_NAME "my_char_device"

void unregister_device(void) {
    unregister_chrdev(DEVICE_MAJOR, DEVICE_NAME);
}


If you were working with a platform device, it would look different:

c
#include <linux/platform_device.h> // for platform_device_unregister

// Assuming my_platform_device is a pointer to your platform device
extern struct platform_device *my_platform_device;

void unregister_platform_device(void) {
    platform_device_unregister(my_platform_device);
}


Please be aware that "my_platform_device" would have been defined elsewhere in your code (probably where you registered the platform device) and should not be declared `extern` without the actual declaration being present somewhere in your project.