#include <cub3d.h>

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