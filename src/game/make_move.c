#include <cub3d.h>

bool check_collision(t_prg *prg, t_point *center, t_point *left, t_point *right)
{
  if (MAP(prg)[center->y / TILE_SIZE][center->x / TILE_SIZE] == '1')
    return (0);
  if (MAP(prg)[center->y / TILE_SIZE][center->x / TILE_SIZE] == '2')
    return (0);
  /* if (MAP(prg)[left->y / TILE_SIZE][left->x / TILE_SIZE] == '1')
    return (0);
  if (MAP(prg)[right->y / TILE_SIZE][right->x / TILE_SIZE] == '1')
    return (0);

  if (MAP(prg)[left->y / TILE_SIZE][left->x / TILE_SIZE] == '2')
    return (0);
  if (MAP(prg)[right->y / TILE_SIZE][right->x / TILE_SIZE] == '2')
    return (0); */
  return (1);
}

void get_hit_box_values(t_prg *prg, double dx, double dy)
{

  HIT_BOX_ANGLE(prg) = atan2(dy,dx);
  printf("MOVE_PIXELS %f  negatice %f positive %f dx %f dy %f\n", MOVE_PIXELS, HIT_BOX_ANGLE(prg) * -1, HIT_BOX_ANGLE(prg), MOVE_PIXELS * cos(HIT_BOX_ANGLE(prg)),  MOVE_PIXELS * sin(HIT_BOX_ANGLE(prg)));
  HIT_BOX_CENTER(prg)->x = PLAYER_CENTER_X(prg) + ((int)(MOVE_PIXELS * cos(HIT_BOX_ANGLE(prg))));// * cos(HIT_BOX_ANGLE(prg));
  HIT_BOX_CENTER(prg)->y = PLAYER_CENTER_Y(prg) + ((int)(MOVE_PIXELS * sin(HIT_BOX_ANGLE(prg))));// * sin
/*   HIT_BOX_LEFT(prg)->x = HIT_BOX_CENTER(prg)->x + ((MOVE_PIXELS ) / 2) * cos(HIT_BOX_ANGLE(prg) - M_PI/2);
  HIT_BOX_LEFT(prg)->y = HIT_BOX_CENTER(prg)->y + ((MOVE_PIXELS ) / 2) * sin(HIT_BOX_ANGLE(prg) - M_PI/2);
  HIT_BOX_RIGHT(prg)->x = HIT_BOX_CENTER(prg)->x + ((MOVE_PIXELS ) / 2) * cos(HIT_BOX_ANGLE(prg) + M_PI/2);
  HIT_BOX_RIGHT(prg)->y = HIT_BOX_CENTER(prg)->y + ((MOVE_PIXELS ) / 2) * sin(HIT_BOX_ANGLE(prg) + M_PI/2); */
}

#if BONUS_FLAG == 0

int	make_move(t_prg *prg, int dir, int side)
{
	double dx;
	double dy;
	bool  can_move;

	if (side == 0)
	{
		dx = (prg->camara_x * MOVE_SPEED * dir);
		dy = (prg->camara_y * MOVE_SPEED * dir);
	}
	else
	{
		dx = -prg->camara_y * MOVE_SPEED * dir;
		dy = prg->camara_x * MOVE_SPEED * dir;
	}
	get_hit_box_values(prg, dx, dy);
  	can_move = check_collision(prg, HIT_BOX_CENTER(prg), HIT_BOX_LEFT(prg), HIT_BOX_RIGHT(prg));
	if(can_move)
	{
		PLAYER_X(prg) += dx;
		PLAYER_Y(prg) += dy;
		PLAYER_CENTER_X(prg) += (int)(dx * TILE_SIZE);
		PLAYER_CENTER_Y(prg) += (int)(dy * TILE_SIZE);
		update_window(prg);
	}
	return (1);
}
#else
int make_move(t_prg *prg, int dir, int side)
{
	double dx;
	double dy;
	bool  can_move;

	if (side == 0)
	{
		dx = (prg->camara_x * MOVE_SPEED * dir);
		dy = (prg->camara_y * MOVE_SPEED * dir);
	}
	else
	{
		dx = -prg->camara_y * MOVE_SPEED * dir;
		dy = prg->camara_x * MOVE_SPEED * dir;
	}
	get_hit_box_values(prg, dx, dy);
  	can_move = check_collision(prg, HIT_BOX_CENTER(prg), HIT_BOX_LEFT(prg), HIT_BOX_RIGHT(prg));
	if(can_move)
	{
		PLAYER_X(prg) += dx;
		PLAYER_Y(prg) += dy;
		PLAYER_CENTER_X(prg) += (int)(dx * TILE_SIZE);
		PLAYER_CENTER_Y(prg) += (int)(dy * TILE_SIZE);
		move_triangle(prg, (int)(dx * TILE_SIZE), (int)(dy * TILE_SIZE));
		update_window(prg);
	}
	return (1);
}
#endif