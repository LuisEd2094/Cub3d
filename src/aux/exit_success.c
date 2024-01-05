#include <cub3d.h>

void exit_success(t_prg *p)
{
    free_prg_mallocs(p);
    exit(EXIT_SUCCESS);
}