#include <linux/fs.h> // for unregister_chrdev

#define MAJOR_NUM 100 // Assumed major number, replace with actual major number used

void unregister_device(void)
{
    unregister_chrdev(MAJOR_NUM, "device_name");
}


This function assumes that a device with the name "device_name" was previously registered with the major number 100. You will need to replace "device_name" and `MAJOR_NUM` with the appropriate device name and major number you used when registering the device.