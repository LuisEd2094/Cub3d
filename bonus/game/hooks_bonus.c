/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:42:21 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 12:40:43 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	close_game(t_prg *prg)
{
	exit_success(prg);
	return (0);
}

int	key_hook(int key, t_prg *prg)
{
	prg->i = 1;
	if (key == KEY_ESC || key == KEY_Q)
		close_game(prg);
	else if (key == TAB)
		return (change_map(prg));
	else if (key == KEY_W || key == KEY_UP)
		return (make_move(prg, 1, -1));
	else if (key == KEY_S || key == KEY_DOWN)
		return (make_move(prg, -1, -1));
	else if (key == KEY_A)
		return (make_move(prg, -1, 1));
	else if (key == KEY_D)
		return (make_move(prg, 1, 1));
	else if (key == KEY_E || key == KEY_SPACE)
		return (open_door(prg));
	else if (key == KEY_LFT)
		return (rotate_player(prg, -1, 15));
	else if (key == KEY_RGT)
		return (rotate_player(prg, 1, 15));
	return (0);
}

int	mouse_move(int x, int y, t_prg *prg)
{
	(void)y;
	prg->mouse_delta = x - prg->prev_mouse;
	prg->prev_mouse = x;
	if (prg->mouse_delta < 0)
		return (rotate_player(prg, -1, -prg->mouse_delta));
	else if (prg->mouse_delta > 0)
		return (rotate_player(prg, 1, prg->mouse_delta));
	return (0);
}

/*We need key hook for linux and hook for mac, specialy 
 * if we want to the keys to be repeatable*/

#if LINUX_KEYS == 1

void	get_hooks(t_prg *prg)
{
	mlx_hook(prg->mlx.window, 17, 0, close_game, (void *)prg);
	mlx_key_hook(prg->mlx.window, key_hook, (void *)prg);
	mlx_hook(prg->mlx.window, 6, 0, mouse_move, prg);
}

#else

void	get_hooks(t_prg *prg)
{
	mlx_hook(prg->mlx.window, 17, 0, close_game, prg);
	mlx_hook(prg->mlx.window, 6, 0, mouse_move, prg);
	mlx_hook(prg->mlx.window, 2, 0, key_hook, prg);
}

#endif
