#include <cub3d.h>


void update_window(t_prg *prg)
{
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  draw_map(prg);
}

int rotate_camara(t_prg *prg, int dir)
{
  double old_dir_x = prg->camara_x;
  double old_plane_x = prg->plane_x;
  double rotate_angle = (90  * M_PI / 180.0);
  double cos_rot = cos(rotate_angle);
  double sin_rot = sin(rotate_angle);
  

  double new_camara_x = prg->camara_x * cos_rot - prg->camara_y * sin_rot;
  double new_camara_y = prg->camara_x * sin_rot + prg->camara_y * cos_rot;

  // Rotate plane vector
  double new_plane_x = prg->plane_x * cos_rot - prg->plane_y * sin_rot;
  double new_plane_y = old_plane_x  * sin_rot + prg->plane_y * cos_rot;

  prg->camara_x = new_camara_x * dir;
  prg->camara_y = new_camara_y * dir;
  prg->plane_x = new_plane_x * dir ;
  prg->plane_y = new_plane_y * dir;

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
void moveTriangle(t_prg *prg, int distance, float direction) {
    // Convert direction to radians
    float radians = degreesToRadians(direction);

    // Calculate the new positions using trigonometry
    PLAYER_DIR_X(prg) += distance * cos(radians);
    PLAYER_DIR_Y(prg) += distance * sin(radians);
    PLAYER_LEFT_X(prg) += distance * cos(radians);
    PLAYER_LEFT_Y(prg) += distance * sin(radians);
    PLAYER_RIGHT_X(prg) += distance * cos(radians);
    PLAYER_RIGHT_Y(prg) += distance * sin(radians);
}


int make_move(t_prg *prg, int dir)
{
  double move_speed;

  move_speed = 0.5;
  //prg->player_x += (move_speed) * dir; // 1 is movement speed should check camara angle first
  PLAYER_Y(prg) += (move_speed * prg->camara_y) * dir;

  float direction = calculateDirection(PLAYER_DIR_X(prg), PLAYER_DIR_Y(prg), PLAYER_LEFT_X(prg), PLAYER_LEFT_Y(prg));

  moveTriangle(prg, 1, direction * dir);
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
      return (rotate_camara(prg, -1));
  else if ((key == KEY_D || key == KEY_RGT))
      return (rotate_camara(prg, 1));
  return (0);
}



void get_hooks(t_prg *prg)
{
  mlx_hook(prg->mlx->window, 17, 0, close_game, (void *)prg);
  mlx_key_hook(prg->mlx->window, key_hook, (void *)prg); 
}