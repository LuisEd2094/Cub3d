#include <cub3d.h>

bool check_collision(t_prg *prg, t_point *center, t_point *left, t_point *right)
{
  if (MAP(prg)[center->y / TILE_SIZE][center->x / TILE_SIZE] == '1')
    return (0);
  if (MAP(prg)[left->y / TILE_SIZE][left->x / TILE_SIZE] == '1')
    return (0);
  if (MAP(prg)[right->y / TILE_SIZE][right->x / TILE_SIZE] == '1')
    return (0);
  if (MAP(prg)[center->y / TILE_SIZE][center->x / TILE_SIZE] == '2')
    return (0);
  if (MAP(prg)[left->y / TILE_SIZE][left->x / TILE_SIZE] == '2')
    return (0);
  if (MAP(prg)[right->y / TILE_SIZE][right->x / TILE_SIZE] == '2')
    return (0);
  return (1);
}

void get_hit_box_values(t_prg *prg, int dir)
{

  HIT_BOX_ANGLE(prg) = atan2(CAMARA_Y(prg), CAMARA_X(prg));
  HIT_BOX_CENTER(prg)->x = PLAYER_CENTER_X(prg) + (MOVE_PIXELS * dir) * cos(HIT_BOX_ANGLE(prg));
  HIT_BOX_CENTER(prg)->y = PLAYER_CENTER_Y(prg) + (MOVE_PIXELS * dir) * sin(HIT_BOX_ANGLE(prg));
  HIT_BOX_LEFT(prg)->x = HIT_BOX_CENTER(prg)->x + ((MOVE_PIXELS * dir) / 2) * cos(HIT_BOX_ANGLE(prg) - M_PI/2);
  HIT_BOX_LEFT(prg)->y = HIT_BOX_CENTER(prg)->y + ((MOVE_PIXELS * dir) / 2) * sin(HIT_BOX_ANGLE(prg) - M_PI/2);
  HIT_BOX_RIGHT(prg)->x = HIT_BOX_CENTER(prg)->x + ((MOVE_PIXELS * dir) / 2) * cos(HIT_BOX_ANGLE(prg) + M_PI/2);
  HIT_BOX_RIGHT(prg)->y = HIT_BOX_CENTER(prg)->y + ((MOVE_PIXELS * dir) / 2) * sin(HIT_BOX_ANGLE(prg) + M_PI/2);
}

#if BONUS_FLAG == 0

int make_move(t_prg *prg, int dir)
{
  double move_x;
  double move_y;
  bool  can_move;


  get_hit_box_values(prg, dir);
  can_move = check_collision(prg, HIT_BOX_CENTER(prg), HIT_BOX_LEFT(prg), HIT_BOX_RIGHT(prg));
  if(can_move)
  {
    move_x = MOVE_SPEED;
    move_y = MOVE_SPEED;
    int dx = (prg->camara_x * (move_x * TILE_SIZE) *  dir);
    int dy = (prg->camara_y * (move_y * TILE_SIZE) *  dir);
    PLAYER_X(prg) += (move_x * prg->camara_x) * dir;
    PLAYER_Y(prg) += (move_y * prg->camara_y) * dir;
    PLAYER_CENTER_X(prg) += dx;
    PLAYER_CENTER_Y(prg) += dy;
    update_window(prg);
  }
  return (1);
}
#else
int make_move(t_prg *prg, int dir)
{
  double move_x;
  double move_y;
  bool  can_move;

  get_hit_box_values(prg, dir);
  can_move = check_collision(prg, HIT_BOX_CENTER(prg), HIT_BOX_LEFT(prg), HIT_BOX_RIGHT(prg));
  if(can_move)
  {
    move_x = MOVE_SPEED;
    move_y = MOVE_SPEED;
    PLAYER_X(prg) += (move_x * prg->camara_x) * dir;
    PLAYER_Y(prg) += (move_y * prg->camara_y) * dir;
    move_triangle(prg, dir, move_x, move_y);
    update_window(prg);
  }
  return (1);
}
#endif