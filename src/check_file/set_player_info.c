/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:58:39 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:58:45 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_player_pos_and_mini_map(t_prg *prg, int x, int y)
{
	prg->player.x = x + 0.5;
	prg->player.y = y + 0.5;
}

void	set_n_or_s(t_prg *prg, char c)
{
	prg->camara_x = 0;
	prg->plane_y = 0;
	if (c == 'N')
	{
		prg->camara_y = -1;
		prg->plane_x = 0.66;
	}
	else
	{
		prg->camara_y = 1;
		prg->plane_x = -0.66;
	}
}

void	set_e_or_w(t_prg *prg, char c)
{
	prg->camara_y = 0;
	prg->plane_x = 0;
	if (c == 'E')
	{
		prg->camara_x = 1;
		prg->plane_y = 0.66;
	}
	else
	{
		prg->camara_x = -1;
		prg->plane_y = -0.66;
	}
}

char	set_player_info(t_prg *prg, char c, int y, int x)
{
	if (c == 'N' || c == 'S')
		set_n_or_s(prg, c);
	else if (c == 'E' || c == 'W')
		set_e_or_w(prg, c);
	prg->player.angle = atan2(prg->camara_y, prg->camara_x);
	set_player_pos_and_mini_map(prg, x, y);
	return ('0');
}
