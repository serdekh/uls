#include "../inc/uls.h"

t_list *mx_get_dirent_structures(const char *name) {
    if (!name) return NULL;

    DIR *dir = NULL;
    t_list *entries = NULL;
    t_dirent *entry = NULL;

    mx_try_opendir(&dir, name);

    while ((entry = readdir(dir)) != NULL) {
        t_dirent *list_element = (t_dirent *)malloc(sizeof(t_dirent));

        mx_direntcpy(list_element, entry);
        mx_push_back(&entries, list_element);
    }

    closedir(dir);

    return entries;
}
