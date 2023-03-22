#include "../inc/uls.h"
#include "../inc/uls_error.h"

bool mx_compare_two_detailed_infos(void *arg1, void *arg2) {
    return (
        mx_strcmp(
            ((t_detailed_information *)(arg1))->file_name, 
            ((t_detailed_information *)(arg2))->file_name
        ) > 0
    );
}

void mx_sort_detailed_infos(t_list *detailed_infos) {
    if (!detailed_infos) return;

    mx_sort_list(detailed_infos, mx_compare_two_detailed_infos);
}

void mx_set_date(t_timespec *time, t_detailed_information *info) {
    if (!time || !info) return;

    char *time_str = ctime(&time->tv_sec);
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

void mx_set_permissions_string(t_detailed_information *info, mode_t file_mode) {
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

void mx_set_detailed_info(char *filename, t_detailed_information *info) {
    if (!filename || !info) return;

    t_stat file_stat;

    if (lstat(filename, &file_stat) == -1) {
        perror(strerror(errno));
        exit(SUCCESS);
    }

    mx_set_permissions_string(info, file_stat.st_mode);

    info->owner_name = getpwuid(file_stat.st_uid)->pw_name;
    info->group_name = getgrgid(file_stat.st_gid)->gr_name;

    t_timespec modification_time = file_stat.st_mtim;

    mx_set_date(&modification_time, info);

    info->file_name  = mx_strnewncpy(filename, strlen(filename));
    info->size       = (int)file_stat.st_size;
    info->hard_links = (int)file_stat.st_nlink;
    info->block_size = (int)file_stat.st_blocks;
}

int mx_get_max_digits_count(t_list *detailed_infos) {
    if (!detailed_infos) return -1;
    int max = 0;

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_detailed_information *temp = (t_detailed_information *)(i->data);

        int digits = mx_get_digits_count(temp->size);

        if (digits > max) {
            max = digits;
        }
    }

    return max;
}

void mx_print_detailed_info(t_detailed_information info, int spaces) {
    mx_printstrc(info.permissions_string, SPACE);
    
    mx_printint(info.hard_links);
    mx_printchar(SPACE);

    mx_printstrc(info.owner_name, SPACE);
    mx_printstrc(info.group_name, SPACE);

    for (int i = 0; i < spaces; i++) { mx_printchar(SPACE); }

    mx_printint(info.size);
    mx_printchar(SPACE);
    mx_printstrc(info.month, SPACE);
    mx_printstrc(info.day, SPACE);
    mx_printstrc(info.time, SPACE);
    mx_printstrc(info.file_name, '\n');
}

void mx_free_detailed_info(t_detailed_information *info) {
    if (!info) return;

    free(info->file_name);
    free(info->month);
    free(info->day);
    free(info->time);
    free(info);
}

void mx_print_detailed_infos(t_list *detailed_infos) {
    if (!detailed_infos) return;

    int max_digits_count = mx_get_max_digits_count(detailed_infos);

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_detailed_information *temp = (t_detailed_information *)(i->data);
        mx_print_detailed_info(*temp, max_digits_count - mx_get_digits_count(temp->size));
    }
}

void mx_free_detailed_infos(t_list *detailed_infos) {
    if (!detailed_infos) return;

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        mx_free_detailed_info((t_detailed_information *)(i->data));
    }

    while (detailed_infos != NULL) {
        mx_pop_front(&detailed_infos);
    }
}

void mx_print_total(t_list *detailed_infos) {
    if (!detailed_infos) return;

    int total = 0;

    for (t_list *i = detailed_infos; i != NULL; i = i->next) {
        t_detailed_information *temp = (t_detailed_information *)(i->data);
        total += temp->block_size;
    }

    mx_printstr("total ");
    mx_printint(total / 2);
    mx_printchar('\n');
}
