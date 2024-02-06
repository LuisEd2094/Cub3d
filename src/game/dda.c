#include <cub3d.h>

void	init_dda(t_prg *prg)
{
	if (prg->ray.ray_dir_x < 0)
	{
		prg->ray.step_x = -1;
		prg->ray.side_dist_x = (PLAYER_X(prg) - prg->ray.map_x) * prg->ray.delta_dist_x;
	}
	else
	{
		prg->ray.step_x = 1;
		prg->ray.side_dist_x = (prg->ray.map_x + 1.0 - PLAYER_X(prg)) * prg->ray.delta_dist_x;
	}
	if (prg->ray.ray_dir_y < 0)
	{
		prg->ray.step_y = -1;
		prg->ray.side_dist_y = (PLAYER_Y(prg) - prg->ray.map_y) * prg->ray.delta_disy_y;
	}
	else
	{
		prg->ray.step_y = 1;
		prg->ray.side_dist_y = (prg->ray.map_y + 1.0 - PLAYER_Y(prg)) * prg->ray.delta_disy_y;
	}
}


#if BONUS_FLAG == 0
void	perform_dda(t_prg *prg)
{
	while (prg->ray.hit == 0)
	{
		if (prg->ray.side_dist_x < prg->ray.side_dist_y)
		{
			prg->ray.side_dist_x += prg->ray.delta_dist_x;
			prg->ray.map_x += prg->ray.step_x;
			prg->ray.side = 0;
		}
		else
		{
			prg->ray.side_dist_y += prg->ray.delta_disy_y;
			prg->ray.map_y += prg->ray.step_y;
			prg->ray.side = 1;
		}
		if (prg->ray.map_y < 0.25
			|| prg->ray.map_x < 0.25
			|| prg->ray.map_y > prg->map_h - 0.25
			|| prg->ray.map_x > prg->map_w - 0.25)
			break ;
		if (prg->map[prg->ray.map_y][prg->ray.map_x] == '1')
			prg->ray.hit = 1;
	}
}

#else

void	perform_dda(t_prg *prg)
{
	while (prg->ray.hit == 0)
	{
		if (prg->ray.side_dist_x < prg->ray.side_dist_y)
		{
			prg->ray.side_dist_x += prg->ray.delta_dist_x;
			prg->ray.map_x += prg->ray.step_x;
			prg->ray.side = 0;
		}
		else
		{
			prg->ray.side_dist_y += prg->ray.delta_disy_y;
			prg->ray.map_y += prg->ray.step_y;
			prg->ray.side = 1;
		}
		if (prg->ray.map_y < 0.25
			|| prg->ray.map_x < 0.25
			|| prg->ray.map_y > prg->map_h - 0.25
			|| prg->ray.map_x > prg->map_w - 0.25)
			break ;
		if (prg->map[prg->ray.map_y][prg->ray.map_x] == '1'
			|| prg->map[prg->ray.map_y][prg->ray.map_x] == '2')
			prg->ray.hit = 1;
	}
}

#endif