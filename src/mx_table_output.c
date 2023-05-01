#include "../inc/uls.h"
#include "../inc/utils.h"

void add_tabs(int max_size, int size) {
    if ((max_size - size) % 8 == 0) mx_printchar('\t');

    while ((max_size - size) > 8) {
        mx_printchar('\t');
        size += 8 - (size % 8);
    }
}

void mx_replace_carriages(char *str, char with) {
	if (!isatty(1)) return;

    for (int i = 0; i < mx_strlen(str); i++) {
        if (str[i] == '\b' || str[i] == '\r' || str[i] == '\t' || str[i] == '\v') {
            str[i] = with;
        }
    }
}

void true_mul(int max_size, int max_d_len, t_dirent **dirents, int size) {
    int cols = max_size / (max_d_len);
    int rows = (size % cols) ? size / cols + 1 : size / cols;

    for (int i = 0; i < rows; i++) {
        for (int k = i; k < size; k += rows) {
            mx_replace_carriages(dirents[i]->d_name, '?');
            mx_printstr(dirents[k]->d_name);

            if (!(--cols) || k + rows > size) {
                mx_printchar('\n');
                cols = max_size / (max_d_len);
                break;
            }

            int kth_dirent_len = mx_strlen(dirents[k]->d_name);

            if (kth_dirent_len % 8) {
               (rows == 1) ? mx_printstr("  ") : mx_printchar('\t');
            }

            add_tabs(max_d_len, kth_dirent_len);
        }
    }
}

void multi_clm_print(t_dirent **dirents, int size, int max_size, int max_d_len) {
    if (max_d_len > max_size) {
        for (int i = 0; i < size; i++) {
            mx_replace_carriages(dirents[i]->d_name, '?');
            mx_printstr(dirents[i]->d_name);
            mx_printchar('\n');
        }
    }
    else {
        true_mul(max_size, max_d_len, dirents, (int)size);
    }
}

int max_d_namlen(t_dirent **dirents, size_t size) {
    if (!dirents || size == 0) return -1;

    int max_len = 0;

    for (size_t i = 0; i < size; i++) {
        int temp_len = mx_strlen(dirents[i]->d_name);

        if (temp_len > max_len) {
            max_len = temp_len;
        }
    }

    if (max_len % 8) max_len += 8 - (max_len % 8);
    else max_len += 8;

    return max_len;
}

void mx_print_table(t_dirent **dirents, size_t size) {
    int max_size = mx_get_winsize().ws_col;
    int max_d_len = max_d_namlen(dirents, size);

    multi_clm_print(dirents, (int)size, max_size, max_d_len);
}
