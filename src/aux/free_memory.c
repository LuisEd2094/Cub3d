#include <cub3d.h>


void free_memory(t_prg *prg)
{
    close_imgs_fd(prg);
	destroy_img(prg);
	free_mallocs(prg);
}