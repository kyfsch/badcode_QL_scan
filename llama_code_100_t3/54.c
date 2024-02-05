/// This function is used to read the JECED ID of the Flash device connected to SPI.</s> .
int spi_nor_read_id(void)
{
	u_char buf[5];
	int i;

	/*
	 * Setup the read for the JEDEC ID.
	 */
	out_8(&at91->spi_csr(0), AT91C_SPI_BR_FPDIV(2));
	out_8(&at91->spi_cr(0), AT91C_SPI_CPOL0 | AT91C_SPI_CPHA1 |
	     AT91C_SPI_MSTR);

	out_8(&at91->spi_txr(0), SPI_NOR_CMD_RD_JED);
	for (i = 0; i < 4; ++i) {
		buf[i] = in_8(&at91->spi_rxr(0));
	}

	out_8(&at91->spi_cr(0), 0);
	return *(u32 *)&buf[1];
}
</s>