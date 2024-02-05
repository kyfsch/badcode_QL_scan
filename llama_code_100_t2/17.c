// This function is used to report napi stats in file format which are printed in.
static ssize_t read_file_napi_stats(struct file *file, char __user *user_buf, size_t count, loff_t *ppos)
{
    ssize_t show_count = 0;
    print_napi_stats();
    char *s = NULL;
    struct napi_info_data temp_napi_stats;

    s = get_stats_buffer(NAPI_BUF_SIZE);

    for (int index = 0; index < MAX_INTF_SUPPORTED; index++) {
        if (is_intf_present[index] && 0 == memcmp(iface_name[index], "wlan", 4)) {
            get_napi_info(&temp_napi_stats, iface_name[index], iface_idx[index]);
            snprintf(s + show_count, NAPI_BUF_SIZE,
                    "%d:txq:%d - rxq:%d : tx_napi : \t\t"
                    "%ju packets \t\t %ju bytes\n",
                    index, q_map.rx_q[index].index, q_map.tx_q[index].index,
                    temprxnapi_pkts[index], temprxnapi_bytes[index]);
            show_count += strlen(s + show_count);
            snprintf(s + show_count, NAPI_BUF_SIZE,
                    "txq:%d - tx_napi : \t\t %ju packets \t\t %ju bytes\n",
                    tx_q_map.index, temptxnapi_pkts[index], temptxnapi_bytes[index]);
            show_count += strlen(s + show_count);
        }
    }
    if(file->private_data != NULL)
        memcpy(file->private_data, (s+1), MAX_FILE_INFO_LEN);
    show_count = simple_read_from_buffer(user_buf, count, ppos, s, (strlen(s) + 1));
    if (s)
        vfree(s);

    return show_count;