#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include <cub3d.h>
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

void    init_parseer(t_parseer *parse);

bool    parse_for_ids(int fd, t_prg *prg, t_parseer *parse);
void    check_img_file(char **elemts, t_prg *p);
void    check_ceil_floor_vals(t_prg *p, char **elem, t_parseer *parse);

#endif