#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include <stdbool.h>
# ifndef MAX_IDENTIFIERS
# define MAX_IDENTIFIERS 7
# endif

typedef struct s_parseer
{
    bool    north;
    bool    south;
    bool    east;
    bool    west;
    bool    floor;
    bool    ceiling;
    bool    found_all;
    bool    error;
    char    *valid_identifier[MAX_IDENTIFIERS];
} t_parseer;


#endif