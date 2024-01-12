static void write_file(const char *path, size_t len, bool pem, bool cert)
{
	mode_t mode = S_IRUSR | S_IWUSR;
	const char *buf_start = buf;
	int fd = STDERR_FILENO;
	ssize_t written;
	int err;

	if (!pem)
		buf_start += sizeof(buf) - len;

	if (!len) {
		fprintf(stderr, "No data to write\n");
		exit(1);
	}
	
	if (cert)
		mode |= S_IRGRP | S_IROTH;

	if (path)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);

	if (fd < 0) {
		fprintf(stderr, "error: I/O error\n");
		exit(1);
	}

	written = write(fd, buf_start, len);
	if (written != len) {
		fprintf(stderr, "writing key failed with: %s\n", strerror(errno));
		exit(1);
	}
	err = fsync(fd);
	if (err < 0) {
		fprintf(stderr, "syncing key failed with: %s\n", strerror(errno));
		exit(1);
	}
	if (path)
		close(fd);
}
