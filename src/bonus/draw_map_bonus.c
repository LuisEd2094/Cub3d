#include <cub3d.h>

int side_of_line(t_point *p1, t_point *p2, t_point *p3)
{
  return ((p2->x - p1->x) * (p3->y - p1->y) - (p3->x - p1->x) * (p2->y - p1->y));
}

bool calculate_if_inside_player(t_map *map, int x, int y)
{
  t_point p3;
  int     side_a_b;
  int     side_b_c;
  int     side_c_a;
  
  p3.x = x;
  p3.y = y;
  side_a_b = side_of_line(map->a, map->b, &p3);
  side_b_c = side_of_line(map->b, map->c, &p3);
  side_c_a = side_of_line(map->c, map->a, &p3);

  return ((side_a_b >= 0 && side_b_c >= 0 && side_c_a >= 0) || \
          (side_a_b <= 0 && side_b_c <= 0 && side_c_a <= 0)); 
}

void  set_mini_map_vals(t_prg *prg)
{


}


void get_x_values(t_prg *prg)
{
  double  reminder;
  double  integer;

  if (prg->mini_map->off_set_x && PLAYER_CENTER_X(prg) + 1 > (MINI_MAP_SIZE / 2))
  {
      reminder = modf(PLAYER_X(prg), &integer);
      ft_printf(1,"map x cal %i\n", (int)(((MINI_MAP_SIZE / 2) + ((reminder * TILE_SIZE)) )));
      MAP_X(prg) = ((PLAYER_CENTER_X(prg) + 1) - (MINI_MAP_SIZE / 2)) / TILE_SIZE;
      prg->mini_map->a->x = ((((MINI_MAP_SIZE / 2) - TILE_SIZE) + ((reminder * TILE_SIZE)))) + ((TILE_SIZE / 2) * cos(prg->player->angle )); 
      prg->mini_map->b->x = ((((MINI_MAP_SIZE / 2) - TILE_SIZE) + ((reminder * TILE_SIZE)))) + ((TILE_SIZE / 2) * cos(prg->player->angle + (2.0 * M_PI / 3.0)));
      prg->mini_map->c->x = ((((MINI_MAP_SIZE / 2) - TILE_SIZE) + ((reminder * TILE_SIZE)))) + ((TILE_SIZE / 2) * cos(prg->player->angle + (4.0 * M_PI / 3.0)));  
  }
  else
  {
    prg->mini_map->a->x = ((PLAYER_CENTER_X(prg))) + ((TILE_SIZE / 2) * cos(prg->player->angle )); 
    prg->mini_map->b->x = ((PLAYER_CENTER_X(prg)) )   + ((TILE_SIZE / 2) * cos(prg->player->angle + (2.0 * M_PI / 3.0)));
    prg->mini_map->c->x = ((PLAYER_CENTER_X(prg)))   + ((TILE_SIZE / 2) * cos(prg->player->angle + (4.0 * M_PI / 3.0)));
    MAP_X(prg) = -1;  
  }


    
  prg->mini_map->a->y = ((PLAYER_CENTER_Y(prg)))  + ((TILE_SIZE / 2) * sin(prg->player->angle )); 
  prg->mini_map->b->y = ((PLAYER_CENTER_Y(prg) + 1))   + ((TILE_SIZE / 2) * sin(prg->player->angle + (2.0 * M_PI / 3.0)));
  prg->mini_map->c->y = ((PLAYER_CENTER_Y(prg) + 1) )  + ((TILE_SIZE / 2) * sin(prg->player->angle + (4.0 * M_PI / 3.0)));  

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
  else if (calculate_if_inside_player(prg->mini_map, x, y))
      return (0xFFFF00);
  else
    return (0xededed);
}


/*vertex1 = (playerX + dirX * triangleSize, playerY + dirY * triangleSize)
vertex2 = (playerX + dirY * triangleSize, playerY - dirX * triangleSize)
vertex3 = (playerX - dirY * triangleSize, playerY + dirX * triangleSize)*/

void draw_map(t_prg *prg)
{
  int x;
  int y;

  set_mini_map_vals(prg);
  get_x_values(prg);

  x = -1;
  while (++x < MAP_MAX_W(prg))
  {
   if (x % (TILE_SIZE) == 0)
      MAP_X(prg)++;
    if (prg->mini_map->off_set_y)
    {
      if (PLAYER_CENTER_Y(prg) + 1 > (MINI_MAP_SIZE / 2))
      {
        MAP_Y(prg) = (((PLAYER_CENTER_Y(prg) + 1) - (MINI_MAP_SIZE / 2)) / TILE_SIZE);
        double intteger = 0;
        double reminder = modf(PLAYER_Y(prg), &intteger);
        int mini_y = (reminder * TILE_SIZE);
        //printf("mini y%i  reminder %f\n", mini_y, reminder);
        prg->mini_map->a->y = ((reminder * TILE_SIZE) + ((MINI_MAP_SIZE) / 2) - TILE_SIZE) + ((TILE_SIZE / 2) * sin(prg->player->angle )); 
        prg->mini_map->b->y = ((reminder * TILE_SIZE) + ((MINI_MAP_SIZE) / 2)- TILE_SIZE) + ((TILE_SIZE / 2) * sin(prg->player->angle + (2.0 * M_PI / 3.0)));
        prg->mini_map->c->y = ((reminder * TILE_SIZE) + ((MINI_MAP_SIZE) / 2)- TILE_SIZE) + ((TILE_SIZE / 2) * sin(prg->player->angle + (4.0 * M_PI / 3.0)));  
      }
      else
        MAP_Y(prg) = -1;
    }
    else
      MAP_Y(prg) = -1;
      // printf("I am moving player center %o\n",PLAYER_CENTER_Y(prg));
      // printf("I am moving player Y %f\n",PLAYER_Y(prg));
      // printf("y in mini map %i\n", prg->mini_map->a->y );


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
