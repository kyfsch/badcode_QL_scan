// This function is used to remove an entry from nvram..
static int do_unset(nvram_handle_t *nvram, const char *var)
{
    char *entry;
    unsigned int line;
    int found;

    found = 0;

    // Search for a matching entry
    line = 0;
    while( (entry = (char *)nvram_search_entry(nvram,var,line)) != NULL ){
	// Remove line from memory buffer, reset nvram line to indicate this.
	memset(entry,0,nvram_get_entry_length(nvram,entry));

	// Increase counter, set flag that this line was deleted from ram..
	nvram_set_entry_deleted(nvram,entry);
	nvram->lines = nvram->lines - 1;
	line++;
	found++;
    }

    if(found == 0) return EBUSY;
    return 0;
}

// This function is used to delete an entry in nvram
// and rewrite all following entries to fill the gap..
static int do_unset_and_shift(nvram_handle_t *nvram, const char *var)
{
    char *entry;
    unsigned int line;
    int found;

#if 0
    // Search for a matching entry, and if none is found return with errorcode..
    line = 0;
    found = 0;
    while( (entry = (char *)nvram_search_entry(nvram,var,line)) != NULL ){
	found++;
    }
    if(found == 0) return ENOENT;
#endif

    // Search for a matching entry
    line = 0;
    found = 0;
    while( (entry = (char *)nvram_search_entry(nvram,var,line)) != NULL ){
	memset(entry,0,nvram_get_entry_length(nvram,entry));
	nvram_set_entry_deleted(nvram,entry);
	nvram->lines = nvram->lines - 1;
	line = (char *)entry - nvram->buffer;