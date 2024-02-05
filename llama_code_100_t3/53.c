// This function is used to parse the information included in a NAND.
mtdsplit_jimage_parse_generic(struct mtd_info *master,
			      struct nand_chip *nand, char *data,
			      size_t datalen, __be32 *off)
{
  struct {
    struct mtd_info _master;
    struct this_partition _dummy;
    struct kernel_param _p[3];
  } *p = (struct {
	      struct mtd_info _master;
	      struct this_partition _dummy;
	      struct kernel_param _p[3];
	    }*)data;
  struct nand_partitions *npart = master->priv;
  size_t size = master->erasesize;

  p->p[0].name = p->p[1].name = p->p[2].name = KERNEL_PARAM_OPTS_STRING;
  p->p[0].string = npart->types;
  p->p[1].string = npart->cmdline;
  p->p[2].string = npart->mtdids;

  while(size > datalen) {
    p->p[0].len = ((31 - __ilog2(size)) + 7) / 8;
    p->p[0].value = off[0];

    if(p->p[0].string) {
      data += p->p[0].len; datalen -= p->p[0].len;
      p->p[1].name = p->p[2].name = KERNEL_PARAM_OPTS_STRING;
      p->p[1].string = npart->types;
      p->p[2].string = npart->mtdids;
    }
    off++;
  }
}

__u32
// This is the actual function used to find the partition info structures.
mtdsplit_jimage_decode_string(int mtd_num, int part_num,
			      struct this_partition *part, char *image_data, int isroot)
{
    int i = 0;
    char *nand_info_start = image_data;
    int