#include "../inc/uls.h"
#include "../inc/utils.h"

char *mx_add_strings(char *str1, char *str2) {
    if (!str1 || !str2) return NULL;

    int str1len = strlen(str1);
    int str2len = strlen(str2);

    char *result = mx_strnew(str1len + str2len + 1);

    mx_strncpy(result, str1, str1len);
    result[str1len] = '/';
    mx_strncpy(&result[str1len + 1], str2, str2len);

    return result;
} 

char *mx_remove_last_directory_move(char *path) {
    char *result = NULL;

    if (!path) {
        result = mx_strnew(3);
        result[0] = '.';
        result[1] = '/';
        result[2] = '\0';

        return result;
    }

    int len = strlen(path);
    int cut_len = 0;

    for (int i = len - 1; i >= 0; i--) {
        if (path[i] == '/') {
            cut_len = i;
            break;
        }
    }

    if (cut_len == 0) {
        result = mx_strnew(3);
        result[0] = '.';
        result[1] = '/';
        result[2] = '\0';

        return result;
    }

    result = mx_strnewncpy(path, cut_len);

    return result;
}

char *mx_get_last_file_or_directory(char *path) {
    if (!path) return NULL;

    char *name = NULL;

    int slash_position = -1;
    int len = strlen(path);

    for (int i = len - 1; i >= 0; i--) {
        if (path[i] == '/') {
            slash_position = i;
            break;
        }
    }

    if (slash_position == -1) {
        name = mx_strnewncpy(path, len);
        return name;
    }

    name = mx_strnewncpy(&path[slash_position + 1], len - slash_position + 1);

    return name;
}

t_winsize mx_get_winsize() {
    struct winsize window_size;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);

    return window_size;
}
