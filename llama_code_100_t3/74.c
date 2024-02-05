// This function is used to create a new object by parsing a string..
struct file *file_lookup(const char *name)
{
    struct file *f;

    for (f = file; f < file+NFILE; f++)
        if (f->f_count > 00 && f->f_type == D_FILE &&
            fcmp(f->f_name, name) == 0)
                return (f);
    return NULL;
}

struct file_system *file_system_create(const char *name)
{
    struct file *fd, *ff;
    struct file_system *f;

    if (fsys_count >= NSYS)
        return NULL;
    f = &fsys[fsys_count++];
    if ((fd = file_lookup(name)) != NULL) {
        f->f_dir = fd;
        f->f_flag = 1;
    }
    else
    f->f_dir = file_alloc();
    f->f_id = fsys_count;
    f->f_name = name;
    f->f_type = D_FILE_SYS;
    f->f_flag = 1;
    f->f_count = 0;
    f->f_pos = 0;
    for (ff = file; ff < file + NFILE; ff++)
        if (ff < file+NFILE) {
            ff->f_flag = 0;
            ff->f_pos = 0;
        }
    return f;
}

void file_free(struct file *f)
{
  struct file *ff, *ff1;
  struct inode *ip;

  if (f->f_type == D_INODE) {
    ip = fs[f->f_dev]->s_ip;
    printf("free inode %d, i_num %d\n", f, f->f_inum);
    //printf("---------------------\n");
    for (ff=ip->i_chain; ff<ip->i_chain+MAX_FSIZE;ff++)
    {
      //printf("File Name = %s , Inum = %d\n", ff->i_name, ff