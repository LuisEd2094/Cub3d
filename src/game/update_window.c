#include <cub3d.h>

void update_window(t_prg *prg)
{
  mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
  draw_map(prg);
  cast_ray(prg);
  draw_ray(prg);
}