#include "../inc/uls.h"
#include "../inc/libmx/inc/libmx.h"

bool mx_is_hidden_file(const char *file_name) {
    return (file_name[0] == '.');
}

int print_files_and_directories(bool hidden_are_printed) {
    DIR *dir = NULL;
    t_dirent *entry = NULL;

    dir = opendir(CURRENT_DIRECTORY);

    if (!dir) {
        /*
            FIXME: Implement the correct way of error hangling by errno
        */
        perror("Error: can't open current directory\n");

        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (hidden_are_printed) {
            mx_printstrc(entry->d_name, ' ');
        }

        if (!mx_is_hidden_file(entry->d_name) && !hidden_are_printed) {
            mx_printstrc(entry->d_name, ' ');
        }
    }

    closedir(dir);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return print_files_and_directories(false);
    }

    if (argc == 2) {
        if (mx_strcmp(argv[1], FLAG__HIDDEN_FILES_PRINTED) == 0) {
            print_files_and_directories(true);
        }
    }

    // if (argc < 3) {
    //     mx_printstr("usage: uls [-l] [file ...]\n");
    //     return 0;
    // }

    if (argv) {} // if statement to avoid the clang unused error

    return 0;
}
