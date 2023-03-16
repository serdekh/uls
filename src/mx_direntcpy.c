#include "../inc/uls.h"

void mx_direntcpy(t_dirent *dest, t_dirent *src) {
    if (!dest || !src) return;
    
    dest->d_ino = src->d_ino;

    mx_strcpy(dest->d_name, src->d_name);

    dest->d_off = src->d_off;
    dest->d_reclen = src->d_reclen;
    dest->d_type = src->d_type;
}
