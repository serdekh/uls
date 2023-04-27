#include "../inc/uls.h"
#include "../inc/uls_foreach.h"

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

t_dirent *mx_get_dirent_structure(char *name) {
    if (!name) return NULL;

    DIR *dir = NULL;
    t_dirent *entry = NULL;
    t_dirent *result = NULL;

    char *directory = mx_remove_last_directory_move(name);

    mx_try_opendir(&dir, directory);

    char *filename = mx_get_last_file_or_directory(name);

    free(directory);

    while ((entry = readdir(dir)) != NULL) {
        if (mx_strcmp(entry->d_name, filename) == 0) {
            result = (t_dirent *)malloc(sizeof(t_dirent));
            mx_strcpy(entry->d_name, name);
            mx_direntcpy(result, entry);
            free(filename);
            closedir(dir);
            return result;
        }
    }

    closedir(dir);
    free(filename);

    return NULL;
}

t_list *mx_get_dirent_structures(const char *name) {
    if (!name) return NULL;

    DIR *dir = NULL;
    t_dirent *entry = NULL;
    t_list *dirent_structures = NULL;

    mx_try_opendir(&dir, name);

    while ((entry = readdir(dir)) != NULL) {
        if (mx_is_hidden_file(entry->d_name)) continue;
        
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

void mx_print_files_and_directories(t_list *dirent_structures) {
    if (!dirent_structures) return;

    mx_foreach_t_dirent_and_iterator(dirent_structures, mx_foreach_print_dirent);
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

    mx_foreach_t_dirent(dirent_structures_list, mx_t_dirent_free);

    while (dirent_structures_list != NULL) {
        mx_pop_front(&dirent_structures_list);
    }
}

void mx_print_dirent_structures_in_folder(t_dirent *folder) {
    if (!folder) return;

    t_list *dirent_structures_in_folder = mx_get_dirent_structures(folder->d_name);

    mx_printstrc(folder->d_name, ':');

    if (!dirent_structures_in_folder) {
        mx_printstr("\t# empty directory\n");
        return;
    }

    mx_sort_dirent_structures(dirent_structures_in_folder);
    mx_printchar('\n');
    mx_foreach_t_dirent(dirent_structures_in_folder, mx_t_dirent_print_name_newline);
    mx_free_dirent_structures(dirent_structures_in_folder);
}

void mx_print_folders(t_list *dirent_structures) {
    if (!dirent_structures) return;

    mx_foreach_t_dirent(dirent_structures, mx_t_dirent_print_folder);
}

t_list *mx_get_dirent_structures_from_array(char **argv, int argc) {
    if (!argv || argc <= 0) return NULL;

    t_list *dirent_structures = NULL;

    for (int i = 1; i < argc; i++) {
        t_dirent *dirent = mx_get_dirent_structure(argv[i]);

        if (dirent != NULL) {
            mx_push_back(&dirent_structures, dirent);
        }
    }

    return dirent_structures;
}

void mx_print_files_from_dirent_structures(t_list *dirent_structures) {
    if (!dirent_structures) return;

    mx_foreach_t_dirent(dirent_structures, mx_t_dirent_print_name);
    mx_printchar('\n');
}

// FIXME: try to find the way how to print data inside a dir
void mx_print_dirents(int argc, char **argv) {
    if (!argv || argc <= 0) return;

    t_list *dirent_structures = mx_get_dirent_structures_from_array(argv, argc);

    mx_print_files_from_dirent_structures(dirent_structures);
    mx_print_folders(dirent_structures);
    mx_free_dirent_structures(dirent_structures);
}

