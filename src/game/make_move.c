#include <cub3d.h>


#if BONUS_FLAG == 0

bool check_collision(t_prg *prg, t_point *center, t_point *left, t_point *right)
{
  if (MAP(prg)[center->y / TILE_SIZE][center->x / TILE_SIZE] == '1')
    return (0);
  return (1);
}

#else

bool check_collision(t_prg *prg, t_point *center, t_point *left, t_point *right)
{
  if (MAP(prg)[center->y / TILE_SIZE][center->x / TILE_SIZE] == '1')
    return (0);
  if (MAP(prg)[center->y / TILE_SIZE][center->x / TILE_SIZE] == '2')
    return (0);
  return (1);
}
#endif


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
