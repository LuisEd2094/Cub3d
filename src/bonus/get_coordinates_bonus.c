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
		MAP_X(prg) = floor(prg->player.x) - (MAX_NUM_TILES / 2);
		MAP_A_X(prg) = get_coordinate(prg, &cos, \
				modf(prg->player.x, &integer), 0);
		MAP_B_X(prg) = get_coordinate(prg, &cos, \
				modf(prg->player.x, &integer), 2.0);
		MAP_C_X(prg) = get_coordinate(prg, &cos, \
				modf(prg->player.x, &integer), 4.0);
	}
	else
	{
		MAP_A_X(prg) = ((prg->player.x * TILE_SIZE)) + \
		((TILE_SIZE / 2) * cos(prg->player.angle));
		MAP_B_X(prg) = ((prg->player.x * TILE_SIZE)) + \
		((TILE_SIZE / 2) * cos(prg->player.angle + (2.0 * M_PI / 3.0)));
		MAP_C_X(prg) = ((prg->player.x * TILE_SIZE)) + \
		((TILE_SIZE / 2) * cos(prg->player.angle + (4.0 * M_PI / 3.0)));
		MAP_X(prg) = -1;
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
		MAP_A_Y(prg) = get_coordinate(prg, \
				&sin, modf(prg->player.y, &integer), 0);
		MAP_B_Y(prg) = get_coordinate(prg, \
				&sin, modf(prg->player.y, &integer), 2.0);
		MAP_C_Y(prg) = get_coordinate(prg, \
				&sin, modf(prg->player.y, &integer), 4.0);
	}
	else
	{
		MAP_A_Y(prg) = ((prg->player.y * TILE_SIZE)) + \
		((TILE_SIZE / 2) * sin(prg->player.angle));
		MAP_B_Y(prg) = ((prg->player.y * TILE_SIZE + 1)) + \
		((TILE_SIZE / 2) * sin(prg->player.angle + (2.0 * M_PI / 3.0)));
		MAP_C_Y(prg) = ((prg->player.y * TILE_SIZE + 1)) + \
		((TILE_SIZE / 2) * sin(prg->player.angle + (4.0 * M_PI / 3.0)));
	}
}
