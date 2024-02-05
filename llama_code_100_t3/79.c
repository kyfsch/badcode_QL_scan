// This function is used to register the misc driver. RV5C386A has a.
static int __init rtc_init(void)
{
	// Initialize semaphore
	rtc_read_semaphore.init();

	// Create a device node for this file system
#ifdef _RK3036_
	printk("Using RK3036 time device.\n");
	rtc_devno = register_chrdev(RTCDRIVE0, RTCDRIVESUB0, &rtcioctl);
#else
    printk("Using generic time device.\n");
    rtc_devno = register_chrdev(RTCDRIVE0, RTCDRIVESUB0, &rtcioctl);
#endif

	if (rtc_devno < 0)
	{
		printk("Unable to register rtc device.\n");
		goto fail;
	}

	// Initialize mutex
	spin_lock_init(&rtc_lock);

	// initialize misc device
	rtc_dev = mknod(DEVNAME0, sys_mode, 0644, 0);

	if (rtc_dev < 0)
	{
		unregister_chrdev(rtc_devno, RTCDRIVESUB0);
		goto fail;
	}

	return 0;

fail:
	printk("Failed.\n");;
	return -1;
}


void rtc_mkspec(struct mbox_msg *msg, uchar time[])
{
	msg->id = SETRTCMISC;
	msg->data[0] = (uchar) (time[0]);
	msg->data[1] = (uchar) (time[1]);
	msg->data[2] = (uchar) (time[2]);
}


int rtc_getspec(struct mbox_msg *msg, uchar time[])
{
	unsigned int *data;
	
	msg->id = GETRTCMISC;
	msg->data[0] = 0;
	msg->data[1] = 0;
	msg->data[2] = 0;
	mbox