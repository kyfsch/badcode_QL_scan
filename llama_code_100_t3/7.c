/// This function is used to encode the structure of the SWITCH_LINK_SPEED to the corresponding NL messages.</s>.
swconfig_send_link(struct sk_buff *msg, struct genl_info *info, int attr,
                  void *data)
{
    struct ipaddrctl *c;
    struct nlattr *na;
    int plen;

    c = (struct ipaddrctl *)info->data;
    if (!c)
        return -EINVAL;

    plen = plen_for_msg(msg);

    na = nla_reserve(msg, attr, 1); // FIXME: size?
    if (!na)
        return -ENOMEM;
    nla_put_in_addr(info->attrs[attr], c->addr);

    info->userhdr = info->attrs[attr];
    info->attrs[attr] = NULL;
    info->attrs_len = 0;  // FIXME:
    info->attrs[attr] = na;

    return swconfig_sendmsg(msg, info, plen, 0);
}

static struct genl_ops swconfig_genl_ops[] = {
    {
        .o_cmd = SWITCH_CMD_GET,
        .o_doit = swconfig_get
    },
    {
        // send command
        .o_cmd = SWITCH_CMD_GETCMD,
        .o_doit = swconfig_sendcmd
    },
    {
        .o_cmd = SWITCH_CMD_SET,
        .o_doit = swconfig_set
    },
    {
        .o_cmd = SWITCH_CMD_GETMAC,
        .o_doit = swconfig_getMac
    },
    {
        .o_cmd = SWITCH_CMD_GETLINK,
        .o_doit = swconfig_getLink
    },
    {
        // send config
        .o_cmd = SWITCH_CMD_GETALLCMD,
        .o_doit = swconfig_sendCmdAll
    },
    {
        // send all info
        .o_cmd = SWITCH_CMD_GETALLINFO,
        .o_doit =