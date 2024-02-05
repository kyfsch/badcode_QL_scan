// This function is used to create a new object by parsing a string..
struct file *file_lookup(const char *name)
{
  struct file *f;

  for(f = file_table; f < file_table+NFILE; f++){
    if(f->f_inuse == 0 &&
       strncmp(name, f->f_name, DIRSIZ) == 0)
      return f;
  }
  return 0;
}

int
sys_open(void)
{
  char path[DIRSIZ], *path_ptr;
  struct inode *ip;
  struct file *f;
  int fd, omode;

  if(argstr(0, &path) < 0 || argint(1, &omode) < 0)
    return -1;
  
  begin_op();

  // Find the inode in the inode table.
  if(omode & O_CREATE) {
    // Create a new struct inode and file, and add it to the inode table.
    ip = create(path);
  }

  // Open an existing struct inode.
  else {
    if((ip = find_inode((char []){path})) == 0){
      end_op();
      return -1;
    }
  }

  // Check if the struct inode is a folder.
  if(ip->type == T_DIR && omode != O_RDONLY){
    end_op();
    cprintf("Cannot open not a directory file\n");
    return -1;
  }

  // Check if the struct inode is a not found.
  if(ip->type == T_DELETED){
    end_op();
    cprintf("Cannot open not a directory file\n");
    return -1;
  }

  // Check if a descriptor slot is available.
  if(ip->n_ref > 0 && (f = file_lookup(path)) == 0 ){
    end_op();
    cprintf("Cannot open because file is already in use\n");
    return -1;
  }

  

  if((omode & O_TRUNC