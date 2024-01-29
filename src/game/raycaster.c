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
		RAY_END_Y(prg) = (int)(( PLAYER_Y(prg) + prg->ray->wallDist * prg->ray->rayDirY) * TILE_SIZE) ;
		RAY_END_X(prg) = (prg->ray->mapX) * TILE_SIZE; // I think you need to check the dirction for this
		if (prg->ray->rayDirX < 0)
			RAY_END_X(prg) += TILE_SIZE;
	}
	else // If the ray hit a horizontal wall
	{
		RAY_END_X(prg) = (int)((PLAYER_X(prg) + prg->ray->wallDist * prg->ray->rayDirX) * TILE_SIZE);
		RAY_END_Y(prg) = (prg->ray->mapY) * TILE_SIZE;
		if (prg->ray->rayDirY < 0)
			RAY_END_Y(prg) += TILE_SIZE;
	}
}

void init_ray(t_prg *prg, int i)
{
	prg->ray->camera = 2 * i / (double)w - 1;
	prg->ray->rayDirX = prg->camara_x + prg->plane_x * prg->ray->camera;
	prg->ray->rayDirY = prg->camara_y + prg->plane_y * prg->ray->camera;
	prg->ray->mapX = (int)PLAYER_X(prg);
	prg->ray->mapY = (int)PLAYER_Y(prg);
	prg->ray->hit = 0;
	if (prg->ray->rayDirX == 0)
		prg->ray->deltaDistX = FLT_MAX;
	else
		prg->ray->deltaDistX = fabs(1 / prg->ray->rayDirX);
	if (prg->ray->rayDirY == 0)
		prg->ray->deltaDistY = FLT_MAX;
	else
		prg->ray->deltaDistY = fabs(1 / prg->ray->rayDirY);
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
			prg->ray->wallDist = prg->ray->sideDistX - prg->ray->deltaDistX;
		else
			prg->ray->wallDist = prg->ray->sideDistY - prg->ray->deltaDistY;
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
			prg->ray->wallDist = prg->ray->sideDistX - prg->ray->deltaDistX;
		else
			prg->ray->wallDist = prg->ray->sideDistY - prg->ray->deltaDistY;
		get_pixel_collision(prg);
		ray_to_img(prg, i);
		draw_ray(prg);
	}
}
#endif