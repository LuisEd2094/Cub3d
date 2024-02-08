/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_move_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:42:41 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:32:13 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	check_valid_move(t_prg *prg, double dx, double dy)
{
	prg->player.x += dx;
	prg->player.y += dy;
	if (prg->map[(int)(prg->player.y - dy)][(int)prg->player.x] == '1'
		|| prg->map[(int)(prg->player.y - dy)][(int)prg->player.x] == '2')
	{
		prg->player.x -= dx;
	}
	if (prg->map[(int)prg->player.y][(int)(prg->player.x - dx)] == '1'
		|| prg->map[(int)prg->player.y][(int)(prg->player.x - dx)] == '2')
	{
		prg->player.y -= dy;
	}
}

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
	check_valid_move(prg, dx, dy);
	update_window(prg);
	return (1);
}
