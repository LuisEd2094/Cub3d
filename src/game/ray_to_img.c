/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_img_normi                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:38:56 by apodader          #+#    #+#             */
/*   Updated: 2024/02/05 16:51:40 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_img	*get_img(t_prg *prg)
{
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
	wall_pixel = (void *)img->addr + \
	(y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)wall_pixel);
}

void	draw_texture(t_prg *prg, int i)
{
	int j;

	j = -1;
	while (++j  < H)
	{
		prg->pixel = (void *)prg->img.addr + \
		(j * prg->img.line_length + i * (prg->img.bpp / 8));
		if (j < prg->ray.start_p)
			*(unsigned int*)prg->pixel = prg->ceiling_vals;
		else if (j < floor(prg->ray.end_p - prg->ray.img_step))
		{
			prg->ray.y_img += prg->ray.img_step;
			prg->color = get_color(&(prg->ray), prg->texture, prg->ray.y_img);
			*(unsigned int*)prg->pixel = prg->color;
		}
		else
			*(unsigned int*)prg->pixel = prg->floor_vals;

	}
}

void	ray_to_img(t_prg *prg, int i)
{
	prg->ray.line_h = (int)(H / prg->ray.wall_dist);
	prg->ray.start_p = -prg->ray.line_h / 2 + H / 2;
	prg->ray.end_p = prg->ray.line_h / 2 + H / 2;
	if (prg->ray.start_p  < 0)
		prg->ray.start_p  = 0;
	if (prg->ray.end_p >= H)
		prg->ray.end_p = H - 1;
	prg->texture = get_img(prg);
	prg->ray.img_step = 1.0 * prg->texture->height / prg->ray.line_h;
	prg->ray.y_img = (prg->ray.start_p - H / 2 + prg->ray.line_h / 2) \
	* prg->ray.img_step;
	draw_texture(prg, i);
}
