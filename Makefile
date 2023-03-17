make:
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic inc/libmx/src/*.c src/uls/*.c src/*.c -o uls