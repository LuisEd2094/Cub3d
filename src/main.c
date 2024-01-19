/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:02 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:19:27 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#define mapWidth 24
#define mapHeight 24


#include <math.h>



/*	int		i;
	float	x;
	float	y;
	float	x1, y1;
	float	x2, y2, dx, dy, step;

	x1 = 1;
	y1 = 1;
	x2 = 3;
	y2 = 4;

	dx = x2 - x1;
	dy = y2 - y1;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x1;
	y = y1;
	i = 0;
	while (i <= step)
	{
		printf("%d - x: %f, y: %f\n", i, x, y);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}*/

void draw_walls(t_prg *prg)
{
 /*int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {3,0,0,0,0,0,1,2,2,2,2,0,0,0,0,1,1,1,1,1,0,0,0,4},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,4,0,0,0,4,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,3,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/

    for(int x = 0; x < w; x++)
    {
    double posX = PLAYER_X(prg), posY = PLAYER_Y(prg);  //x and y start position
    double dirX = prg->camara_x, dirY = prg->camara_y; //initial direction vector

    //dir x 0 y -1 up
    //x 0 y 1 down
    // dirX = 1, dirY = 0;right
    // dirX = -1, dirY = 0;left
      // i think plany X and Y change depending on where you are looking at
      double planeX = prg->plane_x, planeY = prg->plane_y; //the 2d raycaster version of camera plane
      //plane X has to be - for SOUTH VIEW, plane Y has to be -Negative for west view

      double time = 0; //time of current frame
      double oldTime = 0; //time of previous frame
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
      //which box of the map we're in
      int mapX = (int)(posX);
      int mapY = (int)(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      //these are derived as:
      //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
      //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
      //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      //unlike (dirX, dirY) is not 1, however this does not matter, only the
      //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      //stepping further below works. So the values can be computed as below.
      // Division through zero is prevented, even though technically that's not
      // needed in C++ with IEEE 754 floating point values.
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

      printf("RayX %f RayY %f\n", rayDirX, rayDirY);

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
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
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0) 
        perpWallDist = fabs((mapX - posX + (1 - stepX) / 2) / rayDirX) ; //(sideDistX - deltaDistX); //
      else          
        perpWallDist = fabs((mapY - posY + (1 - stepY) / 2) / rayDirY); //(sideDistY - deltaDistY); //

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -(lineHeight / 2) + (h / 2);
      if(drawStart < 0) drawStart = 0;
      int drawEnd = (lineHeight / 2 )+( h / 2);
      if(drawEnd >= h) drawEnd = h - 1;

      //choose wall color
    int wallColor;
    switch (prg->map[mapY][mapX])
    {
    case '1':
        wallColor = 0xFF0000; // Red for walls
        break;
    case '2':
        wallColor = 0x00FF00; // Green for different walls
        break;
    case '3':
        wallColor = 0x0000FF; // Blue for other walls
        break;
    case '4':
        wallColor = 0xFFFFFF; // White for another type of wall
        break;
    case '5':
        wallColor = 0xFFFF00; // Yellow for yet another type of wall
        break;
    default:
        wallColor = 0x2F4F4F; // Default color for unknown values
        break;
    }

      //give x and y sides different brightness
    for (int y = drawStart; y <= drawEnd; y++)
    {
        mlx_pixel_put(prg->mlx->ptr, prg->mlx->window, x, y, wallColor);
    }
  }
 }

int	main(int argc, char *argv[])
{
	t_prg	prg;

  init_prg(&prg);
  if (argc != 2)
      exit_error(INCORRECT_USE, &prg);
  validate_map(argv[1], &prg);
  prg.mlx->ptr = mlx_init();
  if (!prg.mlx->ptr)
    exit_error(NULL, &prg);
  prg.mlx->window = mlx_new_window(prg.mlx->ptr, w, h, "cub3d");
  if (!prg.mlx->window)
  {
    //free_mlx(prg->mlx); Should check mlx elemtns, imgs and stuff and free them;
    exit_error(NULL, &prg);
  }
  /*prg.plane_x = 0;
  prg.plane_y = -0.66;*/
  get_hooks(&prg); 

  //draw_walls(&prg);
  draw_map(&prg);
  mlx_loop(prg.mlx->ptr);


  exit_success(&prg);
}
