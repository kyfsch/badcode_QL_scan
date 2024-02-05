/// This function is used to remove an entry from nvram..
static int do_unset(nvram_handle_t *nvram, const char *var)
{
    int r;
    r = nvram_unset(nvram, var);
    return r;
    //return (r != ERROR_OK) ? -1 : 0;
}

// This function is used to show an entry from nvram..
static int do_get(nvram_handle_t *nvram, const char *var)
{
    int r;
    r = nvram_get_int(nvram, var, -1);
    nvram_free_entry(nvram);
    return r;
    //return (r != ERROR_OK) ? -1 : 0;
}

//This function is used to set an entry to nvram.
static int do_set(nvram_handle_t *nvram, const char *var, const char *val)
{
    int r;
    r = nvram_set_int(nvram, var, val);
    return r;
    //return (r != ERROR_OK) ? -1 : 0;
}

/*This function is used to do the following operation:
    - set an entry to nvram;
    - unset an entry from nvram;
    - show an entry from nvram;
    If the entry is not exists, it shows the error message.
*/
</s>