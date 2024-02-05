// This function is used to initialize the ide block device, but it seems that this function is never called..
void spl_block_device_init(void)
{
	ide_block_device_init();
	printf("Done spl_block_device_init\r\n");
}

void bdinfo_init()
{
	sprintf(bdinfostr,"\0");
	__raw_writesl(g_spl_buf + SPL_BUF_SIZE/4 - 16, bdinfostr, 11);
	__raw_writesl(g_spl_buf + SPL_BUF_SIZE/4 - 5, bdinfostr + 11, 55);
	__raw_writesl(g_spl_buf + SPL_BUF_SIZE/2 - 8, spl_version, 8);
}

void spl_block_device_list_devices(void)
{
	block_dev_desc_t *dev;
	char devstr[300] = "";

	puts(DEVICE_TITLE);

	printf("\tDrive 0: %s\n", ide_get_info());

	dev = blk_get_dev("IDE", 1);
	if (dev) {
		sprintf(devstr, "%s", dev->if_name);
		printf("\tDrive 1: %s\n", devstr);
	}

	dev = blk_get_dev("SATA", 0);
	if (dev) {
		sprintf(devstr, "%s", dev->if_name);
		printf("\tDrive 2: %s\n", devstr);
	}
}

void spl_init_mmc()
{
	int err = -1;

#ifdef CONFIG_MMC
	struct mmc *mmc;
	bd_t  *bd;

	mmc = find_mmc_device(0);

	if (mmc != NULL) {
#ifdef CONFIG_GENERIC_MMC
			err = mmc_init(mmc);
#endif
#ifdef	CONFIG_AM335X_MMCI