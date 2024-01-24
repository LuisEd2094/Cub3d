#include <cub3d.h>


void get_initial_dists(t_prg *prg)
{
  if(RAY_DIRECTION_X(prg) < 0)
  {
    RAY_STEP_X(prg) = -1;
    RAY_DIST_X(prg) = ((PLAYER_X(prg) - RAY_MAP_X(prg)) * RAY_DELTA_X(prg));
  }
  else
  {
    RAY_STEP_X(prg) = 1;
    RAY_DIST_X(prg) = ((RAY_MAP_X(prg) + 1.0 - PLAYER_X(prg)) * RAY_DELTA_X(prg));
  }
  if(RAY_DIRECTION_Y(prg) < 0)
  {
    RAY_STEP_Y(prg) = -1;
    RAY_DIST_Y(prg) = (PLAYER_Y(prg) - RAY_MAP_Y(prg)) * RAY_DELTA_Y(prg);
  }
  else
  {
    RAY_STEP_Y(prg) = 1;
    RAY_DIST_Y(prg) = (RAY_MAP_Y(prg) + 1.0 - PLAYER_Y(prg)) * RAY_DELTA_Y(prg);
  }

}

void set_ray_values(t_prg *prg)
{
  RAY_START_X(prg) = PLAYER_CENTER_X(prg);
  RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
  RAY_END_X(prg) = RAY_START_X(prg);
  RAY_END_Y(prg) = RAY_START_Y(prg);
  RAY_DIRECTION_X(prg) = CAMARA_X(prg);
  RAY_DIRECTION_Y(prg) = CAMARA_Y(prg);
  RAY_DELTA_X(prg) = (RAY_DIRECTION_X(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_X(prg));
  RAY_DELTA_Y(prg) = (RAY_DIRECTION_Y(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_Y(prg));
  RAY_MAP_X(prg) = PLAYER_X(prg);
  RAY_MAP_Y(prg) = PLAYER_Y(prg);
  get_initial_dists(prg);
}

void correct_for_collision(t_prg *prg, int dir, double *x, double *y)
{ 
  set_ray_values(prg);
  if (dir < 0)
  {
    if (RAY_DIST_X(prg) != FLT_MAX)
      RAY_DIST_X(prg) = 1 - fabs(RAY_DIST_X(prg));
    if (RAY_DIST_Y(prg) != FLT_MAX)
      RAY_DIST_Y(prg) = 1 - fabs(RAY_DIST_Y(prg));
  }

  if (RAY_DIST_X(prg) != FLT_MAX && fabs(RAY_DIST_X(prg)) <= HIT_BOX)
    printf("I am about to collide\n");
  if (RAY_DIST_Y(prg) != FLT_MAX && fabs(RAY_DIST_Y(prg)) <= HIT_BOX)
    printf("I am about to collide\n");
}



int make_move(t_prg *prg, int dir)
{
  double move_x;
  double move_y;

  move_x = MOVE_SPEED;
  move_y = MOVE_SPEED;
  correct_for_collision(prg, dir, &move_x, &move_y);
  PLAYER_X(prg) += (move_x * prg->camara_x) * dir;
  PLAYER_Y(prg) += (move_y * prg->camara_y) * dir;
  printf("player X pos %f player Y pos %f ray X side %f, ray Y side %f\n",PLAYER_X(prg), PLAYER_Y(prg), RAY_DIST_X(prg), RAY_DIST_Y(prg));

  move_triangle(prg, dir);
  update_window(prg);
  return (1);
}