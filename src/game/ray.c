#include <cub3d.h>

void draw_ray(t_prg *p) 
{
    int dx = abs(RAY_END_X(p) - RAY_START_X(p)) * TILE_WIDTH;
    int dy = abs(RAY_END_Y(p) - RAY_START_Y(p)) * TILE_HEIGHT;
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
  RAY_START_X(prg) = PLAYER_CENTER_X(prg);
  RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
  RAY_DIRECTION_X(prg) = CAMARA_X(prg);
  RAY_DIRECTION_Y(prg) = CAMARA_Y(prg);
  RAY_END_X(prg) = RAY_START_X(prg);
  RAY_END_Y(prg) = RAY_START_Y(prg);

  float deltaDistX = (RAY_DIRECTION_X(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_X(prg));
  float deltaDistY = (RAY_DIRECTION_Y(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_Y(prg));
  int x;
  int y;
  x = PLAYER_X(prg);
  y = PLAYER_Y(prg); 

  double sideDistX;
  double sideDistY;

  int stepX;
  int stepY;
  int mapX = PLAYER_X(prg);
  int mapY = PLAYER_Y(prg);
  if(RAY_DIRECTION_X(prg) < 0)
  {
    stepX = -1;
    sideDistX = (PLAYER_X(prg) - mapX) * deltaDistX;
  }
  else
  {
    stepX = 1;
    sideDistX = (mapX + 1.0 - PLAYER_X(prg)) * deltaDistX;
  }
  if(RAY_DIRECTION_Y(prg) < 0)
  {
    stepY = -1;
    sideDistY = (PLAYER_Y(prg) - mapY) * deltaDistY;
  }
  else
  {
    stepY = 1;
    sideDistY = (mapY + 1.0 - PLAYER_Y(prg)) * deltaDistY;
  }
  int hit = 0;
  int side; 
  while(hit == 0)
  {
    //jump to next map square, either in x-direction, or in y-direction
    if(sideDistX < sideDistY)
    {
      sideDistX += deltaDistX;
      mapX += stepX;
      side = 0;
    }
    else
    {
      sideDistY += deltaDistY;
      mapY += stepY;
      side = 1;
    }
    //Check if ray has hit a wall
    if(prg->map[mapY][mapX] == '1') hit = 1;
  }

float perpWallDist;
        if(side == 0) 
        perpWallDist = fabs((mapX - PLAYER_X(prg) + (1 - stepX) / 2) / RAY_DIRECTION_X(prg)) ; //(sideDistX - deltaDistX); //
      else          
        perpWallDist = fabs((mapY - PLAYER_Y(prg) + (1 - stepY) / 2) / RAY_DIRECTION_Y(prg)); //(sideDistY - deltaDistY); //

  if (deltaDistX == FLT_MAX)
  {
    RAY_END_X(prg) = PLAYER_CENTER_X(prg);
  }
  else
    RAY_END_X(prg) = sideDistX * TILE_WIDTH;
  
  
  if (deltaDistY == FLT_MAX)
  {
    RAY_END_Y(prg)  = PLAYER_CENTER_Y(prg);
  }
  else
    RAY_END_Y(prg) = sideDistY * TILE_WIDTH;
  draw_ray(prg);
   /* 
  while (is_inside_map(x,  y, prg) && \
        prg->map[y][x] != '1')
  {
    RAY_END_X(prg) += RAY_DIRECTION_X(prg);
    RAY_END_Y(prg) += RAY_DIRECTION_Y(prg);
    if (RAY_END_X(prg) % TILE_WIDTH == 0)
      x += RAY_DIRECTION_X(prg);
    if (RAY_END_Y(prg) % TILE_HEIGHT == 0)
      y += RAY_DIRECTION_Y(prg);
  }*/
}