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

void	raycaster(t_prg *prg)
{
	double	posX = PLAYER_X(prg), posY = PLAYER_Y(prg);		//
	double	dirX = prg->camara_x, dirY = prg->camara_y;		//	info del player
	double	planeX = 0.66, planeY = 0;	//

	int		mapX;		//
	int		mapY;		//
	double	camera;		//
	double	rayDirX;	//
	double	rayDirY;	//
	double	sideDistX;	//
	double	sideDistY;	//	info del rayo
	double	deltaDistX;	//
	double	deltaDistY;	//
	double	wallDist;	//
	int		stepX;		//
	int		stepY;		//
	int		hit;		//
	int		side;		//

	for (int i = 0; i < w; i++)
	{
		camera = 2 * i / (double)w - 1;
		rayDirX = dirX + planeX * camera;
		rayDirY = dirY + planeY * camera;
		mapX = (int)posX;
		mapY = (int)posY;
		hit = 0;
		if (rayDirX == 0)
			deltaDistX = FLT_MAX;
		else
			deltaDistX = fabs(1 / rayDirX);
		if (rayDirY == 0)
			deltaDistY = FLT_MAX;
		else
			deltaDistY = fabs(1 / rayDirY);
		//dda_init()
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//dda()
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (prg->map[mapY][mapX] == '1')
				hit = 1;
		}
		//
		if (side == 0)
			wallDist = sideDistX - deltaDistX;
		else
			wallDist = sideDistY - deltaDistY;
		prg->ray->wallDist = wallDist;
		ray_to_img(prg, i);
	}
}