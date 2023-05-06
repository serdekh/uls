#include "../inc/uls.h"
#include "../inc/utils.h"
#include "../inc/uls_error.h"

void mx_check_l_flag(int argc, char **argv) {
    if (!argv || argc <= 0) return;

    if (mx_check_flag_l_position(argc, argv)) return;

    mx_dirents_print(argc, argv);

    exit(EXIT_SUCCESS);
}

void mx_handle_l_flag(t_list *dirents, int argc) {
    if (!dirents) return;

    t_list *files   = NULL;
    t_list *folders = NULL;

    bool files_were_printed = false;

    for (t_list *t = dirents; t != NULL; t = t->next) {
        t_dirent *temp = (t_dirent *)(t->data);

        if (temp->d_type == DT_DIR) {
            t_dirent *dirent = mx_dirent_new();
            mx_dirent_copy(dirent, temp);
            mx_push_back(&folders, dirent);
            continue;
        }

        t_dirent_info *info = mx_dirent_info_new();

        mx_dirent_info_fill(temp->d_name, info);
        mx_push_back(&files, info);
    }

    mx_dirent_infos_sort(files);

    files_were_printed = mx_dirent_infos_print(files);

    mx_dirent_infos_free(files);

    mx_dirents_sort(folders);

    int list_size = mx_list_size(dirents);

    if (files_were_printed && folders) mx_newline();

    for (t_list *i = folders; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        t_dirent_info *folder_info = mx_dirent_info_new();
        mx_dirent_info_fill(temp->d_name, folder_info);

        if (mx_doesnt_have_permissions(folder_info)) {
            mx_dirent_info_free(folder_info);
            
            if (argc > 3) { 
                mx_printstr(temp->d_name);
                mx_printstr(":\n");
            }

            mx_set_error_and_print(EACCES, temp->d_name, false, true);

           // else mx_set_error_and_print(EACCES, temp->d_name, false, false);
           
            if (i->next != NULL) mx_newline();
            continue;
        }

        mx_dirent_info_free(folder_info);


        t_list *folder_dirents = mx_dirents_get(temp->d_name);
        t_list *folder_dirents_info = NULL;

        for (t_list *j = folder_dirents; j != NULL; j = j->next) {
            t_dirent *folder_dirent = (t_dirent *)(j->data);
            t_dirent_info *info = mx_dirent_info_new();
            
            char *path = mx_add_strings(temp->d_name, folder_dirent->d_name);
      
            mx_dirent_info_fill(path, info);
            mx_push_back(&folder_dirents_info, info);
            free(path);
        }

        mx_dirent_infos_sort(folder_dirents_info);
  
        if (!folder_dirents_info && files) mx_printchar('\n');

        if (list_size != 1) {
            // if (mx_strcmp(temp->d_name, ((t_dirent *)folders->data)->d_name) != 0) {
            //     mx_printchar('\n');
            // }

            mx_printstr(temp->d_name);
            mx_printstr(":\n");   
        }

        mx_dirent_infos_print_from_folder(folder_dirents_info);
        mx_dirents_free(folder_dirents);
        mx_dirent_infos_free(folder_dirents_info);

        if (i->next != NULL) mx_newline();
    }

    mx_dirents_free(folders);
    mx_dirents_free(dirents);

    exit(EXIT_SUCCESS);
}
