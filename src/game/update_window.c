#include <cub3d.h>


void	ray_to_img(t_prg *prg, int i)
{
	int		line_h;
	int		start;
	int		end;
	char	*pixel;

	line_h = (int)(h / prg->ray->wallDist);
	start = -line_h / 2 + h / 2;
	if (start < 0)
		start = 0;
	end = line_h / 2 + h / 2;
	if (end >= h)
		end = h - 1;
	for (int j = 0; j < h; j++)
	{
		pixel = prg->img->addr + (j * prg->img->line_length + i * (prg->img->bpp / 8));
		if (j < start)
			*(unsigned int*)pixel = RGB_BLUE;
		else if (j < end )
		{
			if (prg->ray->side == 0)
				*(unsigned int*)pixel = RGB_DARK_RED;
			else
				*(unsigned int*)pixel = RGB_LIGHT_RED;
		}
		else
			*(unsigned int*)pixel = RGB_GREY;
	}
}

#if BONUS_FLAG == 0

void update_window(t_prg *prg)
{
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  raycaster(prg);
  mlx_put_image_to_window(prg->mlx->ptr, prg->mlx->window, prg->img->img, 0, 0);

  //cast_ray(prg);
  //draw_ray(prg);
}
#else
void update_window(t_prg *prg)
{
  printf("%i\n", BONUS_FLAG);
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  raycaster(prg);
  mlx_put_image_to_window(prg->mlx->ptr, prg->mlx->window, prg->img->img, 0, 0);
  draw_map(prg);
  cast_ray(prg);
  draw_ray(prg);
}
#endif