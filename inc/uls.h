#define _DEFAULT_SOURCE
#include <dirent.h>

#include <stdbool.h>

#define CURRENT_DIRECTORY "."
#define FLAG__HIDDEN_FILES_PRINTED "-a"

typedef struct dirent t_dirent;



int print_files_and_directories(bool hidden_are_printed);


/* My knowledge of how these functions work */

// write        (KNOW!)               - function that prints data into a descriptor
// malloc       (KNOW!)               - function to allocate dynamic memory
// free         (KNOW!)               - function to free dynamic memory;
// exit         (KNOW!)               - kills the process of a program and returns 1 or 0

// malloc_size  (DON'T KNOW!)         - ?
// strerror     (DON'T KNOW!)         - ?
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
