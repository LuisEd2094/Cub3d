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
    if(prg->map[mapY][mapX] == '1') hit = 1;
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
}