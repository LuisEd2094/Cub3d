/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 draw_map_bonus.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lsoto-do <lsoto-do@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/02/05 12:09:35 by lsoto-do		   #+#	  #+#			  */
/*	 Updated: 2024/02/05 12:17:08 by lsoto-do		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <cub3d.h>

void	set_mini_map_vals(t_prg *prg)
{
	get_x_values(prg);
	get_y_values(prg);
}

int	get_pixel_color(t_prg *prg, int x, int y)
{
	if (x == 0 || x == MAP_MAX_W(prg) - 1 || y == 0 || y == MAP_MAX_H(prg) - 1)
		return (0x000000);
	else if (x % (TILE_SIZE) == 0 || y % (TILE_SIZE) == 0)
		return (0xFFFFFF);
	if (MAP_Y(prg) < prg->map_h && MAP_X(prg) < ft_strlen(prg->map[MAP_Y(prg)]))
	{
		if (prg->map[MAP_Y(prg)][MAP_X(prg)] == '1')
			return (0xFF0000);
		else if (prg->map[MAP_Y(prg)][MAP_X(prg)] == '2')
			return (0x00FF00);
		else if (prg->map[MAP_Y(prg)][MAP_X(prg)] == '3')
			return (0x00008B);
		else if (calculate_if_inside_player(prg->mini_map, x, y))
			return (0xFFFF00);
		else
			return (0xededed);
	}
	else
		return (0xededed);
}

void	draw_map(t_prg *prg)
{
	int	x;
	int	y;

	set_mini_map_vals(prg);
	x = -1;
	while (++x < MAP_MAX_W(prg))
	{
		if (x % (TILE_SIZE) == 0)
			MAP_X(prg)++;
		MAP_Y(prg) = get_map_y_position(prg);
		y = -1;
		while (++y < MAP_MAX_H(prg))
		{
			if (y % (TILE_SIZE) == 0)
				MAP_Y(prg)++;
			MAP_PIXEL(prg) = MAP_GET_PIXEL(prg, x, y);
			*(unsigned int *)MAP_PIXEL(prg) = (get_pixel_color(prg, x, y));
		}
	}
}
