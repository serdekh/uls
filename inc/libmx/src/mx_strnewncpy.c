#include "../inc/libmx.h"

char *mx_strnewncpy(const char *src, int len) {
    char *str = mx_strnew(len);
    mx_strncpy(str, src, len);
    return str;
}
