

#include <cub3d_bonus.h>

void	update_window(t_prg *prg)
{
	mlx_clear_window(prg->mlx.ptr, prg->mlx.window);
	draw_map(prg);
	raycaster(prg);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, \
			prg->img.img, 0, 0);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, \
			prg->mini_map.current_img->img, 0, 0);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, \
			prg->sprite[prg->i].img, W / 2 - 75, H - 193);
}