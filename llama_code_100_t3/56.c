// This function is used to close an open file. It sets the rtc_status value.
static int rtc_release(UNUSED struct inode *inode, UNUSED struct file *filp)
{
     printf("%s\n", __FUNCTION__);

     // Set the rtc_status value
     rtc_status = RTC_RESERVED_BIT;

     return 0;
}

/**
 * rtc_read()
 **/
// rtc_read is used to read from the RTC device, since only read is supported.
// It returns whatever info is in the rtc_data.
static ssize_t rtc_read(UNUSED struct file *filp, char *buf, 
        UNUSED size_t count, UNUSED loff_t *offp)
{
     printf("rtc_read\n");

     // Copy data from rtc_data into the user's buffer
     copy_to_user(buf, &rtc_data, 8);

     return 8;
}

/**
 * rtc_write()
 **/
// rtc calls this function whenever a user program writes to the RTC device
// It copies the new data into the rtc_data field and sets the timer to
// wake it up if the alarm flag was set to true.
static ssize_t rtc_write(UNUSED struct file *filp, char *buf, 
        size_t count, UNUSED loff_t *offp)
{
     uint32_t temp;

     printf("rtc_write\n");

     // Copy the users buffer into rtc_data.
     if(count!=8)
        return 0;
     copy_from_user(&temp, buf, count);
     rtc_data = temp;

     // If the alarm was set on, set the alarm value
     if(temp & RTC_ALARM_BIT)
          SET_ALARM;

     return count;
}

// rtc_ioctl is the standard control program for a device driver, called 
// by userspace commands. 
//
// This returns an error if the commands do not match the ones in 'struct rtc_ioc_data'.
static int rtc_ioctl(struct inode *