#include <cub3d.h>


void free_memory(t_prg *prg)
{
    close_imgs_fd(prg);
	destroy_img(prg);
	mlx_destroy_window(prg->mlx->ptr, prg->mlx->window);
	free_mallocs(prg);
}