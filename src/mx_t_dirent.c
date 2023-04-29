#include "../inc/uls.h"
#include "../inc/utils.h"
#include "../inc/uls_error.h"
#include "../inc/uls_foreach.h"

t_dirent *mx_dirent_get(char *name) {
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
            mx_dirent_copy(result, entry);

            free(filename);
            closedir(dir);

            return result;
        }
    }

    closedir(dir);
    free(filename);

    return NULL;
}

t_list *mx_dirents_get(const char *name) {
    if (!name) return NULL;

    DIR *dir = NULL;
    t_dirent *entry = NULL;
    t_list *dirent_structures = NULL;

    mx_try_opendir(&dir, name);

    while ((entry = readdir(dir)) != NULL) {
        if (mx_is_hidden_file(entry->d_name)) continue;
        
        t_dirent *list_element = (t_dirent *)malloc(sizeof(t_dirent));

        mx_dirent_copy(list_element, entry);
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

void mx_dirents_sort(t_list *dirent_structures) {
    if (!dirent_structures) return;
    
    mx_sort_list(dirent_structures, compare_dirent_name_fields);
}

void mx_dirents_print_both(t_list *dirent_structures) {
    if (!dirent_structures) return;

    mx_foreach_t_dirent_and_iterator(dirent_structures, mx_foreach_print_dirent);
}

void mx_dirent_copy(t_dirent *dest, t_dirent *src) {
    if (!dest || !src) return;

    mx_strcpy(dest->d_name, src->d_name);

    dest->d_ino = src->d_ino;
    dest->d_off = src->d_off;
    dest->d_type = src->d_type;
    dest->d_reclen = src->d_reclen;
}

void mx_dirents_free(t_list *dirent_structures_list) {
    if (!dirent_structures_list) return;

    mx_foreach_t_dirent(dirent_structures_list, mx_t_dirent_free);

    while (dirent_structures_list != NULL) {
        mx_pop_front(&dirent_structures_list);
    }
}

void mx_dirents_print_from_folder(t_dirent *folder) {
    if (!folder) return;

    t_list *dirent_structures_in_folder = mx_dirents_get(folder->d_name);

    mx_printstrc(folder->d_name, ':');

    if (!dirent_structures_in_folder) {
        mx_printstr("\t# empty directory\n");
        return;
    }

    mx_dirents_sort(dirent_structures_in_folder);
    mx_printchar('\n');
    mx_foreach_t_dirent(dirent_structures_in_folder, mx_t_dirent_print_name_newline);
    mx_dirents_free(dirent_structures_in_folder);
}

void mx_dirents_print_folders(t_list *dirent_structures) {
    if (!dirent_structures) return;

    mx_foreach_t_dirent(dirent_structures, mx_t_dirent_print_folder);
}

t_list *mx_dirents_get_from_main_input(char **argv, int argc) {
    if (!argv || argc <= 0) return NULL;

    t_list *dirent_structures = NULL;

    for (int i = 1; i < argc; i++) {
        t_dirent *dirent = mx_dirent_get(argv[i]);

        if (dirent == NULL) {
            mx_print_no_such_file_or_directory(argv[i]);
            mx_dirents_free(dirent_structures);
            exit(EXIT_FAILURE);
        }

        mx_push_back(&dirent_structures, dirent);
    }

    return dirent_structures;
}

void mx_dirents_print_of_type(t_list *dirents, unsigned char type_printed) {
    for (t_list *i = dirents; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        if (mx_is_hidden_file(temp->d_name) || temp->d_type != type_printed) continue;

        mx_printstr(temp->d_name);
        
        if (isatty(STDOUT_FILENO) != 0) {
            if (i->next != NULL) {
                mx_printchar(SPACE);    
                mx_printchar(SPACE);
            }
        }
        else {
            mx_printchar('\n');
        }
    }
}

//FIXME: change foreach function so it doesn't print a char in the end
void mx_dirents_print_files(t_list *dirent_structures) {
    if (!dirent_structures) return;
    mx_dirents_print_of_type(dirent_structures, DT_REG);
}

void mx_dirents_print(int argc, char **argv) {
    if (!argv || argc <= 0) return;

    t_list *dirent_structures = mx_dirents_get_from_main_input(argv, argc);

    mx_dirents_sort(dirent_structures);
    mx_dirents_print_files(dirent_structures);
    mx_dirents_print_folders(dirent_structures);
    mx_dirents_free(dirent_structures);
}

