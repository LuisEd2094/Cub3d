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
    bool    found_map;
    bool    found_new_line_btwn_maps;
    bool    found_player;
    char    valid_map_chars[8];
    char    *valid_identifier[ID_ARRAY_SIZE];
    char    *rgb_str[4];
    int     prev_len;
    int     next_len;
    int     list_size;
    char    *next_line;
    t_list  *list;
} t_parseer;

void    init_parseer(t_parseer *parse);

bool    parse_for_ids(int fd, t_prg *prg, t_parseer *parse);
void    check_img_file(char **elemts, t_prg *p);
void    check_ceil_floor_vals(t_prg *p, char **elem, t_parseer *parse);
void    check_elements(t_parseer *parse, char *line, t_prg *prg);
bool    parse_map(int fd, t_prg *prg, t_parseer *parse);
bool    get_map_to_list(int fd, t_prg *prg, t_parseer *parse, char *line);
bool    free_list(t_parseer *parse, bool return_val);
bool    valid_map_line(char * line, t_parseer *p);
bool    get_map_to_prg(t_prg *prg, t_parseer *parse);
bool    check_map_borders(t_prg *prg, t_parseer *parse);
#endif