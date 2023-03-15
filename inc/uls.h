#define _DEFAULT_SOURCE
#include <dirent.h>

#include <errno.h>
#include <stdbool.h>

#include "../inc/libmx/inc/libmx.h"

#define CURRENT_DIRECTORY "."
#define FLAG__HIDDEN_FILES_PRINTED "-a"

typedef struct dirent t_dirent;

/**
 * @brief reads current directory and prints files/directories to stdout
 * @param hidden_are_printed if true, then hidden files will be printed
 * @return nothing but if opening file fails, program stops working and returns 1 by exit() function
*/
void print_files_and_directories(bool hidden_are_printed);

/**
 * @brief calls opendir() function from dirent.h but also checks if opening dir was successful.
 * If opening failed, then program stops working and returns 1. Otherwise, sets current directory
 * to the dir pointer
 * 
 * @param dir pointer which will be set with a {name} directory
 * @param name directory path which will be set to a {dir} struct
 * @return nothing but if opening file fails, program stops working and returns 1 by exit() function
*/
void try_opendir(DIR **dir, const char *name);

/* Functions note */

// write        (KNOW!)               - function that prints data into a descriptor
// malloc       (KNOW!)               - function to allocate dynamic memory
// free         (KNOW!)               - function to free dynamic memory;
// exit         (KNOW!)               - kills the process of a program and returns 1 or 0
// malloc_size  (KNOW!)               - returns size of an allocated memory
// strerror     (KNOW!)               - prints error from 'errno' variable

// opendir      (DON'T KNOW!)         - ?
// readdir      (DON'T KNOW!)         - ?
// closedir     (DON'T KNOW!)         - ?
// stat         (DON'T KNOW!)         - ?
// lstat        (DON'T KNOW!)         - ?
// getpwuid     (DON'T KNOW!)         - ?
// getgrgid     (DON'T KNOW!)         - ?
// listxattr    (DON'T KNOW!)         - ?
// getxattr     (DON'T KNOW!)         - ?
// readlink     (DON'T KNOW!)         - ?
// ioctl        (DON'T KNOW!)         - ?
// issaty       (DON'T KNOW!)         - ?
// acl_get_file (DON'T KNOW!)         - ?
// acl_to_text  (DON'T KNOW!)         - ?
// acl_free     (DON'T KNOW!)         - ?

// perror       (NOT COMPLETELY KNOW) - function to print error in stderr. Maybe works with errno?
// time         (NOT COMPLETELY KNOW) - function to calculate how long program works?
// ctime        (NOT COMPLETELY KNOW) - function to calculate how long program works? 
// errno        (NOT COMPLETELY KNOW) - saves error to a global variable?
