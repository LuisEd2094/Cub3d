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

  printf("player X %f, player Y %f step x %f step y %f\n", PLAYER_X(prg), PLAYER_Y(prg), RAY_STEP_X(prg), RAY_STEP_Y(prg));

  if (RAY_DIST_X(prg) != FLT_MAX && fabs(RAY_DIST_X(prg)) <= HIT_BOX)
  {
    if (RAY_DELTA_X(prg) < 0 && MAP(prg)[(int)PLAYER_Y(prg)][(int)PLAYER_X(prg) - 1] == '1')
      *x = 0;
    else if (MAP(prg)[(int)PLAYER_Y(prg)][(int)PLAYER_X(prg) + 1] == '1')
      *x = 0;

  }
  if (RAY_DIST_Y(prg) != FLT_MAX && fabs(RAY_DIST_Y(prg)) <= HIT_BOX)
  {
    if (RAY_DELTA_Y(prg) < 0 && MAP(prg)[(int)PLAYER_Y(prg) - 1][(int)PLAYER_X(prg)] == '1')
      *y = 0;
    else if (MAP(prg)[(int)PLAYER_Y(prg) + 1][(int)PLAYER_X(prg)] == '1')
      *y = 0;
    printf("I AM HERE\n");
  }
}

void put_colision_pixels(t_mlx*mlx, t_point* hit_box_center, t_point*hit_box_left, t_point* hit_box_right)
{
  mlx_pixel_put(mlx->ptr, mlx->window, hit_box_center->x, hit_box_center->y, 0x008000);
  mlx_pixel_put(mlx->ptr, mlx->window, hit_box_left->x, hit_box_left->y, 0x008000);
  mlx_pixel_put(mlx->ptr, mlx->window, hit_box_right->x, hit_box_right->y, 0x008000);



}



int make_move(t_prg *prg, int dir)
{

  t_point hit_box_center;
  t_point hit_box_left;
  t_point hit_box_right;


double move_x;
double move_y;

  double hit_box_angle = atan2(CAMARA_Y(prg), CAMARA_X(prg));
  printf("hit_box_angle %f \n", hit_box_angle);

  hit_box_center.x = PLAYER_CENTER_X(prg) + (MOVE_PIXELS * dir) * cos(hit_box_angle);
  hit_box_center.y = PLAYER_CENTER_Y(prg) + (MOVE_PIXELS * dir) * sin(hit_box_angle);

  hit_box_left.x = hit_box_center.x + ((MOVE_PIXELS * dir) / 2) * cos(hit_box_angle - M_PI/2);
  hit_box_left.y = hit_box_center.y + ((MOVE_PIXELS * dir) / 2) * sin(hit_box_angle - M_PI/2);

  // Coordinates to the right
  hit_box_right.x = hit_box_center.x + ((MOVE_PIXELS * dir) / 2) * cos(hit_box_angle + M_PI/2);
  hit_box_right.y = hit_box_center.y + ((MOVE_PIXELS * dir) / 2) * sin(hit_box_angle + M_PI/2);


  move_x = MOVE_SPEED;
  move_y = MOVE_SPEED;


  printf("CENTER X %i, CENTER Y %i\n LEFT X %i LEFT %i\n RIGHT X %i RIGHT Y %i\n", hit_box_center.x / TILE_SIZE, hit_box_center.y / TILE_SIZE, hit_box_left.x /64,  hit_box_left.y / 64, hit_box_right.x / 64, hit_box_right.y /64 );
  
  PLAYER_X(prg) += (move_x * prg->camara_x) * dir;
  PLAYER_Y(prg) += (move_y * prg->camara_y) * dir;
 // printf("player X pos %f player Y pos %f ray X side %f, ray Y side %f\n",PLAYER_X(prg), PLAYER_Y(prg), RAY_DIST_X(prg), RAY_DIST_Y(prg));

  move_triangle(prg, dir, move_x, move_y);
  update_window(prg);
  put_colision_pixels(prg->mlx, &hit_box_center,  &hit_box_left,  &hit_box_right);
  return (1);
}