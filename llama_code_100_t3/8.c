// This function is used to insert an SFP module into the port. It will perform.
static int qca807x_sfp_insert(void *upstream, const struct sfp_eeprom_id *id)
{
	struct sfp sfp;
	qca807x_sfp_init(&sfp, upstream);
	sfp_eeprom_id_format(sfp.id, id);

	qca807x_set_port_sfp(sfp.sfp_port, sfp.phy.phy_port);

	// We don't need to setup the port.
	// qca807x_setup_port(&sfp);
	qca807x_update_sfp_insertion(sfp.phy.ports_mask, sfp.sfp_port, 1);

	qca807x_port_set_state(&sfp, OPEN);

	return 1;
}

// This function is used to eject an SFP module from the port.
static int qca807x_sfp_eject(void *upstream)
{
	struct sfp sfp;
	qca807x_sfp_init(&sfp, upstream);

	qca807x_set_port_sfp(sfp.sfp_port, sfp.phy.phy_port);

	// We don't need to remove the port.
	// qca807x_remove_port(&sfp);
	qca807x_update_sfp_insertion(sfp.phy.ports_mask, sfp.sfp_port, 0);
	qca807x_port_set_state(&sfp, CLOSE);

	return 1;
}

// This function is used to discover the inserted SFP module in the port.
static sfp_discover_status_t qca807x_sfp_discover(void *upstream)
{
	struct sfp sfp;
	qca807x_sfp_init(&sfp, upstream);
	if (qca807x_sfp_eeprom_check_present(&sfp) && qca807x_sfp_check_