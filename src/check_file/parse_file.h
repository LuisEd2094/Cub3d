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
    bool    north;
    bool    south;
    bool    east;
    bool    west;
    bool    floor;
    bool    ceiling;
    bool    found_all;
    bool    error;
    char    *valid_identifier[ID_ARRAY_SIZE];
} t_parseer;


#endif