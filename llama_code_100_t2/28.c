// This function is used to write data into flash..
mtk_bmt_write(struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
{
    nfl_addr_t dst_addr;
    unsigned long ofs;
    int page_left, write_size;

    // If OOB data is defined..
    if ((mtd->ecclayout->eccbytes > 0) &&
        (nand_bbm_flag == NAND_BAD_BLK_FLAG))
    {
        unsigned int i;
        int lastpage, lastpageofs;
        int oob_left;
        int retval;

        // get the last byte in this flash area..
        lastpage = to + len;
        lastpageofs = lastpage % (mtd->erasesize);

        // if this write does not cover the full page,
        // the write address needs to be adjusted accordingly
        dst_addr = to / mtd->erasesize * mtd->erasesize;

        // and the flash must be read with the proper offsets..

        // first read full pages..
        retval = mtk_nand_read(mtd, dst_addr, (mtd->erasesize + mtd->oobsize), retlen,
                               mainbuf);

        if (retval < 0)
        {
            NAND_AHB_ERR("[%s]: mtk_nand_read failed\n", __func__);
            printk("%s: mtk_nand_read error @ 0x%08x", __func__, dst_addr);
            return (int) retval;
        }
        printk("[%s] read data:\n", __func__);
        bmt_print_data("MAINBUF", mainbuf, mtd->writesize, mtd);

        // The last page needs to be special cased
        if (lastpageofs > 0)
        {
            oob_left = lastpageofs;
            memcpy(oobbuf, mainbuf, oob_left);

            dst_addr = to;
            retval = mtk_