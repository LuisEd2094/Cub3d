#include <cub3d.h>

void	init_dda(t_prg *prg)
{
	if (prg->ray->rayDirX < 0)
	{
		prg->ray->stepX = -1;
		prg->ray->sideDistX = (PLAYER_X(prg) - prg->ray->mapX) * prg->ray->deltaDistX;
	}
	else
	{
		prg->ray->stepX = 1;
		prg->ray->sideDistX = (prg->ray->mapX + 1.0 - PLAYER_X(prg)) * prg->ray->deltaDistX;
	}
	if (prg->ray->rayDirY < 0)
	{
		prg->ray->stepY = -1;
		prg->ray->sideDistY = (PLAYER_Y(prg) - prg->ray->mapY) * prg->ray->deltaDistY;
	}
	else
	{
		prg->ray->stepY = 1;
		prg->ray->sideDistY = (prg->ray->mapY + 1.0 - PLAYER_Y(prg)) * prg->ray->deltaDistY;
	}
}

void	perform_dda(t_prg *prg)
{
	while (prg->ray->hit == 0)
	{
		if (prg->ray->sideDistX < prg->ray->sideDistY)
		{
			prg->ray->sideDistX += prg->ray->deltaDistX;
			prg->ray->mapX += prg->ray->stepX;
			prg->ray->side = 0;
		}
		else
		{
			prg->ray->sideDistY += prg->ray->deltaDistY;
			prg->ray->mapY += prg->ray->stepY;
			prg->ray->side = 1;
		}
		if (prg->ray->mapY < 0.25
			|| prg->ray->mapX < 0.25
			|| prg->ray->mapY > prg->map_h - 0.25
			|| prg->ray->mapX > prg->map_w - 0.25)
			break ;
		if (prg->map[prg->ray->mapY][prg->ray->mapX] == '1')
			prg->ray->hit = 1;
	}
}