#include <cub3d.h>

int close_game(t_prg *prg)
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
int key_hook(int key, t_prg *prg)
{
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
		return (rotate_player(prg, -1, -prg->mouse_delta)); //800 / 360 = 2.222222
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
	mlx_hook(prg->mlx.window, 17, 0, close_game, (void *)prg);
	mlx_hook(prg->mlx.window, 6, 0, mouse_move, (void *)prg);
	mlx_hook(prg->mlx.window, 2, 0, key_hook, (void *)prg);
}

#endif
