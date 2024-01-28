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
    printf("Before plane x %f plane y %f\n", prg->plane_x, prg->plane_y);
    prg->camara_x = camX * cos(rads) - prg->camara_y * sin(rads);
    prg->camara_y = camX * sin(rads) + prg->camara_y * cos(rads);
    prg->plane_x = planeX * cos(rads) - prg->plane_y * sin(rads);
    prg->plane_y = planeX * sin(rads) + prg->plane_y * cos(rads);
        printf("after plane x %f plane y %f\n", prg->plane_x, prg->plane_y);
    update_window(prg);
    return (0);
}


#else

int rotate_player(t_prg *prg, int dir)
{  
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
    prg->player->angle = atan2(prg->camara_y, prg->camara_x);
    rotate_point( prg->player->dir, PLAYER_CENTER(prg), dir, rads);
    rotate_point( prg->player->left_corner, PLAYER_CENTER(prg), dir, rads);
    rotate_point( prg->player->right_corner, PLAYER_CENTER(prg), dir, rads);
    update_window(prg);
  return (0);
}

#endif