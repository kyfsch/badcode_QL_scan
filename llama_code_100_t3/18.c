// This function is used to set the age-out timer in seconds..
static ssize_t age_out_write(struct file *filp, const char __user *buffer,
			      size_t length, loff_t *off)
{
	u32 sec_timeout;
	int val;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (length != 4)
		return -EINVAL;

	if (copy_from_user(&sec_timeout, buffer, 4))
		return -EFAULT;

	val = sec_timeout;
	if (val == 0) {
		/*
		 * If no value is specified,
		 * disable the age-out timer.
		 */
		sec_timeout = 0;
	}
	/*
	 * Enforce a minimum value of 10 seconds.
	 * If user space requests less than this, set to the minimum value.
	 */
	if (val < 10)
		val = 10;

	sec_timeout = (u32) jiffies_to_msecs(val * HZ)/1000;
	gss_set_age_out(&authid, (unsigned long)sec_timeout);
	return 4;
}

// This function retrieves authentication information.

static ssize_t info_read(struct file *filp, char __user *buffer,
			 size_t length, loff_t *off)
{
	static uid_t euid;
	char buf[3072];
	u32 buflen;
	int i;
	struct cache_head *pos;
	struct gss_auth *entry;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (*off != 0)
		return 0;

	euid = rpl_geteuid();

	buflen = sprintf(buf,"NIS_DOMAIN_NAME:%s\n",
			 NIS_domain_name ? NIS_domain_name: "");

	// This is the list of credentials.