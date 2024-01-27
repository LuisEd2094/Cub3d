#include <cub3d.h>

int close_game(t_prg *prg)
{
  exit_success(prg); 
  return (0);
}

#if BONUS_FLAG == 0

int key_hook(int key, t_prg *prg)
{

  // COMMENTING AS MARKER; KEY HOOKS SHOULD CHANGE DEPEDING ON BONUS
    printf("%i\n", key);
  if (key == KEY_ESC || key == KEY_Q)
    close_game(prg);
    else if ((key == KEY_W || key == KEY_UP))
      return (make_move(prg, 1));
  else if ((key == KEY_S || key == KEY_DOWN))
      return (make_move(prg, -1));
  else if ((key == KEY_A || key == KEY_LFT))
      return (rotate_player(prg, 1));
  else if ((key == KEY_D || key == KEY_RGT))
      return (rotate_player(prg, -1));
  return (0);
}
#else
int key_hook(int key, t_prg *prg)
{
  printf("%i\n", key);
  // COMMENTING AS MARKER; KEY HOOKS SHOULD CHANGE DEPEDING ON BONUS
  if (key == KEY_ESC || key == KEY_Q)
    close_game(prg);
  else if ((key == KEY_W || key == KEY_UP))
    return (make_move(prg, 1));
  else if ((key == KEY_S || key == KEY_DOWN))
    return (make_move(prg, -1));
  else if (key == KEY_E || key == KEY_SPACE)
    return (open_door(prg));
  else if ((key == KEY_A || key == KEY_LFT))
    return (rotate_player(prg, 1));
  else if ((key == KEY_D || key == KEY_RGT))
    return (rotate_player(prg, -1));
  return (0);
}

#endif
void get_hooks(t_prg *prg)
{
  mlx_hook(prg->mlx->window, 17, 0, close_game, (void *)prg);
  mlx_key_hook(prg->mlx->window, key_hook, (void *)prg); 
}