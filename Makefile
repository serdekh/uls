make:
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic src/*.c inc/libmx/src/*.c -o uls