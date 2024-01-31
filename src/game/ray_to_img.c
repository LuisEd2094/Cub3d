#include <cub3d.h>

void	ray_to_img(t_prg *prg, int i)
{
	int		line_h;
	int		start;
	int		end;
	int 	*pixel;
	unsigned int 		*wall_pixel;
	int		color; 
	int		y;

	line_h = (int)(h / prg->ray->wall_dist);
	
	float step= 1.0 * prg->north_img->height / line_h;


	start = -line_h / 2 + h / 2;
	if (start < 0)
		start = 0;
	end = line_h / 2 + h / 2;
	if (end >= h)
		end = h - 1;
	int x = (RAY_END_X(prg) % TILE_SIZE);


	float textpos =  (start - h / 2 + line_h / 2) * step;
		// p->dda->textpos = (p->dda->drawstart - WIN_HEIGHT / 2
		// 	+ p->dda->lineheight / 2) * p->dda->step;
	//printf("%i\n", RAY_END_X(prg) % TILE_SIZE);// X POSITION on IMG
	for (int j = 0; j < h; j++)
	{

		textpos += step;

		wall_pixel = (void *)prg->north_img->addr + ((int)textpos * prg->north_img->line_length + x * (prg->north_img->bpp / 8));
		pixel = (void *)prg->img->addr + (j * prg->img->line_length + i * (prg->img->bpp / 8));
		color = *(unsigned int *)wall_pixel;
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
