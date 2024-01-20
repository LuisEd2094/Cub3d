#include <cub3d.h>


void update_window(t_prg *prg)
{
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  draw_map(prg);
}


void rotatePoint(int x, int y, int cx, int cy, double theta, int *resultX, int *resultY) {
    double radians = theta * (M_PI / 180.0);
    *resultX = (int)((x - cx) * cos(radians) - (y - cy) * sin(radians) + cx);
    *resultY = (int)((x - cx) * sin(radians) + (y - cy) * cos(radians) + cy);
}



void rotate_point(t_point *point, t_point *center, int dir )
{
  int temp_x;
  int temp_y;
  double angle;

  angle = ROTATION_ANGLE  * (M_PI / 180.0);
  temp_x = point->x;
  temp_y = point->y;

  point->x = round(((temp_x - center->x) * cos(angle * dir) + (temp_y - center->y) * sin(angle * dir)) + center->x);
  point->y = round((( -1 * (temp_x - center->x)) * sin(angle * dir) + (temp_y - center->y) * cos(angle * dir)) + center->y);
}

int rotate_triangle(t_prg *prg, int dir)
{
  
  rotate_point( prg->player->dir, PLAYER_CENTER(prg), dir);
  rotate_point( prg->player->left_corner, PLAYER_CENTER(prg), dir);
  rotate_point( prg->player->right_corner, PLAYER_CENTER(prg), dir);

  //RayX 0.657937 RayY -1.000000

  update_window(prg);
  return (0);
}


float calculateDirection(int x1, int y1, int x2, int y2) 
{
    // Calculate the change in x and y
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Calculate the angle in radians
    float radians = atan2(dy, dx);

    // Convert the angle to degrees
    float degrees = radians * 180.0 / M_PI;

    // Ensure the angle is positive
    if (degrees < 0) {
        degrees += 360.0;
    }

    return degrees;
}

float degreesToRadians(float degrees) 
{
    return degrees * M_PI / 180.0;
}

// Function to move an equilateral triangle
void moveTriangle(t_prg *prg, int dir) {
    // Convert direction to radians
    int dx = prg->camara_x * (MOVE_SPEED * TILE_WIDTH) *  dir;
    int dy = prg->camara_y * (MOVE_SPEED * TILE_WIDTH) *  dir;

    // Calculate the new positions using trigonometry
    PLAYER_DIR_X(prg) += dx;
    PLAYER_DIR_Y(prg) += dy;
    PLAYER_LEFT_X(prg) += dx;
    PLAYER_LEFT_Y(prg) += dy;
    PLAYER_RIGHT_X(prg) += dx;
    PLAYER_RIGHT_Y(prg) += dy;
}


int make_move(t_prg *prg, int dir)
{
  double move_speed;

  move_speed = MOVE_SPEED;
  //prg->player_x += (move_speed) * dir; // 1 is movement speed should check camara angle first
  PLAYER_Y(prg) += (move_speed * prg->camara_y) * dir;

  float direction = calculateDirection(PLAYER_DIR_X(prg), PLAYER_DIR_Y(prg), PLAYER_LEFT_X(prg), PLAYER_LEFT_Y(prg));

  moveTriangle(prg, dir);
  update_window(prg);
  return (1);
}

int close_game(t_prg *prg)
{
  exit_success(prg);
  return (0);
}

int key_hook(int key, t_prg *prg)
{
  if (key == KEY_ESC || key == KEY_Q)
    close_game(prg);
    else if ((key == KEY_W || key == KEY_UP))
      return (make_move(prg, 1));
  else if ((key == KEY_S || key == KEY_DOWN))
      return (make_move(prg, -1));
  else if ((key == KEY_A || key == KEY_LFT))
      return (rotate_triangle(prg, 1));
  else if ((key == KEY_D || key == KEY_RGT))
      return (rotate_triangle(prg, -1));
  return (0);
}



void get_hooks(t_prg *prg)
{
  mlx_hook(prg->mlx->window, 17, 0, close_game, (void *)prg);
  mlx_key_hook(prg->mlx->window, key_hook, (void *)prg); 
}