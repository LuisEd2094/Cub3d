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
  char *pixel; 
  int x;
  int y;

  set_mini_map_vals(prg);
  x = -1;
  while (++x < MAP_MAX_W(prg))
  {
   if (x % (TILE_SIZE) == 0)
      MAP_X(prg)++;
    MAP_Y(prg) = -1;
    y = -1;
    while (++y < MAP_MAX_H(prg))
    {
      if (y % (TILE_SIZE) == 0)
        MAP_Y(prg)++;
      pixel = prg->mini_map->t_img->addr + (y * prg->mini_map->t_img->line_length + x * (prg->mini_map->t_img->bpp / 8));  
      *(unsigned int*)pixel = (get_pixel_color(prg, x, y));
    }
  }
  mlx_put_image_to_window(prg->mlx->ptr, prg->mlx->window, prg->mini_map->t_img->img, 0, 0);
}
