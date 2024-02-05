#include <cub3d.h>

void run_mlx_destroy(t_img *img, t_mlx *mlx)
{
    if (img && img->img)
        mlx_destroy_image(mlx->ptr, img->img);

}

#if BONUS_FLAG == 0

void destroy_img(t_prg *prg)
{
    run_mlx_destroy(prg->img, prg->mlx);
    run_mlx_destroy(prg->north_img, prg->mlx);
    run_mlx_destroy(prg->south_img, prg->mlx);
    run_mlx_destroy(prg->west_img, prg->mlx);
    run_mlx_destroy(prg->east_img, prg->mlx);

}

#else

void destroy_img(t_prg *prg)
{
    run_mlx_destroy(prg->img, prg->mlx);
    run_mlx_destroy(prg->north_img, prg->mlx);
    run_mlx_destroy(prg->south_img, prg->mlx);
    run_mlx_destroy(prg->west_img, prg->mlx);
    run_mlx_destroy(prg->east_img, prg->mlx);
    if (prg->mini_map)
        run_mlx_destroy(prg->mini_map->t_img, prg->mlx);
}

#endif