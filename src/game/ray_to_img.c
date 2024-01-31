#include <cub3d.h>

void	ray_to_img(t_prg *prg, int i)
{
	int		line_h;
	int		start;
	int		end;
	char	*pixel;
	int		*wall_pixel;
	int		color; 
	int		y;

	y = -1;
	line_h = (int)(h / prg->ray->wall_dist);
	start = -line_h / 2 + h / 2;
	if (start < 0)
		start = 0;
	end = line_h / 2 + h / 2;
	if (end >= h)
		end = h - 1;
	int x = (RAY_END_X(prg) % TILE_SIZE);
	//printf("%i\n", RAY_END_X(prg) % TILE_SIZE);// X POSITION on IMG
	for (int j = 0; j < h; j++)
	{
		if (j % (line_h /prg->north_img->height) == 0)
			y++;
		//printf("%i\n", y);
		wall_pixel = (void *)prg->north_img->addr + (15 + 32 * (prg->north_img->bpp / 8));
		pixel = prg->img->addr + (j * prg->img->line_length + i * (prg->img->bpp / 8));
		color = *(int *)wall_pixel;
		if (j < start)
			*(unsigned int*)pixel = prg->floor_vals;
		else if (j < end )
		{
			if (prg->ray->side == 0)
				*(unsigned int*)pixel = RGB_DARK_RED;
			else
				*(unsigned int*)pixel = color;
		}
		else
			*(unsigned int*)pixel = prg->ceiling_vals;
	}
}
