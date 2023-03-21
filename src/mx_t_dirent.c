#include "../inc/uls.h"

t_list *mx_get_dirent_structures(const char *name) {
    if (!name) return NULL;

    DIR *dir = NULL;
    t_dirent *entry = NULL;
    t_list *dirent_structures = NULL;

    mx_try_opendir(&dir, name);

    while ((entry = readdir(dir)) != NULL) {
        t_dirent *list_element = (t_dirent *)malloc(sizeof(t_dirent));

        mx_direntcpy(list_element, entry);
        mx_push_back(&dirent_structures, list_element);
    }

    closedir(dir);

    return dirent_structures;
}

bool compare_dirent_name_fields(void *file1, void *file2) {
    return (
        mx_strcmp(
            ((t_dirent *)file1)->d_name, ((t_dirent *)file2)->d_name
        ) > 0
    );
}

void mx_sort_dirent_structures(t_list *dirent_structures) {
    if (!dirent_structures) return;
    
    mx_sort_list(dirent_structures, compare_dirent_name_fields);
}

void mx_print_files_and_directories(t_list *dirent_structures, bool hidden_are_printed) {
    if (!dirent_structures) return;

    for (t_list *i = dirent_structures; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        bool only_not_hidden_printed = !mx_is_hidden_file(temp->d_name) && !hidden_are_printed;

        if (hidden_are_printed || only_not_hidden_printed) {
            mx_printstr(temp->d_name);

            if (i->next != NULL) {
                mx_printstr("  ");
            }
        }
    }
}

void mx_direntcpy(t_dirent *dest, t_dirent *src) {
    if (!dest || !src) return;

    mx_strcpy(dest->d_name, src->d_name);

    dest->d_ino = src->d_ino;
    dest->d_off = src->d_off;
    dest->d_type = src->d_type;
    dest->d_reclen = src->d_reclen;
}

void mx_free_dirent_structures(t_list *dirent_structures_list) {
    if (!dirent_structures_list) return;

    for (t_list *i = dirent_structures_list; i != NULL; i = i->next) {
        free(i->data);
    }

    while (dirent_structures_list != NULL) {
        mx_pop_front(&dirent_structures_list);
    }
}
