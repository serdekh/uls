#include "../inc/libmx.h"

bool mx_is_hidden_file(const char *file_name) {
    return (file_name[0] == '.');
}
