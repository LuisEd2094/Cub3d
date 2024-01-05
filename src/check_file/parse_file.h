#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include <stdbool.h>
# ifndef ID_ARRAY_SIZE
#  define ID_ARRAY_SIZE 7
# endif

typedef struct s_parseer
{
    int     identifiers[ID_ARRAY_SIZE];
    int     ids_found;
    bool    found_all;
    char    *valid_identifier[ID_ARRAY_SIZE];
    char    *rgb_str[4];
} t_parseer;


#endif