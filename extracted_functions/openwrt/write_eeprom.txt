static int write_eeprom(struct data_header **data_table, int cnt)
{
	int ret = EXIT_FAILURE;

	for (int i = 0; i < cnt; i++) {
		if (data_table[i]->type == DATA_HEADER_EEPROM
		    && data_table[i]->id == DATA_HEADER_ID_CAL) {
			ret =
			    write_file(ofname, data_table[i]->data,
				       data_table[i]->length);
			break;
		}

	}

	return ret;
}
