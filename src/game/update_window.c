#include <cub3d.h>


#if BONUS_FLAG == 0

void update_window(t_prg *prg)
{
  printf("%i\n", BONUS_FLAG);
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  cast_ray(prg);
  draw_ray(prg);
}
#else
void update_window(t_prg *prg)
{
  printf("%i\n", BONUS_FLAG);
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  draw_map(prg);
  cast_ray(prg);
  draw_ray(prg);
}
#endif