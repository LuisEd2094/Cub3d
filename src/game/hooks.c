/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:36:16 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:37:13 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_game(t_prg *prg)
{
	exit_success(prg);
	return (0);
}

#if BONUS_FLAG == 0

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
		return (rotate_player(prg, -1, 15));
	else if (key == KEY_RGT)
		return (rotate_player(prg, 1, 15));
	return (0);
}

void	get_hooks(t_prg *prg)
{
	mlx_hook(prg->mlx.window, 17, 0, close_game, (void *)prg);
	mlx_hook(prg->mlx.window, 2, 0, key_hook, (void *)prg);
}

#else

int	key_hook(int key, t_prg *prg)
{
	printf("%i\n", key);
	prg->i = 1;
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
	else if (key == KEY_E || key == KEY_SPACE)
		return (open_door(prg));
	else if (key == KEY_LFT)
	{
		prg->i = 0;
		return (rotate_player(prg, -1, 15));
	}
	else if (key == KEY_RGT)
	{
		prg->i = 2;
		return (rotate_player(prg, 1, 15));
	}
	return (0);
}

int	mouse_move(int x, int y, t_prg *prg)
{
	prg->mouse_delta = x - prg->prev_mouse;
	prg->prev_mouse = x;
	if (prg->mouse_delta < 0)
	{
		prg->i = 0;
		return (rotate_player(prg, -1, -prg->mouse_delta));
	}
	else if (prg->mouse_delta > 0)
	{
		prg->i = 2;
		return (rotate_player(prg, 1, prg->mouse_delta));
	}
	return (0);
}

void	get_hooks(t_prg *prg)
{
	printf("i am here %i\n", KEY_ESC);
	mlx_hook(prg->mlx.window, 17, 0, close_game, (void *)prg);
/* 	mlx_hook(prg->mlx.window, 6, 0, mouse_move, (void *)prg);
	mlx_hook(prg->mlx.window, 2, 0, key_hook, (void *)prg); */
	//mlx_mouse_hook(prg->mlx.window, mouse_move, (void *)prg);
	mlx_key_hook(prg->mlx.window, key_hook, (void *)prg);
}

#endif
