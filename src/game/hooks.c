#include <cub3d.h>


void draw_ray(t_prg *p) 
{
    int dx = abs(RAY_END_X(p) - RAY_START_X(p)) * TILE_WIDTH;
    int dy = abs(RAY_END_Y(p) - RAY_START_Y(p)) * TILE_HEIGHT;
    int sx = (RAY_START_X(p) < RAY_END_X(p)) ? 1 : -1;
    int sy = (RAY_START_Y(p) < RAY_END_Y(p)) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(MLX_PTR(p), MLX_WIN(p), RAY_START_X(p), RAY_START_Y(p), 0x0000FF);

        if (RAY_START_X(p) == RAY_END_X(p) && RAY_START_Y(p) == RAY_END_Y(p))
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            RAY_START_X(p) += sx;
        }
        if (e2 < dx) {
            err += dx;
            RAY_START_Y(p) += sy;
        }
    }
}

void update_window(t_prg *prg)
{
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  draw_map(prg);
  draw_ray(prg);
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

int check_camara(int coordiante, int center)
{
  if (coordiante == center)
    return (0);
  else if (coordiante > center)
    return (1);
  else
    return (-1);
}

int rotate_triangle(t_prg *prg, int dir)
{
  
  rotate_point( prg->player->dir, PLAYER_CENTER(prg), dir);
  rotate_point( prg->player->left_corner, PLAYER_CENTER(prg), dir);
  rotate_point( prg->player->right_corner, PLAYER_CENTER(prg), dir);

  prg->camara_x = check_camara(PLAYER_DIR_X(prg), PLAYER_CENTER_X(prg));
  prg->camara_y = check_camara(PLAYER_DIR_Y(prg), PLAYER_CENTER_Y(prg));
  update_window(prg);
  return (0);
}

// Function to move an equilateral triangle
void move_triangle(t_prg *prg, int dir) {
    // Convert direction to radians
    int dx = (prg->camara_x * (MOVE_SPEED * TILE_WIDTH) *  dir);
    int dy = (prg->camara_y * (MOVE_SPEED * TILE_WIDTH) *  dir);

    // Calculate the new positions using trigonometry
    PLAYER_DIR_X(prg) += dx;
    PLAYER_DIR_Y(prg) += dy;
    PLAYER_LEFT_X(prg) += dx;
    PLAYER_LEFT_Y(prg) += dy;
    PLAYER_RIGHT_X(prg) += dx;
    PLAYER_RIGHT_Y(prg) += dy;
    PLAYER_CENTER_X(prg) += dx;
    PLAYER_CENTER_Y(prg) += dy;
}


int make_move(t_prg *prg, int dir)
{
  double move_speed;

  move_speed = MOVE_SPEED;
  PLAYER_X(prg) += (move_speed * prg->camara_x) * dir;
  PLAYER_Y(prg) += (move_speed * prg->camara_y) * dir;

  move_triangle(prg, dir);
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