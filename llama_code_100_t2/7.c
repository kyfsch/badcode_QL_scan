/// This function is used to encode the structure of the SWITCH_LINK_SPEED to the corresponding NL messages.</s>.
swconfig_send_link(struct sk_buff *msg, struct genl_info *info, int attr, int flags);
.
#include <linux/err.h>
#include <linux/file.h>
#include <linux/list.h>
.
\#include "nl80211.h"
.
struct iw_handler_def swconfig_iw_handler_def = {
..
..
.
/*
	 * This ioctl function has already completed in the kernel.  The only
	 * reason we have any code here is so that we can have a nonzero
	 * return value if there is an error.
	 */

	return -ENODEV;
}
static int swconfig_nl_handle_request(struct sk_buff *msg, struct genl_info *info)
{
	struct file       *file;
	size_t             len;
	int                retval, status;
	char              *buf;

	len = info->attrs ? nla_len(info->attrs[0]) : 0;
	if (len < 0)
		return -EINVAL;
	
        if (!info->attrs || len == 0) {
                /* empty packet? */
                printk(KERN_ALERT "Empty request in the netlink message\n");
                return 0;
        }

	if (!(file = current->files))
		/*
		 * This ioctl function has already completed in the kernel,
		 * so we don't have to worry about failing to perform a sys_close().
		 */
		return -EINVAL;
	
	if (file->f_flags & O_NONBLOCK)
		return -EAGAIN;

	buf = kmalloc(len, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	if (copy_from_user(buf, nla_data(info->attrs[0]), len)) {
		retval = -EFAULT;
	} else {
		status=swconfig_send_link(skb_get(netdev_priv(dev)),info,n