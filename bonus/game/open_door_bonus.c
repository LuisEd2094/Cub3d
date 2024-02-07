
#include <cub3d_bonus.h>

int	open_door(t_prg *prg)
{
	double	map_x;
	double	map_y;

	prg->player.hit_box_angle = atan2(prg->camara_y, prg->camara_x);
	map_x = (double)(prg->player.x + (DOORS_PIXELS * \
			cos(prg->player.hit_box_angle)));
	map_y = (double)(prg->player.y + (DOORS_PIXELS * \
			sin(prg->player.hit_box_angle)));
	if ((int)map_y == (int)prg->player.y && (int)map_x == (int)prg->player.x)
		return (0);
	if (prg->map[(int)map_y][(int)map_x] == '2')
		prg->map[(int)map_y][(int)map_x] = '3';
	else if (prg->map[(int)map_y][(int)map_x] == '3')
		prg->map[(int)map_y][(int)map_x] = '2';
	update_window(prg);
	return (0);
}
