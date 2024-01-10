#include <cub3d.h>

void exit_success(t_prg *p)
{
    close_imgs_fd(p);
    free_mallocs(p);
    exit(EXIT_SUCCESS);
}