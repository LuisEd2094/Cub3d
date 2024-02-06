#include <cub3d.h>


void free_memory(t_prg *prg)
{
	destroy_img(prg);
	free_2d_array((void **)prg->map);
	//free_mallocs(prg);
}