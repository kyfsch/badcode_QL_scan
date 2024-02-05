// This function is used to get the value of mirror_tx. It.
ar8xxx_sw_get_mirror_tx_enable(struct switch_dev *dev,
		struct switch_port_mirror *mirr, int *enable)
{
	struct port_801x *port = (struct port_801x *)dev->priv;
	int i;

	*enable = 0;
	if (mirr->id > SWITCH_MIRROR_ID_MAX)
		return SWITCH_STATUS_INVAL;

	for (i = 0; i < SWITCH_MIRROR_PORT_MAX; i++) {
		if ((port->mirror_tx[i].id == mirr->id) &&
					switch_api_port_link_check(dev, i, NULL,
						SWITCH_FALSE, NULL, NULL)) {
			/* found */
			*enable = mirr->loc.port;
			break;
		}
	}

	return SWITCH_STATUS_SUCCESS;
}

static int ar8327_switch_port_mirror_replace(struct switch_dev *dev,
		const struct switch_port_mirror *mirr_old,
		const struct switch_port_mirror *mirr_new)
{
	int rv;
	struct port_801x *port = (struct port_801x *)dev->priv;

	if (mirr_old->id > SWITCH_MIRROR_ID_MAX ||
				mirr_new->id > SWITCH_MIRROR_ID_MAX) {
		return SWITCH_STATUS_INVAL;
	}

	if (mirr_old->loc.port != mirr_new->loc.port)
		return SWITCH_STATUS_UNSUPPORTED;

	rv = ar8xxx_sw_set_mirror_port_dest(dev, mirr_new->loc.port,
				mirr_new->id, AR8XXX_MIRROR_DIRECTION_TX);
	if (SWITCH_STATUS_SUCCESS != rv