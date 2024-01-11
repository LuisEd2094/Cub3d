#include <cub3d.h>

void    init_str_array(char **array, int size)
{
    int i;
    
    i = -1;
    while(++i <= size)
        array[i] = NULL;
}

void    init_prg(t_prg *prg)
{
    prg->north_img = 0;
    prg->south_img = 0;
    prg->west_img  = 0;
    prg->east_img = 0;
    init_int_array(prg->floor_vals, RGB_ARRAY);
    init_int_array(prg->ceiling_vals, RGB_ARRAY);
    init_int_array(prg->player_pos, 3);
    prg->error_msg = NULL;
    prg->map = NULL;
    errno = 0; 
}