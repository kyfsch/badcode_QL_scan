// This function is used to update the BSS (Basic Service Set) configuration in the HostAPD module for the configured access point (AP). The function takes in three arguments: a file object, an index, and a Boolean value representing whether only files or the full configuration.
uc_hostapd_bss_set_config(uc_vm_t *vm, size_t nargs) {

	uc_hostapd_bss_t bs;
	char* name;
	uc_hostapd_bss_info *info;
	uc_value_t *o, *b;
	int fileid, rv;
	bool onlyfiles = false;
	uc_valstack_t *stk;

	CAST_OBJECT(stk, vm->stack, sizeof(uc_valstack_t));

	fileid = _hostapd_get_fileid(vm, stk);

	// If the access point is inactive, return an error to the caller.
	if (accesspoints[fileid].active == INACTIVE) {
		return throw_error(vm, UC_ERR_INVALID_ARG, "Access point is inactive");
	}

	// Pop the Boolean argument.
	b = uv_pop(stk);

	if (ucv_type(b) == UC_TYPE_BOOLEAN) {

		// Set whether only files or the complete BSS should be updated.
		onlyfiles = b->value.boolean;

	} else {

		return throw_error(vm, UC_ERR_INVALID_TYPE, "Argument is not boolean");
	}

	// Pop the information argument.
	o = uv_pop(stk);

	if (ucv_type(o) == UC_TYPE_OBJECT) {
		
		// Create a copy of the BSS information provided by the caller (a copy is required to pass it to the parser).
		info = object_to_hostapd_bss_info(o, stk, (char *)bss_default_info, &bs.filename, &bs.conf);

		// Create a new BSS (Basic Service Set) configuration.
		if ((info == NULL) || ((info->ssid == NULL) && !(onlyfiles))) {

			return throw_error(vm, UC_ERR_INVALID_TYPE, "Missing required BSS information");
		}

	}