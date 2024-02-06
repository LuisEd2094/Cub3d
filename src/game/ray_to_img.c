/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:39:42 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:40:42 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_img	*get_img(t_prg *prg)
{
	if (prg->map[(int)prg->ray.ray_end_y][(int)prg->ray.ray_end_x] == '2')
		return (&(prg->door_img));
	if (!prg->ray.side)
	{
		if (prg->ray.ray_dir_x < 0)
			return (&(prg->east_img));
		else
			return (&(prg->west_img));
	}
	else 
	{
		if (prg->ray.ray_dir_y < 0)
			return (&(prg->south_img));
		else
			return (&(prg->north_img));
	}
}

int	get_color(t_ray *ray, t_img *img, int y)
{
	unsigned int	*wall_pixel;
	int				x;

	if (ray->side)
		x = ((int)(ray->ray_end_x * img->width) % img->width);
	else
		x = ((int)(ray->ray_end_y * img->width) % img->width);
	wall_pixel = (void *)img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)wall_pixel);
}

void	ray_to_img(t_prg *prg, int i)
{
	int				line_h;
	int				start;
	int				end;
	unsigned int	*pixel;
	t_img			*img;
	unsigned int	color; 

	line_h = (int)(H / prg->ray.wall_dist);
	start = -line_h / 2 + H / 2;
	if (start < 0)
		start = 0;
	end = line_h / 2 + H / 2;
	if (end >= H)
		end = H - 1;
	img = get_img(prg);
	float step = 1.0 * img->height / line_h;
	float y =  (start - H / 2 + line_h / 2) * step;	
	for (int j = 0; j < H; j++)
	{
		pixel = (void *)prg->img.addr + (j * prg->img.line_length + i * (prg->img.bpp / 8));

		if (j < start)
			*(unsigned int*)pixel = prg->ceiling_vals;
		else if (j < floor(end - step))
		{
			y += step;
			color = get_color(&(prg->ray), img, y);
				*(unsigned int*)pixel = color;
		}
		else
			*(unsigned int*)pixel = prg->floor_vals;
	}
}
