#include <cub3d.h>


#define ANSI_RESET "\x1b[0m"
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_MAGNETA "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"


void draw_ray(t_prg *p) 
{
    int dx = abs(RAY_END_X(p) - RAY_START_X(p)) * TILE_SIZE;
    int dy = abs(RAY_END_Y(p) - RAY_START_Y(p)) * TILE_SIZE;
    int sx = (RAY_START_X(p) < RAY_END_X(p)) ? 1 : -1;
    int sy = (RAY_START_Y(p) < RAY_END_Y(p)) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(MLX_PTR(p), MLX_WIN(p), RAY_START_X(p), RAY_START_Y(p), 0x0000FF);

        if (RAY_START_X(p) == RAY_END_X(p) && RAY_START_Y(p) == RAY_END_Y(p))
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            RAY_START_X(p) += sx;
        }
        if (e2 < dx) {
            err += dx;
            RAY_START_Y(p) += sy;
        }
    }
}

void	init_dda_map(t_prg *prg)
{
	if (prg->ray->rayDirX < 0)
	{
		prg->ray->stepX = -1;
		prg->ray->sideDistX = (PLAYER_X(prg) - prg->ray->mapX) * prg->ray->deltaDistX;
	}
	else
	{
		prg->ray->stepX = 1;
		prg->ray->sideDistX = (prg->ray->mapX + 1.0 - PLAYER_X(prg)) * prg->ray->deltaDistX;
	}
	if (prg->ray->rayDirY < 0)
	{
		prg->ray->stepY = -1;
		prg->ray->sideDistY = (PLAYER_Y(prg) - prg->ray->mapY) * prg->ray->deltaDistY;
	}
	else
	{
		prg->ray->stepY = 1;
		prg->ray->sideDistY = (prg->ray->mapY + 1.0 - PLAYER_Y(prg)) * prg->ray->deltaDistY;
	}
}

void	perform_dda_map(t_prg *prg)
{
	while (prg->ray->hit == 0)
	{
		if (prg->ray->sideDistX < prg->ray->sideDistY)
		{
			prg->ray->sideDistX += prg->ray->deltaDistX;
			prg->ray->mapX += prg->ray->stepX;
			prg->ray->side = 0;
		}
		else
		{
			prg->ray->sideDistY += prg->ray->deltaDistY;
			prg->ray->mapY += prg->ray->stepY;
			prg->ray->side = 1;
		}
		if (prg->ray->mapY < 0.25
			|| prg->ray->mapX < 0.25
			|| prg->ray->mapY > prg->map_h - 0.25
			|| prg->ray->mapX > prg->map_w - 0.25)
			break ;
		if (prg->map[prg->ray->mapY][prg->ray->mapX] == '1')
			prg->ray->hit = 1;
	}
}

void	cast_ray(t_prg *prg)
{

	for (int i = 0; i < w; i++)
	{
		RAY_START_X(prg) = PLAYER_CENTER_X(prg);
		RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
		prg->ray->camera = 2 * i / (double)w - 1;
		prg->ray->rayDirX = prg->camara_x + prg->plane_x * prg->ray->camera;
		prg->ray->rayDirY = prg->camara_y + prg->plane_y * prg->ray->camera;
		prg->ray->mapX = (int)PLAYER_X(prg);
		prg->ray->mapY = (int)PLAYER_Y(prg);
		prg->ray->hit = 0;
		if (prg->ray->rayDirX == 0)
			prg->ray->deltaDistX = FLT_MAX;
		else
			prg->ray->deltaDistX = fabs(1 / prg->ray->rayDirX);
		if (prg->ray->rayDirY == 0)
			prg->ray->deltaDistY = FLT_MAX;
		else
			prg->ray->deltaDistY = fabs(1 / prg->ray->rayDirY);
		init_dda_map(prg);
		perform_dda_map(prg);
		if (prg->ray->side == 0)
			prg->ray->wallDist = prg->ray->sideDistX - prg->ray->deltaDistX;
		else
			prg->ray->wallDist = prg->ray->sideDistY - prg->ray->deltaDistY;
		ray_to_img(prg, i);

		if (prg->ray->deltaDistX == FLT_MAX)
		{
		prg->ray->sideDistX = 0;
		}
		if (prg->ray->deltaDistY == FLT_MAX)
		{
		prg->ray->sideDistY = 0;
		}

  		printf("map x%i map y %i\n", prg->ray->mapX, prg->ray->mapY);
		if (prg->ray->side == 0) // If the ray hit a vertical wall
		{
			RAY_END_Y(prg) = (int)(( PLAYER_Y(prg) + prg->ray->wallDist * prg->ray->rayDirY) * TILE_SIZE) ;
      		RAY_END_X(prg) = (prg->ray->mapX) * TILE_SIZE; // I think you need to check the dirction for this
			if (prg->ray->rayDirX < 0)
				RAY_END_X(prg) += TILE_SIZE;
			printf(" vertical wall X %d Y %d\n",RAY_END_X(prg) ,RAY_END_Y(prg));

		}
		else // If the ray hit a horizontal wall
		{
			RAY_END_X(prg) = (int)((PLAYER_X(prg) + prg->ray->wallDist * prg->ray->rayDirX) * TILE_SIZE);
      		RAY_END_Y(prg) = (prg->ray->mapY) * TILE_SIZE;
			if (prg->ray->rayDirY < 0)
				RAY_END_Y(prg) += TILE_SIZE;
			printf(" horizontal wall X %d y %d\n", RAY_END_X(prg) ,RAY_END_Y(prg));

    }
		printf("\tnew ray\n");
    draw_ray(prg);
	}
}
