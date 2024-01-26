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
    prg->camara_x = check_camara(PLAYER_DIR_X(prg), PLAYER_CENTER_X(prg));
    prg->camara_y = check_camara(PLAYER_DIR_Y(prg), PLAYER_CENTER_Y(prg));
    prg->player->angle = atan2(prg->camara_y, prg->camara_x);
    update_window(prg);
    return (0);
}

#else

int rotate_player(t_prg *prg, int dir)
{
  
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