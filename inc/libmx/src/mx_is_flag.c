#include "../inc/libmx.h"

bool mx_is_flag(const char *s) {
    if (!s) return false;

    return (s[0] == '-');
}
