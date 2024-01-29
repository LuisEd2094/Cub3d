#include <cub3d.h>


#define ANSI_RESET "\x1b[0m"
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_MAGNETA "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"


void draw_ray(t_prg *prg) 
{
	RAY_START_X(prg) = PLAYER_CENTER_X(prg);
	RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
	if (prg->ray->side == 0) // If the ray hit a vertical wall
	{
		RAY_END_Y(prg) = (int)(( PLAYER_Y(prg) + prg->ray->wallDist * prg->ray->rayDirY) * TILE_SIZE) ;
		RAY_END_X(prg) = (prg->ray->mapX) * TILE_SIZE; // I think you need to check the dirction for this
		if (prg->ray->rayDirX < 0)
			RAY_END_X(prg) += TILE_SIZE;
	}
	else // If the ray hit a horizontal wall
	{
		RAY_END_X(prg) = (int)((PLAYER_X(prg) + prg->ray->wallDist * prg->ray->rayDirX) * TILE_SIZE);
		RAY_END_Y(prg) = (prg->ray->mapY) * TILE_SIZE;
		if (prg->ray->rayDirY < 0)
			RAY_END_Y(prg) += TILE_SIZE;
	}
    int dx = abs(RAY_END_X(prg) - RAY_START_X(prg)) * TILE_SIZE;
    int dy = abs(RAY_END_Y(prg) - RAY_START_Y(prg)) * TILE_SIZE;
    int sx = (RAY_START_X(prg) < RAY_END_X(prg)) ? 1 : -1;
    int sy = (RAY_START_Y(prg) < RAY_END_Y(prg)) ? 1 : -1;
    int err = dx - dy;
	char *pixel; 


    while (1) {
        //mlx_pixel_put(MLX_PTR(prg), MLX_WIN(prg), RAY_START_X(prg), RAY_START_Y(prg), 0x0000FF);
      	pixel = prg->mini_map->t_img->addr + (RAY_START_Y(prg) * prg->mini_map->t_img->line_length + RAY_START_X(prg) * (prg->mini_map->t_img->bpp / 8));  
		*(unsigned int*)pixel = 0x0000FF;

        if (RAY_START_X(prg) == RAY_END_X(prg) && RAY_START_Y(prg) == RAY_END_Y(prg))
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            RAY_START_X(prg) += sx;
        }
        if (e2 < dx) {
            err += dx;
            RAY_START_Y(prg) += sy;
        }
    }
}