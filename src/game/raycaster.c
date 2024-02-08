/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:11:44 by apodader          #+#    #+#             */
/*   Updated: 2024/02/08 11:26:21 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_pixel_collision(t_prg *prg)
{
	if (prg->ray.side == 0)
	{
		prg->ray.ray_end_y = (prg->player.y + prg->ray.wall_dist \
			* prg->ray.ray_dir_y);
		prg->ray.ray_end_x = (prg->ray.map_x);
	}
	else
	{
		prg->ray.ray_end_x = ((prg->player.x + prg->ray.wall_dist \
			* prg->ray.ray_dir_x));
		prg->ray.ray_end_y = (prg->ray.map_y);
	}
}

void	init_ray(t_prg *prg, int i)
{
	prg->ray.camera = 2 * i / (double)W - 1;
	prg->ray.ray_dir_x = prg->camara_x + prg->plane_x * prg->ray.camera;
	prg->ray.ray_dir_y = prg->camara_y + prg->plane_y * prg->ray.camera;
	prg->ray.map_x = (int)prg->player.x;
	prg->ray.map_y = (int)prg->player.y;
	prg->ray.hit = 0;
	if (prg->ray.ray_dir_x == 0)
		prg->ray.delta_dist_x = FLT_MAX;
	else
		prg->ray.delta_dist_x = fabs(1 / prg->ray.ray_dir_x);
	if (prg->ray.ray_dir_y == 0)
		prg->ray.delta_disy_y = FLT_MAX;
	else
		prg->ray.delta_disy_y = fabs(1 / prg->ray.ray_dir_y);
}

void	raycaster(t_prg *prg)
{
	int	i;

	i = -1;
	while (++i < W)
	{
		init_ray(prg, i);
		init_dda(prg);
		perform_dda(prg);
		if (prg->ray.side == 0)
			prg->ray.wall_dist = prg->ray.side_dist_x - prg->ray.delta_dist_x;
		else
			prg->ray.wall_dist = prg->ray.side_dist_y - prg->ray.delta_disy_y;
		get_pixel_collision(prg);
		ray_to_img(prg, i);
	}
}
