// This function is used to report napi stats in file format which are printed in.
static ssize_t read_file_napi_stats(struct file *file, char __user *user_buf,
                                    size_t count, loff_t *ppos)
{
    int status;
    char out_buffer[MAX_STATS_BUF];
    char out_buffer2[MAX_STATS_BUF];
    char *ptr;
    char *ptr2;
    ptr = out_buffer;
    ptr2 = out_buffer2;
    int size, size2;
    int i;
    /* Get napi stats from each queue */
    for (i = 0; i < max_napi_queues_len; i++) {
	if (napi_queue[i].is_valid) {
            status = 0;
            size = snprintf(ptr, MAX_STATS_BUF - 1, "\n");
            ptr += size;
            size2 = snprintf(ptr2, MAX_STATS_BUF - 1, "\n");
            ptr2 += size2;
	    status++;
            size = snprintf(ptr, MAX_STATS_BUF - 1, "Queue_%-2d",i);
            ptr += size;
            size2 = snprintf(ptr2, MAX_STATS_BUF - 1, "Queue_%-2d",i);
            ptr2 += size2;
            status++;
            size = snprintf(ptr, MAX_STATS_BUF - 1, "\n");
            ptr += size;
            size2 = snprintf(ptr2, MAX_STATS_BUF - 1, "\n");
            ptr2 += size2;
            status++;

            size = snprintf(ptr, MAX_STATS_BUF - 1, "    Total RX\n");
            ptr += size;
            size2 = snprintf(ptr2, MAX_STATS_BUF - 1, "    Total RX\n");
            ptr2 += size2;
            status++;

            size =  snprintf(ptr, MAX_STATS_BUF - 1, "    Bytes:      %-2d",
                        napi_queue[i].stats.rx_bytes);
            ptr +=