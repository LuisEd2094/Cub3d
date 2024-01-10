#include <cub3d.h>

void free_mallocs(t_prg *p)
{
    free_2d_array((void **)p->map);
}