/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:33:40 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/05 12:34:05 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	open_door(t_prg *prg)
{
	double	map_x;
	double	map_y;

	HIT_BOX_ANGLE(prg) = atan2(CAMARA_Y(prg), CAMARA_X(prg));
 	map_x = (double)(PLAYER_X(prg) + (DOORS_PIXELS* \
			cos(HIT_BOX_ANGLE(prg))));
	map_y = (double)(PLAYER_Y(prg) + (DOORS_PIXELS * \
			sin(HIT_BOX_ANGLE(prg))));
	if ((int)map_y == (int)PLAYER_Y(prg) && (int)map_x == (int)PLAYER_X(prg))
		return (0);
	if (MAP(prg)[(int)map_y][(int)map_x] == '2')
		MAP(prg)[(int)map_y][(int)map_x] = '3';
	else if (MAP(prg)[(int)map_y][(int)map_x] == '3')
		MAP(prg)[(int)map_y][(int)map_x] = '2';
	update_window(prg);
	return (0);
}
