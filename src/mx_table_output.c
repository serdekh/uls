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

bool true_mul(int max_size, int max_d_len, t_dirent **dirents, int size, t_list *current) {
    int cols = max_size / (max_d_len);
    int rows = (size % cols) ? size / cols + 1 : size / cols;

    if (rows == 1) {
        for (int i = 0; i < size; i++) {
            mx_printstr(dirents[i]->d_name);

            if (i != size - 1) mx_printstr("  ");
        }

        if (current->next != NULL) mx_newline();

        return true;
    }

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
                if (rows == 1) {
                    mx_printstr("  "); 
                }
                else mx_printchar('\t');
            }

            add_tabs(max_d_len, kth_dirent_len);
        }
    }
    if (current->next != NULL) mx_newline();
    return false;
}

void multi_clm_print(t_dirent **dirents, int size, int max_size, int max_d_len, t_list *current) {
    if (max_d_len > max_size) {
        for (int i = 0; i < size; i++) {
            mx_replace_carriages(dirents[i]->d_name, '?');
            mx_printstr(dirents[i]->d_name);
            if (i < size - 1) mx_printchar('\n');
        }
    }
    else {
        if (true_mul(max_size, max_d_len, dirents, (int)size, current)) mx_newline();
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

void mx_print_table(t_dirent **dirents, size_t size, t_list *current) {
    int max_size = mx_get_winsize().ws_col;
    int max_d_len = max_d_namlen(dirents, size);

    multi_clm_print(dirents, (int)size, max_size, max_d_len, current);
}
