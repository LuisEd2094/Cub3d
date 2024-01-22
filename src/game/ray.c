#include <cub3d.h>


#define ANSI_RESET "\x1b[0m"
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
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

  double og_side_disty = sideDistY;
  double og_side_distx = sideDistX;
  printf("side X before %f side Y before%f\n", sideDistX, sideDistY);

  int hit = 0;
  int side; 
  while(hit == 0)
  {
    //jump to next map square, either in x-direction, or in y-direction
    if(fabs(sideDistX) < fabs(sideDistY))
    {
      sideDistX += deltaDistX;
      mapX += stepX;
      side = 1;
    }
    else
    {
      sideDistY += deltaDistY;
      mapY += stepY;
      side = 0;
    }
    //Check if ray has hit a wall
    if(prg->map[mapY][mapX] == '1') hit = 1;
  }
  printf(ANSI_BLUE "max X %i map Y %i \n" ANSI_RESET, mapX, mapY);
float perpWallDist;
  if(side == 0) 
  perpWallDist = fabs((mapX - PLAYER_X(prg) + (1 - stepX) / 2) / RAY_DIRECTION_X(prg)) ; //(sideDistX - deltaDistX); //
  else          
  perpWallDist = fabs((mapY - PLAYER_Y(prg) + (1 - stepY) / 2) / RAY_DIRECTION_Y(prg)); //(sideDistY - deltaDistY); //

  if (deltaDistX == FLT_MAX)
    og_side_distx = og_side_disty;

  if (deltaDistY == FLT_MAX)
    og_side_disty = og_side_distx;
  if (side)
  {
    if (sideDistX < 0)
      sideDistX += 1;
  }
  else
  {
    if (sideDistY > 0)
      sideDistY -= 1;
    else if (sideDistY < 0)
      sideDistY += 1;
    if (sideDistX < 0 )
    {
      if (sideDistY < 0)
      {
        if (og_side_distx > og_side_disty)
          sideDistX +=  fabs(og_side_disty + og_side_distx);
        else
          sideDistX +=  fabs(og_side_disty - og_side_distx);
      }
      else
      {
        if (fabs(og_side_distx) < og_side_disty)
        {
          printf("i am here\n");
          sideDistX += 1 - (og_side_disty + og_side_distx);
        }
        else
          sideDistX +=  fabs(og_side_disty + og_side_distx);


      }

    }


    printf("plust =  %f minus = %f\n", (og_side_disty + og_side_distx), og_side_disty - og_side_distx);
  }

  /*printf("side X After %f side Y After %f\n", sideDistX, sideDistY);

  if (side)
  {
    if (deltaDistY == FLT_MAX)
      og_side_disty = og_side_distx;
   if (fabs(og_side_disty) > fabs(og_side_distx))
      sideDistY += fabs(og_side_distx) - fabs(og_side_disty);
    else
      sideDistY += (og_side_distx) - (og_side_disty);

    if (sideDistX > 0) 
      sideDistX -= 1.0;
    else
      sideDistX += 1.0;
    printf(ANSI_RED  "%f og_side_distx %f og_side_disty\n" ANSI_RESET , og_side_distx,  og_side_disty);

    printf(ANSI_RED  "%f og_side_distx - og_side_disty\n" ANSI_RESET , og_side_distx - og_side_disty);
  }
  else
  {
    if (deltaDistX == FLT_MAX)
      og_side_distx = og_side_disty;
    if (sideDistY > 0)
      sideDistY -= 1.0 ;
    else
      sideDistY += 1.0 ;
    printf("%f side X PRE FABS\n", sideDistX);

    if (fabs(og_side_disty - og_side_distx) <= 1.0)
    {
      printf("I AM HERE %f \n", 1 + (og_side_disty - og_side_distx));
      sideDistX += (1 + (og_side_disty - og_side_distx)) - 1;

    }
    else
    {
            printf("THIS IS FABS HERE %f \n", fabs(og_side_disty - og_side_distx) - 2);

      sideDistX += fabs(og_side_disty - og_side_distx) - 2; 

    }
    printf("side X FABS %f side Y FABs %f\n", sideDistX, sideDistY);

    printf(ANSI_GREEN  "%f og_side_disty %f og_side_distx\n" ANSI_RESET, og_side_disty , og_side_distx);

    printf(ANSI_GREEN  "%f og_side_disty - og_side_distx %f fabs \n" ANSI_RESET, og_side_disty - og_side_distx, fabs(og_side_disty - og_side_distx));

  }

    printf("%f ogX  %f ogY\n", og_side_distx, og_side_disty);

  printf("side X Pre Ray %f side Y Pre ray %f\n", sideDistX, sideDistY);*/



  if (deltaDistX == FLT_MAX)
  {
    RAY_END_X(prg) = PLAYER_CENTER_X(prg);
  }
  else
    RAY_END_X(prg) = PLAYER_CENTER_X(prg) + (sideDistX * TILE_WIDTH);
  
  
  if (deltaDistY == FLT_MAX)
  {
    RAY_END_Y(prg)  = PLAYER_CENTER_Y(prg);
  }
  else
    RAY_END_Y(prg) = PLAYER_CENTER_Y(prg) + (sideDistY * TILE_WIDTH);
  /*if (deltaDistY == FLT_MAX)
    sideDistY = 0;
  if (deltaDistX == FLT_MAX)
    sideDistX = 0;

    printf(ANSI_GREEN  "%f DIST X %f DIST Y\n" ANSI_RESET, sideDistX , sideDistY);
    printf(ANSI_GREEN  "%f DELTA X %f DELTA Y\n" ANSI_RESET, deltaDistX , deltaDistY);

if (side) {
    RAY_END_X(prg)  = PLAYER_CENTER_X(prg) + (sideDistX * TILE_WIDTH);
    RAY_END_Y(prg) = PLAYER_CENTER_Y(prg) + (sideDistY * TILE_WIDTH);
} else {
    RAY_END_X(prg) = PLAYER_CENTER_X(prg) + (sideDistX * TILE_WIDTH);
    RAY_END_Y(prg)  = PLAYER_CENTER_Y(prg) + (sideDistY * TILE_WIDTH);
}*/

  printf("%i side\n", side);
  draw_ray(prg);
}