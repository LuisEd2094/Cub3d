#include <cub3d.h>

void free_prg_mallocs(t_prg *prg)
{
    if (prg->north_img)
        free(prg->north_img);
    if ( prg->south_img)
        free(prg->south_img);
    if (prg->west_img)
        free(prg->west_img);
    if (prg->east_img)
        free(prg->east_img);
}