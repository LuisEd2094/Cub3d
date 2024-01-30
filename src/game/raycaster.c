/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:11:44 by apodader          #+#    #+#             */
/*   Updated: 2024/01/26 11:11:44 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void get_pixel_collision(t_prg *prg)
{
	if (prg->ray->side == 0) // If the ray hit a vertical wall
	{
		RAY_END_Y(prg) = (int)(( PLAYER_Y(prg) + prg->ray->wall_dist * prg->ray->ray_dir_y) * TILE_SIZE) ;
		RAY_END_X(prg) = (prg->ray->map_x) * TILE_SIZE; // I think you need to check the dirction for this
		if (prg->ray->ray_dir_x < 0)
			RAY_END_X(prg) += TILE_SIZE;
	}
	else // If the ray hit a horizontal wall
	{
		RAY_END_X(prg) = (int)((PLAYER_X(prg) + prg->ray->wall_dist * prg->ray->ray_dir_x) * TILE_SIZE);
		RAY_END_Y(prg) = (prg->ray->map_y) * TILE_SIZE;
		if (prg->ray->ray_dir_y < 0)
			RAY_END_Y(prg) += TILE_SIZE;
	}
}

void init_ray(t_prg *prg, int i)
{
	prg->ray->camera = 2 * i / (double)w - 1;
	prg->ray->ray_dir_x = prg->camara_x + prg->plane_x * prg->ray->camera;
	prg->ray->ray_dir_y = prg->camara_y + prg->plane_y * prg->ray->camera;
	prg->ray->map_x = (int)PLAYER_X(prg);
	prg->ray->map_y = (int)PLAYER_Y(prg);
	prg->ray->hit = 0;
	if (prg->ray->ray_dir_x == 0)
		prg->ray->delta_dist_x = FLT_MAX;
	else
		prg->ray->delta_dist_x = fabs(1 / prg->ray->ray_dir_x);
	if (prg->ray->ray_dir_y == 0)
		prg->ray->delta_disy_y = FLT_MAX;
	else
		prg->ray->delta_disy_y = fabs(1 / prg->ray->ray_dir_y);
}

#if BONUS_FLAG == 0
void	raycaster(t_prg *prg)
{
	int i;

	i = -1;
	while(++i < w)
	{
		init_ray(prg, i);
		init_dda(prg);
		perform_dda(prg);
		if (prg->ray->side == 0)
			prg->ray->wall_dist = prg->ray->side_dist_x - prg->ray->delta_dist_x;
		else
			prg->ray->wall_dist = prg->ray->side_dist_y - prg->ray->delta_disy_y;
		get_pixel_collision(prg);
		ray_to_img(prg, i);
	}
}
#else
void	raycaster(t_prg *prg)
{
	int i;
	
	i = -1;
	while (++i < w)
	{
		init_ray(prg, i);
		init_dda(prg);
		perform_dda(prg);
		if (prg->ray->side == 0)
			prg->ray->wall_dist = prg->ray->side_dist_x - prg->ray->delta_dist_x;
		else
			prg->ray->wall_dist = prg->ray->side_dist_y - prg->ray->delta_disy_y;
		get_pixel_collision(prg);
		ray_to_img(prg, i);
		//draw_ray(prg);
	}
}
#endif