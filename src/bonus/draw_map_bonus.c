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
	if (x == 0 || x == prg->mini_map.max_w - 1 || y == 0 || y == prg->mini_map.max_h - 1)
		return (0x000000);
	else if (x % (TILE_SIZE) == 0 || y % (TILE_SIZE) == 0)
		return (0xFFFFFF);
	if (prg->mini_map.y_pos < prg->map_h && prg->mini_map.x_pos < ft_strlen(prg->map[prg->mini_map.y_pos]))
	{
		if (prg->map[prg->mini_map.y_pos][prg->mini_map.x_pos] == '1')
			return (0xFF0000);
		else if (prg->map[prg->mini_map.y_pos][prg->mini_map.x_pos] == '2')
			return (0x00FF00);
		else if (prg->map[prg->mini_map.y_pos][prg->mini_map.x_pos] == '3')
			return (0x00008B);
		else if (calculate_if_inside_player(&(prg->mini_map), x, y))
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
	while (++x < prg->mini_map.max_w)
	{
		if (x % (TILE_SIZE) == 0)
			prg->mini_map.x_pos++;
		prg->mini_map.y_pos = get_map_y_position(prg);
		y = -1;
		while (++y < prg->mini_map.max_h)
		{
			if (y % (TILE_SIZE) == 0)
				prg->mini_map.y_pos++;
			prg->mini_map.pixel = (prg->mini_map.t_img.addr) + (y * prg->mini_map.t_img.line_length + x * (prg->mini_map.t_img.bpp / 8));
			*(unsigned int *)prg->mini_map.pixel = (get_pixel_color(prg, x, y) + (42 << 24));
		}
	}
}
