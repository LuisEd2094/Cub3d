#include <cub3d.h>

#if BONUS_FLAG == 0

void destroy_img(t_prg *prg)
{
    if (prg->img->img)
    {
        mlx_destroy_image(MLX_PTR(prg), prg->img->img);
    }
}

#else

void destroy_img(t_prg *prg)
{
    if (prg->img->img)
    {
        mlx_destroy_image(MLX_PTR(prg), prg->img->img);
    }
    if (MAP_IMG(prg))
    {
        mlx_destroy_image(MLX_PTR(prg), MAP_IMG(prg));
    }
}

#endif