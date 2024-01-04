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
    init_str_array(prg->imgs, 5);
    init_int_array(prg->floor_vals, RGB_ARRAY);
    init_int_array(prg->ceiling_vals, RGB_ARRAY);
    prg->error_msg = NULL;
    errno = 0; 
}