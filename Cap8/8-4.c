int fseek(FILE *f, long offset, int whence)
{
    if ((f->flag & _UNBUF) == 0 && base != NULL) {
        if (f->flag & _WRITE) {
            fflush(f);  // din 8-3.c
        } else if (f->flag & _READ) {
            f->cnt = 0;
            f->ptr = f->base;
        }
    }
    return (lseek(f->fd, offset, whence) < 0);
}