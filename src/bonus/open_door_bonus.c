/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 open_door_bonus.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lsoto-do <lsoto-do@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/02/05 12:33:40 by lsoto-do		   #+#	  #+#			  */
/*	 Updated: 2024/02/05 12:34:05 by lsoto-do		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <cub3d.h>

int	open_door(t_prg *prg)
{
	double	map_x;
	double	map_y;

	prg->player.hit_box_angle = atan2(CAMARA_Y(prg), CAMARA_X(prg));
	map_x = (double)(prg->player.x + (DOORS_PIXELS * \
			cos(prg->player.hit_box_angle)));
	map_y = (double)(prg->player.y + (DOORS_PIXELS * \
			sin(prg->player.hit_box_angle)));
	if ((int)map_y == (int)prg->player.y && (int)map_x == (int)prg->player.x)
		return (0);
	if (MAP(prg)[(int)map_y][(int)map_x] == '2')
		MAP(prg)[(int)map_y][(int)map_x] = '3';
	else if (MAP(prg)[(int)map_y][(int)map_x] == '3')
		MAP(prg)[(int)map_y][(int)map_x] = '2';
	update_window(prg);
	return (0);
}
