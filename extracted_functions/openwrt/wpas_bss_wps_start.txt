wpas_bss_wps_start(struct ubus_context *ctx, struct ubus_object *obj,
			struct ubus_request_data *req, const char *method,
			struct blob_attr *msg)
{
	int rc;
	struct wpa_supplicant *wpa_s = get_wpas_from_object(obj);
	struct blob_attr *tb[__WPS_START_MAX], *cur;
	int multi_ap = 0;

	blobmsg_parse(wps_start_policy, __WPS_START_MAX, tb, blobmsg_data(msg), blobmsg_data_len(msg));

	if (tb[WPS_START_MULTI_AP])
		multi_ap = blobmsg_get_bool(tb[WPS_START_MULTI_AP]);

	rc = wpas_wps_start_pbc(wpa_s, NULL, 0, multi_ap);

	if (rc != 0)
		return UBUS_STATUS_NOT_SUPPORTED;

	return 0;
}
