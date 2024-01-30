#include <cub3d.h>

/* void move_triangle(t_prg *prg, int dx, int dy) 
{
    PLAYER_DIR_X(prg) += dx;
    PLAYER_DIR_Y(prg) += dy;
    PLAYER_LEFT_X(prg) += dx;
    PLAYER_LEFT_Y(prg) += dy;
    PLAYER_RIGHT_X(prg) += dx;
    PLAYER_RIGHT_Y(prg) += dy;
}


void rotate_point(t_point *point, t_point *center, double rads)
{
  int temp_x;
  int temp_y;

  temp_x = point->x;
  temp_y = point->y;
  point->x = round(((temp_x - center->x) * cos(rads * -1) + (temp_y - center->y) * sin(rads * -1)) + center->x);
  point->y = round((( -1 * (temp_x - center->x)) * sin(rads * -1) + (temp_y - center->y) * cos(rads * -1)) + center->y);
} */