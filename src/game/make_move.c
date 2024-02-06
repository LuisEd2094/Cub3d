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
	bool	can_move;

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
	PLAYER_X(prg) += dx;
	PLAYER_Y(prg) += dy;
	if (prg->map[(int)(PLAYER_Y(prg) - dy)][(int)PLAYER_X(prg)] == '1'
		|| prg->map[(int)(PLAYER_Y(prg) - dy)][(int)PLAYER_X(prg)] == '2')
	{
		PLAYER_X(prg) -= dx;
	}
	if (prg->map[(int)PLAYER_Y(prg)][(int)(PLAYER_X(prg) - dx)] == '1'
		|| prg->map[(int)PLAYER_Y(prg)][(int)(PLAYER_X(prg) - dx)] == '2')
	{
		PLAYER_Y(prg) -= dy;
	}
	update_window(prg);
	return (1);
}
