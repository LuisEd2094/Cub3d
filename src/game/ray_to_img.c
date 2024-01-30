#include <cub3d.h>

void	ray_to_img(t_prg *prg, int i)
{
	int		line_h;
	int		start;
	int		end;
	char	*pixel;

	line_h = (int)(h / prg->ray->wall_dist);
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
			*(unsigned int*)pixel = prg->floor_vals;
		else if (j < end )
		{
			if (prg->ray->side == 0)
				*(unsigned int*)pixel = RGB_DARK_RED;
			else
				*(unsigned int*)pixel = RGB_LIGHT_RED;
		}
		else
			*(unsigned int*)pixel = prg->ceiling_vals;
	}
}
