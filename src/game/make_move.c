/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:37:35 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:39:14 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	make_move(t_prg *prg, int dir, int side)
{
	double	dx;
	double	dy;

	if (side == -1)
	{
		dx = (prg->camara_x * MOVE_SPEED * dir);
		dy = (prg->camara_y * MOVE_SPEED * dir);
	}
	else
	{
		dx = -prg->camara_y * MOVE_SPEED * dir;
		dy = prg->camara_x * MOVE_SPEED * dir;
	}
	prg->player.x += dx;
	prg->player.y += dy;
	if (prg->map[(int)(prg->player.y - dy)][(int)prg->player.x] == '1')
	{
		prg->player.x -= dx;
	}
	if (prg->map[(int)prg->player.y][(int)(prg->player.x - dx)] == '1')
	{
		prg->player.y -= dy;
	}
	update_window(prg);
	return (1);
}
