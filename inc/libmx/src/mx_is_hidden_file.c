#include "../inc/libmx.h"

bool mx_is_hidden_file(const char *file_name) {
    if (!file_name) return false;

    int len = strlen(file_name);

    if (len == 1 && file_name[0] == '.') return true;
    if (len == 2 && file_name[0] == '.' && file_name[1] == '.') return true;
    if (len > 2 && file_name[0] == '.') return true;
    
    return false;
}
