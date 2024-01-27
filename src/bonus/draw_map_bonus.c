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

void draw_map(t_prg *prg)
{
  int color; // Red for walls
  int y_pos;
  int x_pos;
  char *pixel; 
  int x;
  int y;

  int max_w = ft_min(((prg->map_w + 1) * TILE_SIZE), MINI_MAP_SIZE);
  int max_h = ft_min((prg->map_h) * TILE_SIZE, MINI_MAP_SIZE);
  x_pos = -1;
  for ( x = 0; x < max_w; ++x)
  {
    if (x % (TILE_SIZE) == 0)
      x_pos++;
    y_pos = -1;
    for ( y = 0; y < max_h ; ++y)
    {
      if (y % (TILE_SIZE) == 0)
        y_pos++;
      pixel = prg->mini_map->addr + (y * prg->mini_map->line_length + x * (prg->img->bpp / 8));  
      if (is_inside_map(x_pos, y_pos, prg))
      {
        if (prg->map[y_pos][x_pos] == '1')
          *(unsigned int*)pixel = 0xFF0000;
        else if (prg->map[y_pos][x_pos] == '2')
          *(unsigned int*)pixel = 0x00FF00;
        else if (prg->map[y_pos][x_pos] == '3')
          *(unsigned int*)pixel = 0x00008B;
        else if (x == PLAYER_CENTER_X(prg) && y == PLAYER_CENTER_Y(prg))
          *(unsigned int*)pixel = 0x0000FF;
        else if (calculate_if_inside_player(prg->player, x, y))
            *(unsigned int*)pixel = 0xFFFF00;
        else
          *(unsigned int*)pixel = 0xededed ;
      }
      else
        *(unsigned int*)pixel = 0xededed ;

      //DEBUG GRID
      if (x % (TILE_SIZE) == 0 || y % (TILE_SIZE)  == 0)
        *(unsigned int*)pixel = 0xFFFFFF;
    }
  }
  printf("x %i y %i\n", x, y);
  mlx_put_image_to_window(prg->mlx->ptr, prg->mlx->window, prg->mini_map->img, 0, 0);
}
