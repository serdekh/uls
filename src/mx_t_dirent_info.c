#include "../inc/uls.h"
#include "../inc/uls_error.h"

t_dirent_info *mx_dirent_info_new() {
    t_dirent_info *result = (t_dirent_info *)malloc(sizeof(t_dirent_info));
    return result;
}

bool mx_compare_two_detailed_infos(void *arg1, void *arg2) {
    return (
        mx_strcmp(
            ((t_dirent_info *)(arg1))->file_name, 
            ((t_dirent_info *)(arg2))->file_name
        ) > 0
    );
}

void mx_dirent_infos_sort(t_list *detailed_infos) {
    if (!detailed_infos) return;

    mx_sort_list(detailed_infos, mx_compare_two_detailed_infos);
}

void mx_set_date(
    
    #ifdef __APPLE__
        time_t *time, 
    #endif
    #ifdef __linux__
        t_timespec *time, 
    #endif

    t_dirent_info *info) {
    if (!time || !info) return;

    char *time_str = ctime(
        #ifdef __APPLE__
            time
        #endif
        #ifdef __linux__
            &time->tv_sec
        #endif
    );

    char **time_str_splitted = mx_strsplit(time_str, SPACE);

    int size = malloc_size(time_str_splitted) / sizeof(char **);

    info->month = mx_strnewncpy(time_str_splitted[1], 3);
    info->day = mx_strnewncpy(time_str_splitted[2], 2);
    info->time = mx_strnewncpy(time_str_splitted[3], 5);

    for (int i = 0; i < size; i++) {
        free(time_str_splitted[i]);
    }

    free(time_str_splitted);
}

void mx_set_permissions_string(t_dirent_info *info, mode_t file_mode) {
    if (!info) return;

    info->permissions_string[0] = (S_ISDIR(file_mode)) ? 'd' : '-';
    info->permissions_string[1] = (file_mode & S_IRUSR) ? 'r' : '-';
    info->permissions_string[2] = (file_mode & S_IWUSR) ? 'w' : '-';
    info->permissions_string[3] = (file_mode & S_IXUSR) ? 'x' : '-';
    info->permissions_string[4] = (file_mode & S_IRGRP) ? 'r' : '-';
    info->permissions_string[5] = (file_mode & S_IWGRP) ? 'w' : '-';
    info->permissions_string[6] = (file_mode & S_IXGRP) ? 'x' : '-';
    info->permissions_string[7] = (file_mode & S_IROTH) ? 'r' : '-';
    info->permissions_string[8] = (file_mode & S_IWOTH) ? 'w' : '-';
    info->permissions_string[9] = (file_mode & S_IXOTH) ? 'x' : '-';
    info->permissions_string[10] = '\0';
}

void mx_dirent_info_fill(char *filename, t_dirent_info *info) {
    if (!filename || !info) return;

    t_stat file_stat;

    if (lstat(filename, &file_stat) == -1) {
        mx_printerr("uls: ");
        mx_printerr(filename);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        exit(EXIT_FAILURE);
    }

    mx_set_permissions_string(info, file_stat.st_mode);

    info->owner_name = getpwuid(file_stat.st_uid)->pw_name;
    info->group_name = getgrgid(file_stat.st_gid)->gr_name;

    #ifdef __APPLE__
        time_t modification_time;
        modification_time = file_stat.st_mtime;
        mx_set_date(&modification_time, info);
    #endif
    #ifdef __linux__
        t_timespec modification_time;
        modification_time = file_stat.st_mtim;
        mx_set_date(&modification_time, info);
    #endif

    info->file_name  = mx_get_last_file_or_directory(filename);
    info->size       = (int)file_stat.st_size;
    info->hard_links = (int)file_stat.st_nlink;
    info->block_size = (int)file_stat.st_blocks;
}

int mx_get_max_digits_count(t_list *detailed_infos) {
    if (!detailed_infos) return -1;
    int max = 0;

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_dirent_info *temp = (t_dirent_info *)(i->data);

        int digits = mx_get_digits_count(temp->size);

        if (digits > max) max = digits;
    }

    return max;
}

void mx_dirent_info_print(t_dirent_info info, int spaces, int hard_link_spaces) {
    mx_printstrc(info.permissions_string, SPACE);
    mx_printchar(SPACE);

    spaces++;

    for (int i = 0; i < hard_link_spaces - 1; i++) { mx_printchar(SPACE); }

    mx_printint(info.hard_links);
    mx_printchar(SPACE);
    mx_printstrc(info.owner_name, SPACE);
    mx_printchar(SPACE);
    mx_printstrc(info.group_name, SPACE);

    for (int i = 0; i < spaces; i++) { mx_printchar(SPACE); }

    mx_printint(info.size);
    mx_printchar(SPACE);
    mx_printstrc(info.month, SPACE);

    if (mx_strlen(info.day) == 1) mx_printchar(SPACE);

    mx_printstrc(info.day, SPACE);
    mx_printstrc(info.time, SPACE);
    mx_printstrc(info.file_name, '\n');
}

void mx_dirent_info_free(t_dirent_info *info) {
    if (!info) return;

    free(info->file_name);
    free(info->month);
    free(info->day);
    free(info->time);
    free(info);
}

int mx_get_hard_links_max_digits_count(t_list *detailed_infos) {
    int hard_links_spaces = 0;

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_dirent_info *temp = (t_dirent_info *)(i->data);

        int hard_link_digits = mx_count_digits(temp->hard_links);

        if (hard_link_digits > hard_links_spaces) {
            hard_links_spaces = hard_link_digits;
        }
    }

    return hard_links_spaces;
}

void mx_dirent_infos_print(t_list *detailed_infos) {
    if (!detailed_infos) return;

    int max_digits_count = mx_get_max_digits_count(detailed_infos);
    int hard_links_spaces = mx_get_hard_links_max_digits_count(detailed_infos);

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_dirent_info *temp = (t_dirent_info *)(i->data);
        mx_dirent_info_print(*temp, max_digits_count - mx_get_digits_count(temp->size), hard_links_spaces);
    }
}

void mx_dirent_infos_print_from_folder(t_list *detailed_infos) {
    if (!detailed_infos) {
        return;
    }

    mx_print_total(detailed_infos);

    int max_digits_count = mx_get_max_digits_count(detailed_infos);
    int hard_links_spaces = mx_get_hard_links_max_digits_count(detailed_infos);

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_dirent_info *temp = (t_dirent_info *)(i->data);

        mx_dirent_info_print(*temp, max_digits_count - mx_get_digits_count(temp->size), hard_links_spaces);
    }
}

void mx_dirent_infos_free(t_list *detailed_infos) {
    if (!detailed_infos) return;

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        mx_dirent_info_free((t_dirent_info *)(i->data));
    }

    while (detailed_infos != NULL) {
        mx_pop_front(&detailed_infos);
    }
}

void mx_print_total(t_list *detailed_infos) {
    if (!detailed_infos) return;

    int total = 0;

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_dirent_info *temp = (t_dirent_info *)(i->data);
        total += temp->block_size;
    }

    mx_printstr("total ");
    #ifdef __APPLE__
    mx_printint(total);
    #endif
     #ifdef __linux__
    mx_printint(total / 2);
    #endif
    mx_printchar('\n');
}

t_list *mx_dirents_parse_to_dirent_infos(t_list *dirent_structurs) {
    if (!dirent_structurs) return NULL;

    t_list *detailed_infos = NULL;

    for (t_list *i = dirent_structurs; i != NULL; i = i->next) {
        t_dirent *temp = (t_dirent *)(i->data);

        t_dirent_info *info = mx_dirent_info_new();
        mx_dirent_info_fill(temp->d_name, info);
        mx_push_back(&detailed_infos, info);
    }

    return detailed_infos;
}
