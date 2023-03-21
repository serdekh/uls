#include "../inc/libmx.h"

int mx_count_digits(int number) {
    int count = 0;
    int number_copy = number;

    while (number_copy != 0) {
        number_copy = number_copy / 10;
        count++;
    }

    return count;
}
