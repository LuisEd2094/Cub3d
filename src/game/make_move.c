#include <cub3d.h>

int make_move(t_prg *prg, int dir)
{
  double move_speed;

  move_speed = MOVE_SPEED;
  PLAYER_X(prg) += (move_speed * prg->camara_x) * dir;
  PLAYER_Y(prg) += (move_speed * prg->camara_y) * dir;
  move_triangle(prg, dir);
  update_window(prg);
  return (1);
}