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

int is_inside_map(int x, int y, t_prg *prg) {
    return (y >= 0 && y < prg->map_h && x >= 0 && x < ft_strlen(prg->map[y]));
}

void cast_ray(t_prg *prg)
{  
  //for (int i = 0; i < w; ++i){
  
  RAY_START_X(prg) = PLAYER_CENTER_X(prg);
  RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
  RAY_DIRECTION_X(prg) = CAMARA_X(prg);// + prg->plane_x * (2 * i  / (double)w - 1);
  RAY_DIRECTION_Y(prg) = CAMARA_Y(prg);//+ prg->plane_y * (2 * i  / (double)w - 1);
  RAY_END_X(prg) = RAY_START_X(prg);
  RAY_END_Y(prg) = RAY_START_Y(prg);

  RAY_DELTA_X(prg) = (RAY_DIRECTION_X(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_X(prg)) ;
  RAY_DELTA_Y(prg) = (RAY_DIRECTION_Y(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_Y(prg)) ;

  double sideDistX;
  double sideDistY;

  RAY_STEP_X(prg);
  RAY_STEP_Y(prg);
  int mapX = PLAYER_X(prg);
  int mapY = PLAYER_Y(prg);

  if(RAY_DIRECTION_X(prg) < 0)
  {
    RAY_STEP_X(prg) = -1;
    sideDistX = ((PLAYER_X(prg) - mapX) * RAY_DELTA_X(prg));
  }
  else
  {
    RAY_STEP_X(prg) = 1;
    sideDistX = ((mapX + 1.0 - PLAYER_X(prg)) * RAY_DELTA_X(prg));
  }
  if(RAY_DIRECTION_Y(prg) < 0)
  {
    RAY_STEP_Y(prg) = -1;
    sideDistY = (PLAYER_Y(prg) - mapY) * RAY_DELTA_Y(prg);
  }
  else
  {
    RAY_STEP_Y(prg) = 1;
    sideDistY = (mapY + 1.0 - PLAYER_Y(prg)) * RAY_DELTA_Y(prg);
  }

  int hit = 0;
  int side; 

  // DDA 
  while(hit == 0)
  {
    if(fabs(sideDistX) < fabs(sideDistY))
    {
      sideDistX += RAY_DELTA_X(prg);
      mapX += RAY_STEP_X(prg);
      side = 1;
    }
    else
    {
      sideDistY += RAY_DELTA_Y(prg);
      mapY += RAY_STEP_Y(prg);
      side = 0;
    }
    if(prg->map[mapY][mapX] == '1' || prg->map[mapY][mapX] == '2') hit = 1;
  }


  double perpWallDist;
  if(side == 0) 
    perpWallDist = fabs((mapX - PLAYER_X(prg) + (1 - RAY_STEP_X(prg)) / 2) / RAY_DIRECTION_X(prg)) ; //(sideDistX - RAY_DELTA_X(prg)); //
  else          
    perpWallDist = fabs((mapY - PLAYER_Y(prg) + (1 - RAY_STEP_Y(prg)) / 2) / RAY_DIRECTION_Y(prg)); //(sideDistY - RAY_DELTA_Y(prg)); //



    if (RAY_DELTA_X(prg) == FLT_MAX)
    {
      sideDistX = 0;
    }
    if (RAY_DELTA_Y(prg) == FLT_MAX)
    {
      sideDistY = 0;
    }
  double offset = fabs(fabs(sideDistX) - fabs(sideDistY));
if (side)
{
  if (sideDistX < 0)
    sideDistX += 1;
  else
    sideDistX -= 1;
  if (sideDistY > 0)
  {
    sideDistY += offset - 1 ;
  }
  else
  {
    sideDistY += 1 - offset;

  }
}
else
{
  if (sideDistY < 0)
    sideDistY += 1;
  else
    sideDistY -= 1;
  if (sideDistX > 0)
  {
    sideDistX += offset - 1 ;
  }
  else
  {
    sideDistX += 1 - offset;

  }
}

  if (RAY_DELTA_X(prg) == FLT_MAX)
  {
    RAY_END_X(prg) = PLAYER_CENTER_X(prg);
  }
  else
    RAY_END_X(prg) = PLAYER_CENTER_X(prg) + (sideDistX * TILE_SIZE);
  
  
  if (RAY_DELTA_Y(prg) == FLT_MAX)
  {
    RAY_END_Y(prg)  = PLAYER_CENTER_Y(prg);
  }
  else
    RAY_END_Y(prg) = PLAYER_CENTER_Y(prg) + (sideDistY * TILE_SIZE);
  draw_ray(prg);
  printf("%f\n", offset);
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
/*
void	cast_ray(t_prg *prg)
{
  RAY_START_X(prg) = PLAYER_CENTER_X(prg);
  RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
	for (int i = 0; i < w; i++)
	{
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

double offset = fabs(fabs(prg->ray->sideDistX) - fabs(prg->ray->deltaDistY));
if (prg->ray->side)
{
  if (prg->ray->sideDistX < 0)
    prg->ray->sideDistX += 1;
  else
    prg->ray->sideDistX -= 1;
  if (prg->ray->deltaDistY > 0)
  {
    prg->ray->deltaDistY += offset - 1 ;
  }
  else
  {
    prg->ray->deltaDistY += 1 - offset;

  }
}
else
{
  if (prg->ray->deltaDistY < 0)
    prg->ray->deltaDistY += 1;
  else
    prg->ray->deltaDistY -= 1;
  if (prg->ray->sideDistX > 0)
  {
    prg->ray->sideDistX += offset - 1 ;
  }
  else
  {
    prg->ray->sideDistX += 1 - offset;

  }
}

  if (RAY_DELTA_X(prg) == FLT_MAX)
  {
    RAY_END_X(prg) = PLAYER_CENTER_X(prg);
  }
  else
    RAY_END_X(prg) = PLAYER_CENTER_X(prg) + (prg->ray->sideDistX * TILE_SIZE);
  
  
  if (RAY_DELTA_Y(prg) == FLT_MAX)
  {
    RAY_END_Y(prg)  = PLAYER_CENTER_Y(prg);
  }
  else
    RAY_END_Y(prg) = PLAYER_CENTER_Y(prg) + (prg->ray->deltaDistY * TILE_SIZE);
  draw_ray(prg);
	}
}
*/