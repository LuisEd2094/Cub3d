#include <cub3d.h>

int check_camara(int coordiante, int center)
{
  if (coordiante == center)
    return (0);
  else if (coordiante > center)
    return (1);
  else
    return (-1);
}

#if BONUS_FLAG == 0
int rotate_player(t_prg *prg, int dir)
{
  printf("i am normal\n");
      double  camX;
    double  planeX;
    double  rads;
    rads = M_PI / 180.0 * 15 * dir;
    camX = prg->camara_x;
    planeX = prg->plane_x;
    prg->camara_x = camX * cos(rads) - prg->camara_y * sin(rads);
    prg->camara_y = camX * sin(rads) + prg->camara_y * cos(rads);
    prg->plane_x = planeX * cos(rads) - prg->plane_y * sin(rads);
    prg->plane_y = planeX * sin(rads) + prg->plane_y * cos(rads);
    update_window(prg);
    return (0);
}


#else

int rotate_player(t_prg *prg, int dir)
{
  printf("i am bonus\n");
  
    rotate_point( prg->player->dir, PLAYER_CENTER(prg), dir);
    rotate_point( prg->player->left_corner, PLAYER_CENTER(prg), dir);
    rotate_point( prg->player->right_corner, PLAYER_CENTER(prg), dir);

    prg->camara_x = check_camara(PLAYER_DIR_X(prg), PLAYER_CENTER_X(prg));
    prg->camara_y = check_camara(PLAYER_DIR_Y(prg), PLAYER_CENTER_Y(prg));
    prg->player->angle = atan2(prg->camara_y, prg->camara_x);
    update_window(prg);
  return (0);
}

#endif