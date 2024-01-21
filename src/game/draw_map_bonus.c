#include <cub3d.h>


int side_of_line(t_point *p1, t_point *p2, t_point *p3)
{
  return ((p2->x - p1->x) * (p3->y - p1->y) - (p3->x - p1->x) * (p2->y - p1->y));
}


bool calculate_if_inside_player(t_pc *player, int x, int y)
{
  t_point p3;
  int     side_a_b;
  int     side_b_c;
  int     side_c_a;
  
  p3.x = x;
  p3.y = y;
  side_a_b = side_of_line(player->dir, player->left_corner, &p3);
  side_b_c = side_of_line(player->left_corner, player->right_corner, &p3);
  side_c_a = side_of_line(player->right_corner, player->dir, &p3);

  return ((side_a_b >= 0 && side_b_c >= 0 && side_c_a >= 0) || \
          (side_a_b <= 0 && side_b_c <= 0 && side_c_a <= 0)); 
}



// Function to perform ray casting
/*HitInfo castRay(Ray ray) {
    Point currentPoint = ray.start;
    
    while (isInsideMap(currentPoint.x, currentPoint.y) &&
           map[currentPoint.x][currentPoint.y] != 1) {
        currentPoint.x += ray.direction.x;
        currentPoint.y += ray.direction.y;
    }

    HitInfo hitInfo;
    hitInfo.point = currentPoint;
    hitInfo.distance = sqrt(pow(currentPoint.x - ray.start.x, 2) + pow(currentPoint.y - ray.start.y, 2));

    return hitInfo;
}*/

int is_inside_map(int x, int y, t_prg *prg) {
    return (y >= 0 && y < prg->map_h && x >= 0 && x < ft_strlen(prg->map[y]));
}

void cast_ray(t_prg *prg)
{
  RAY_START_X(prg) = PLAYER_CENTER_X(prg);
  RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
  RAY_DIRECTION_X(prg) = CAMARA_X(prg);
  RAY_DIRECTION_Y(prg) = CAMARA_Y(prg);
  RAY_END_X(prg) = PLAYER_X(prg);
  RAY_END_Y(prg) = PLAYER_Y(prg);  
  
  while (is_inside_map(RAY_END_X(prg), RAY_END_Y(prg), prg) && \
        prg->map[RAY_END_Y(prg)][RAY_END_X(prg)] != '1')
  {
    RAY_END_X(prg) += RAY_DIRECTION_X(prg);
    RAY_END_Y(prg) += RAY_DIRECTION_Y(prg);
  }
  if (RAY_END_Y(prg) == 0)
    RAY_END_Y(prg) = TILE_HEIGHT - 1;
  else
    RAY_END_Y(prg) = (RAY_END_Y(prg) * TILE_HEIGHT) - 1;
  if (RAY_END_X(prg) == 0)
    RAY_END_X(prg) = TILE_WIDTH - 1; 
  else 
    RAY_END_X(prg) = (RAY_END_X(prg) * TILE_WIDTH) - 1;

}

void draw_map(t_prg *prg)
{
  int color = 0xFF0000; // Red for walls
  int y_pos;
  int x_pos; 

  x_pos = -1;
  cast_ray(prg);
  ft_printf(1, "END_X (%i) END_Y(%i)\n", RAY_END_X(prg), RAY_END_Y(prg));
  for (int x = 0; x < w; ++x)
  {
    if (x % (TILE_WIDTH) == 0)
      x_pos++;
    y_pos = -1;
    for (int y = 0; y < h ; ++y)
    {
      if (y % (TILE_HEIGHT) == 0)
        y_pos++;     
      if (is_inside_map(x_pos, y_pos, prg))
      {
        if (prg->map[y_pos][x_pos] == '1')
          color = 0xFF0000;
        else if (x == PLAYER_CENTER_X(prg) && y == PLAYER_CENTER_Y(prg))
          color = 0x0000FF;
        else if (calculate_if_inside_player(prg->player, x, y))
                  color = 0xFFFF00;
        else
          color = 0x000000;
      }
      else
        color = 0x000000;

      //DEBUG GRID
      if (x % (TILE_WIDTH) == 0 || y % (TILE_HEIGHT)  == 0)
        color = 0xFFFFFF;

      mlx_pixel_put(prg->mlx->ptr, prg->mlx->window, x, y, color);

    }
  }
}
