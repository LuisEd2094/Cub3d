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
int rotate_player(t_prg *prg, int dir, int angle)
{
  double  cam_x;
  double  plane_x;
  double  rads;

  rads = M_PI / 180.0 * 15 * dir;
  cam_x = prg->camara_x;
  plane_x = prg->plane_x;
  prg->camara_x = cam_x * cos(rads) - prg->camara_y * sin(rads);
  prg->camara_y = cam_x * sin(rads) + prg->camara_y * cos(rads);
  prg->plane_x = plane_x * cos(rads) - prg->plane_y * sin(rads);
  prg->plane_y = plane_x * sin(rads) + prg->plane_y * cos(rads);
  update_window(prg);
  return (0);
}


#else

int rotate_player(t_prg *prg, int dir, int angle)
{ 
  double  cam_x;
  double  plane_x;
  double  rads;

  rads = M_PI / 180.0 * angle * dir;
  cam_x = prg->camara_x;
  plane_x = prg->plane_x;
  prg->camara_x = cam_x * cos(rads) - prg->camara_y * sin(rads);
  prg->camara_y = cam_x * sin(rads) + prg->camara_y * cos(rads);
  prg->plane_x = plane_x * cos(rads) - prg->plane_y * sin(rads);
  prg->plane_y = plane_x * sin(rads) + prg->plane_y * cos(rads);
  prg->player->angle += rads; // should check to reset it so it oesn't get too high
/*   rotate_point(prg->player->dir, PLAYER_CENTER(prg),  rads);
  rotate_point(prg->player->left_corner, PLAYER_CENTER(prg),  rads);
  rotate_point(prg->player->right_corner, PLAYER_CENTER(prg), rads); */
  update_window(prg);
  return (0);
}

#endif