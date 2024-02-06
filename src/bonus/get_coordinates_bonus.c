/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_coordinates_bonus.c							:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lsoto-do <lsoto-do@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/02/05 12:20:35 by lsoto-do		   #+#	  #+#			  */
/*	 Updated: 2024/02/05 12:22:08 by lsoto-do		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <cub3d.h>

int	get_coordinate(t_prg *prg, double (*f)(double), double rem, double value)
{
	return (((rem * TILE_SIZE) + ((MINI_MAP_SIZE) / 2) - TILE_SIZE) \
			+ ((TILE_SIZE / 2) \
			* f(prg->player.angle + (value * M_PI / 3.0))));
}

void	get_x_values(t_prg *prg)
{
	double	integer;

	if (prg->mini_map.off_set_x && \
			prg->player.x > (MAX_NUM_TILES / 2))
	{
		prg->mini_map.x_pos = floor(prg->player.x) - (MAX_NUM_TILES / 2);
		prg->mini_map.a.x = get_coordinate(prg, &cos, \
				modf(prg->player.x, &integer), 0);
		prg->mini_map.b.x = get_coordinate(prg, &cos, \
				modf(prg->player.x, &integer), 2.0);
		prg->mini_map.c.x = get_coordinate(prg, &cos, \
				modf(prg->player.x, &integer), 4.0);
	}
	else
	{
		prg->mini_map.a.x = ((prg->player.x * TILE_SIZE)) + \
		((TILE_SIZE / 2) * cos(prg->player.angle));
		prg->mini_map.b.x = ((prg->player.x * TILE_SIZE)) + \
		((TILE_SIZE / 2) * cos(prg->player.angle + (2.0 * M_PI / 3.0)));
		prg->mini_map.c.x = ((prg->player.x * TILE_SIZE)) + \
		((TILE_SIZE / 2) * cos(prg->player.angle + (4.0 * M_PI / 3.0)));
		prg->mini_map.x_pos = -1;
	}
}

int	get_map_y_position(t_prg *prg)
{
	if (prg->mini_map.off_set_y && \
			prg->player.y > (MAX_NUM_TILES / 2))
		return (floor(prg->player.y) - (MAX_NUM_TILES / 2));
	return (-1);
}

void	get_y_values(t_prg *prg)
{
	double	integer;

	if (prg->mini_map.off_set_y && \
			prg->player.y > (MAX_NUM_TILES / 2))
	{
		prg->mini_map.a.y = get_coordinate(prg, \
				&sin, modf(prg->player.y, &integer), 0);
		prg->mini_map.b.y = get_coordinate(prg, \
				&sin, modf(prg->player.y, &integer), 2.0);
		prg->mini_map.c.y = get_coordinate(prg, \
				&sin, modf(prg->player.y, &integer), 4.0);
	}
	else
	{
		prg->mini_map.a.y = ((prg->player.y * TILE_SIZE)) + \
		((TILE_SIZE / 2) * sin(prg->player.angle));
		prg->mini_map.b.y = ((prg->player.y * TILE_SIZE + 1)) + \
		((TILE_SIZE / 2) * sin(prg->player.angle + (2.0 * M_PI / 3.0)));
		prg->mini_map.c.y = ((prg->player.y * TILE_SIZE + 1)) + \
		((TILE_SIZE / 2) * sin(prg->player.angle + (4.0 * M_PI / 3.0)));
	}
}
