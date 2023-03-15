#include "../inc/uls.h"

t_list *mx_get_dirent_structures(const char *name) {
    DIR *dir = NULL;
    t_list *entries = NULL;
    t_dirent *entry = NULL;

    mx_try_opendir(&dir, name);

    while ((entry = readdir(dir)) != NULL) {
        t_dirent *list_element = (t_dirent *)malloc(sizeof(t_dirent));

        list_element->d_ino = entry->d_ino;

        mx_strcpy(list_element->d_name, entry->d_name);

        list_element->d_off = entry->d_off;
        list_element->d_reclen = entry->d_reclen;
        list_element->d_type = entry->d_type;

        mx_push_back(&entries, list_element);
    }

    closedir(dir);

    return entries;
}
