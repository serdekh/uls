#include "../inc/uls.h"
#include "../inc/utils.h"

int main(int argc, char *argv[]) {
    if (argc == 1 && isatty(STDOUT_FILENO) == 0) mx_call_uls_cat_e();
    if (argc == 1) mx_call_uls_without_params(CURRENT_DIRECTORY, true);
    if (argc >= 2) mx_call_uls_with_params(argc, argv);

    return 0;
}
