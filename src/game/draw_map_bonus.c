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

  int wallColor = 0xFF0000; // Red for walls
  int y_pos;
  int x_pos; 


  x_pos = 0;
  for (int x = 0; x < w; ++x)
  {
    if (x % TILE_WIDTH == TILE_WIDTH - 1)
      x_pos++;
    y_pos = 0;
    for (int y = 0; y < h ; ++y)
    {
      if (y % TILE_HEIGHT == TILE_HEIGHT - 1)
        y_pos++;     
      if (y_pos < prg->map_h && x_pos < ft_strlen(prg->map[y_pos]))
      {
        if (prg->map[y_pos][x_pos] == '1')
          wallColor = 0xFF0000;
        else if (calculate_if_inside_player(prg->player, x, y))
                  wallColor = 0xFFFF00;
        else
          wallColor = 0x000000;
      }
      else
        wallColor = 0x000000;
      mlx_pixel_put(prg->mlx->ptr, prg->mlx->window, x, y, wallColor);

    }
  }
}
