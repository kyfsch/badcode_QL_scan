static int zyxel_bootconfig_write(struct zyxel_bootconfig *config, struct zyxel_bootconfig_mtd *mtd)
{
	struct erase_info_user erase_info;
	char img_status, img_active;
	char *args = NULL;
	int ret = 0;

	/* Allocate memory for reading boot-config partition */
	args = calloc(1, mtd->mtd_info.erasesize);
	if (!args) {
		fprintf(stderr, "Could not allocate memory!\n");
		ret = -1;
		goto out;
	}

	/* Read bootconfig partition */
	pread(mtd->fd, args, mtd->mtd_info.erasesize, 0);

	img_status = IMAGE_STATUS(config->image0_status, config->image1_status);
	img_active = ACTIVE_IMAGE(config->active_image);

	/* Check if bootconfig has to be written */
	if (args[BOOTCONFIG_IMAGE_STATUS] == img_status && args[BOOTCONFIG_ACTIVE_IMAGE] == img_active) {
		ret = 0;
		goto out;
	}

	/* Erase first block (containing the magic) */
	erase_info.start = 0;
	erase_info.length = mtd->mtd_info.erasesize;
	ret = ioctl(mtd->fd, MEMERASE, &erase_info);
	if (ret < 0) {
		fprintf(stderr, "Failed to erase block: %i\n", ret);
		goto out;
	}


	/* Write bootconfig */
	args[BOOTCONFIG_IMAGE_STATUS] = img_status;
	args[BOOTCONFIG_ACTIVE_IMAGE] = img_active;

	if (pwrite(mtd->fd, args, mtd->mtd_info.erasesize, 0) != mtd->mtd_info.erasesize) {
		fprintf(stderr, "Error writing bootconfig!\n");
		ret = -1;
		goto out;
	}

out:
	if (args)
		free(args);
	return ret;
}
