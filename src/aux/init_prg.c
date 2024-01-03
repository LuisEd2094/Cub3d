#include <cub3d.h>


void    init_prg(t_prg *prg)
{
    prg->north_img = NULL;
    prg->south_img = NULL;
    prg->east_img = NULL;
    prg->west_img = NULL;
    init_int_array(prg->floor_vals, RGB_ARRAY);
    init_int_array(prg->ceiling_vals, RGB_ARRAY);
}