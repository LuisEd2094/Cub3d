/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:43:21 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:35:57 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	change_sprite(t_prg *prg, int dir)
{
	if (dir == -1)
		prg->i = 0;
	else
		prg->i = 2;
}

int	rotate_player(t_prg *prg, int dir, int angle)
{
	double	cam_x;
	double	plane_x;
	double	rads;

	change_sprite(prg, dir);
	rads = M_PI / 180.0 * angle * dir;
	cam_x = prg->camara_x;
	plane_x = prg->plane_x;
	prg->camara_x = cam_x * cos(rads) - prg->camara_y * sin(rads);
	prg->camara_y = cam_x * sin(rads) + prg->camara_y * cos(rads);
	prg->plane_x = plane_x * cos(rads) - prg->plane_y * sin(rads);
	prg->plane_y = plane_x * sin(rads) + prg->plane_y * cos(rads);
	prg->player.angle += rads;
	update_window(prg);
	return (0);
}
