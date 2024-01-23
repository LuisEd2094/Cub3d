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

  float deltaDistX = (RAY_DIRECTION_X(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_X(prg)) ;
  float deltaDistY = (RAY_DIRECTION_Y(prg) == 0) ? FLT_MAX : floor(1 / RAY_DIRECTION_Y(prg)) ;
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
    sideDistX = ((PLAYER_X(prg) - mapX) * deltaDistX);
  }
  else
  {
    stepX = 1;
    sideDistX = ((mapX + 1.0 - PLAYER_X(prg)) * deltaDistX);
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
float perpWallDist;
  if(side == 0) 
  perpWallDist = fabs((mapX - PLAYER_X(prg) + (1 - stepX) / 2) / RAY_DIRECTION_X(prg)) ; //(sideDistX - deltaDistX); //
  else          
  perpWallDist = fabs((mapY - PLAYER_Y(prg) + (1 - stepY) / 2) / RAY_DIRECTION_Y(prg)); //(sideDistY - deltaDistY); //





  if (deltaDistX == FLT_MAX)
  {
    og_side_distx = og_side_disty;
    sideDistX = 0;
  }

  if (deltaDistY == FLT_MAX)
    {
      og_side_disty = og_side_distx;
      sideDistY = 0;
    }
  /*  if (side)
  {
    if (sideDistX > 0)
      sideDistX -= 1;
    else if (sideDistX < 0)
      sideDistX += 1;
    if (sideDistY > 0)
      sideDistY -= 1; 
  }
  else
  {
    if (sideDistY < 0)
      sideDistY += 1;
    else if (sideDistY > 0 )
      sideDistY -= 1;
    if (sideDistX > 0)
      sideDistX -= 1;
  }*/

 float new_dist_x = fabs(sideDistX);
 float new_dist_y = fabs(sideDistY);
float length = sqrt((new_dist_x - PLAYER_X(prg)) * (new_dist_x - PLAYER_X(prg)) +
                        (new_dist_y - PLAYER_Y(prg)) * (new_dist_y - PLAYER_Y(prg)));
  printf("length = %f\n", length);
  printf(ANSI_GREEN "new_dist_x t%f y new_dist_y pos  %f" ANSI_RESET, new_dist_x, new_dist_y);
  printf("DISTANCE = %f\n", perpWallDist);
  printf(ANSI_YELLOW "MAP X %i map Y %i\n" ANSI_RESET, mapX, mapY);

  printf(ANSI_BLUE "%F DISTANCE SUMS %f \n" ANSI_RESET, perpWallDist, perpWallDist - (og_side_distx));
  printf(ANSI_GREEN "SIDE X %f SIDE Y %f \n" ANSI_RESET, sideDistX * 64, sideDistY * 64);
  printf(ANSI_GREEN "SIDE X - SIDE Y %f \n" ANSI_RESET, fabs(fabs(sideDistX) * 64 - fabs(sideDistY) * 64));

  printf(ANSI_MAGNETA "OG SIDE X %f OG SIDE Y %f \n" ANSI_RESET, og_side_distx, og_side_disty);
  printf(ANSI_CYAN "ADDITION %f SUBSTRACTION X %f\nABSOLUTE SUB %f ABSOLUTE SUM %f \n" ANSI_RESET, og_side_distx + og_side_disty, og_side_distx - og_side_disty, fabs(fabs(og_side_distx) - fabs(og_side_disty)), fabs(fabs(og_side_distx) + fabs(og_side_disty)));



  double offset = 0;
  if ((fabs(og_side_distx) > 0 && fabs(og_side_distx) < 1) && fabs(og_side_disty) > 0 && fabs(og_side_disty) < 1)
  {
      if (fabs(og_side_distx) > fabs(og_side_disty))
    offset = fabs(og_side_distx + og_side_disty);
  else
      offset = fabs(og_side_disty + og_side_distx);

  }

  printf(ANSI_MAGNETA "OFFSET  %f \n" ANSI_RESET,  offset);
/*
  if (side)
  {
    if (sideDistX < 0)
      sideDistX += 1;
    else
      sideDistX -= 1;
  }
  else
  {
    if (sideDistY > 0)
      sideDistY -= 1;
    else if (sideDistY < 0)
      sideDistY += 1;
    if (offset > 0.0 && offset < 1.0)
    {
      if (offset > 0.0 && offset < 1.0)
      {

      if (og_side_distx > 0) //right  
      {
        double x_correction = 1 - offset;
        if (og_side_disty > 0)
        {
          printf("correction %f\n", x_correction); 

          if (x_correction >= 0.5 && og_side_distx <= 0.5) 
          {
            sideDistX -= x_correction;
            printf("%f\n",x_correction ); 

          }
          else
          {
            sideDistX -= 1 - x_correction;
          }
        }
        else 
            printf("%f\n", x_correction + 0.5);

        
        if (sideDistY > 0) //riight down
        {
          if (og_side_distx >= 0.0 && og_side_distx <= 0.5)
            sideDistX -= 1  - offset;
          else
            sideDistX -= offset;
        }
        else //right up
        {
            printf("right up%f \n", 0.5 + offset);

          if (og_side_distx >= 0.0 && og_side_distx <= 0.5)
            sideDistX -= 1 - offset;
          else
            sideDistX -= offset;
        }


      }
    }
        
      }


  }*/
  printf(ANSI_YELLOW "PLAYER X %f PLAYER Y %f \n" ANSI_RESET, 0.5 - og_side_distx, 0.5 - og_side_disty);

  printf(ANSI_GREEN "BEFORE RAY SIDE X %f SIDE Y %f \n" ANSI_RESET, sideDistX, sideDistY);


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
  printf("%i side\n", side);
  printf("\n\n");

  draw_ray(prg);
}