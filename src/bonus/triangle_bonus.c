#include <cub3d.h>

void move_triangle(t_prg *prg, int dir, double x, double y) 
{
    int dx = (prg->camara_x * (x * TILE_SIZE) *  dir);
    int dy = (prg->camara_y * (y * TILE_SIZE) *  dir);

    PLAYER_DIR_X(prg) += dx;
    PLAYER_DIR_Y(prg) += dy;
    PLAYER_LEFT_X(prg) += dx;
    PLAYER_LEFT_Y(prg) += dy;
    PLAYER_RIGHT_X(prg) += dx;
    PLAYER_RIGHT_Y(prg) += dy;
    PLAYER_CENTER_X(prg) += dx;
    PLAYER_CENTER_Y(prg) += dy;
}


void rotate_point(t_point *point, t_point *center, int dir, double rads)
{
  int temp_x;
  int temp_y;
  double angle;

  angle = ROTATION_ANGLE  * (M_PI / 180.0);
  temp_x = point->x;
  temp_y = point->y;
  printf("%f angle double %f rads * -1 %d Rotation ANGLe\n", angle, rads * -1, ROTATION_ANGLE);

  point->x = round(((temp_x - center->x) * cos(rads * -1) + (temp_y - center->y) * sin(rads * -1)) + center->x);
  point->y = round((( -1 * (temp_x - center->x)) * sin(rads * -1) + (temp_y - center->y) * cos(rads * -1)) + center->y);
}