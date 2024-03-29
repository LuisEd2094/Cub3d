/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:36:16 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:59:34 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_game(t_prg *prg)
{
	exit_success(prg);
	return (0);
}

int	key_hook(int key, t_prg *prg)
{
	if (key == KEY_ESC || key == KEY_Q)
		close_game(prg);
	else if (key == KEY_W || key == KEY_UP)
		return (make_move(prg, 1, -1));
	else if (key == KEY_S || key == KEY_DOWN)
		return (make_move(prg, -1, -1));
	else if (key == KEY_A)
		return (make_move(prg, -1, 1));
	else if (key == KEY_D)
		return (make_move(prg, 1, 1));
	else if (key == KEY_LFT)
		return (rotate_player(prg, -1));
	else if (key == KEY_RGT)
		return (rotate_player(prg, 1));
	return (0);
}

#if LINUX_KEYS == 1

void	get_hooks(t_prg *prg)
{
	mlx_hook(prg->mlx.window, 17, 0, close_game, (void *)prg);
	mlx_key_hook(prg->mlx.window, key_hook, (void *)prg);
}

#else

void	get_hooks(t_prg *prg)
{
	mlx_hook(prg->mlx.window, 17, 0, close_game, (void *)prg);
	mlx_hook(prg->mlx.window, 2, 0, key_hook, (void *)prg);
}

#endif
