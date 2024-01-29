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

void  set_mini_map_vals(t_prg *prg)
{
  MAP_MAX_W(prg) = ft_min(MAP_W(prg), MINI_MAP_SIZE); // this MAX i should calculate once
  MAP_MAX_H(prg) = ft_min(MAP_H(prg), MINI_MAP_SIZE);
  prg->mini_map->off_set_x = MAP_W(prg) > MINI_MAP_SIZE;
  prg->mini_map->off_set_y = MAP_H(prg) > MINI_MAP_SIZE;
  MAP_X(prg) = -1;
}

int get_pixel_color(t_prg *prg, int x, int y)
{
  if (x % (TILE_SIZE) == 0 || y % (TILE_SIZE)  == 0) // DEBUG GRID
    return (0xFFFFFF);
  if (prg->map[MAP_Y(prg)][MAP_X(prg)] == '1')
    return (0xFF0000);
  else if (prg->map[MAP_Y(prg)][MAP_X(prg)] == '2')
    return (0x00FF00);
  else if (prg->map[MAP_Y(prg)][MAP_X(prg)] == '3')
    return (0x00008B);
  else if (calculate_if_inside_player(prg->player, x, y))
      return (0xFFFF00);
  else
    return (0xededed);
}

void draw_map(t_prg *prg)
{
  int x;
  int y;

  set_mini_map_vals(prg);
  if (prg->mini_map->off_set_x)
  {
    if (PLAYER_CENTER_X(prg) + 1 > (MINI_MAP_SIZE / 2))
      MAP_X(prg) = ((PLAYER_CENTER_X(prg) + 1) - (MINI_MAP_SIZE / 2)) / TILE_SIZE;
  }
  x = -1;
  while (++x < MAP_MAX_W(prg))
  {
   if (x % (TILE_SIZE) == 0)
      MAP_X(prg)++;
    if (prg->mini_map->off_set_y)
    {
      if (PLAYER_CENTER_Y(prg) + 1 > (MINI_MAP_SIZE / 2))
      {
        MAP_Y(prg) = ((PLAYER_CENTER_Y(prg) + 1) - (MINI_MAP_SIZE / 2)) / TILE_SIZE;
      }
    }
    else
      MAP_Y(prg) = -1;
    y = -1;
    while (++y < MAP_MAX_H(prg))
    {
      if (y % (TILE_SIZE) == 0)
        MAP_Y(prg)++;
      MAP_PIXEL(prg) = MAP_GET_PIXEL(prg, x, y);  
      *(unsigned int*)MAP_PIXEL(prg) = (get_pixel_color(prg, x, y));
    }
  }
}
