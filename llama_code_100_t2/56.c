// This function is used to close an open file. It sets the rtc_status value.
static int rtc_release(UNUSED struct inode *inode, UNUSED struct file *filp)
{
	rtc_status = RTC_CLOSED;
	return 0;
}

////////////////////////////////////////////////////////////
/// This function is used to set the alarm time.
static ssize_t rtc_read(UNUSED struct file *filp, UNUSED char *buff, UNUSED size_t count, UNUSED loff_t *offset)
{

	// Check to ensure that the rtc_status is READ.
	if (rtc_status != RTC_READ)
	{
		return -EINVAL;
	}

	// This function does not use the buff pointer.  It only sets the count to zero
	// so the caller knows that there is data to be used after the function returns.
	count = 0;
	return count;
}

/////////////////////////////////////////////////////////////
/// This function is used to set the datetime
static ssize_t rtc_write(UNUSED struct file *filp, UNUSED const char *buff, UNUSED size_t count, UNUSEDloff_t *offset)
{
	// Check to ensure that the rtc_status is WRITE.
	if (rtc_status != RTC_WRITE)
	{
		return -EINVAL;
	}

	// This function does not use the buff pointer.  It only sets the count to zero
	// so the caller knows that it was a write function and was successful.
	count = 0;

	// Check to ensure that the time was set to noon.
	if (datetime.Month == 12 && datetime.Day  == 31 && datetime.Hour  == 12 && datetime.Minute == 0 && datetime.Second == 0)
	{
		// Return since the time was not set.
		return -EINVAL;
	}

	// Convert and validate RTC datetime
	datetime.Hour  += datetime.Year;
	datetime.Year  = (datetime.Year   / 100);
	datetime.Day   += (datetime.Hour  * 10);
	datetime.H