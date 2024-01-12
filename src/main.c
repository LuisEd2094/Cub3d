#include <cub3d.h>
#define mapWidth 24
#define mapHeight 24
#define w 600
#define h 400

#include <math.h>

 int worldMap[mapWidth][mapHeight]=
{
  {1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
  {3,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
};


void draw_walls(t_prg *prg)
{
    double posX = 5, posY = 3;  //x and y start position
    double dirX = 1, dirY = 0; //initial direction vector

    //dir x 0 y -1 up
    //x 0 y 1 down
    // dirX = 1, dirY = 0;right
    // dirX = -1, dirY = 0;left

    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    //planeY  closer to 0, more to up
    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame
    for(int x = 0; x < w; x++)
    {
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
      double deltaDistX = (rayDirX == 0) ? 1e30 : abs(1 / rayDirX);
      double deltaDistY =  (rayDirY == 0) ? 1e30 : abs(1 / rayDirY);

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
    while (hit == 0)
    {
        // Jump to the next map square, either in x-direction or y-direction
        if (sideDistX < sideDistY)
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

        // Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0)
            hit = 1;
    }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
     //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
if(side == 0) perpWallDist = fabs((mapX - posX + (1 - stepX) / 2) / rayDirX);
else          perpWallDist = fabs((mapY - posY + (1 - stepY) / 2) / rayDirY);

      //Calculate height of line to draw on screen
    int lineHeight = (int)(h / perpWallDist);

    // Apply a scaling factor based on the distance to the wall
    lineHeight = (lineHeight > h) ? h : lineHeight; // Clamp the line height

    // Calculate starting and ending pixel positions for the wall slice
    int drawStart = -lineHeight / 2 + h / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + h / 2;
    if (drawEnd >= h) drawEnd = h - 1;

      //choose wall color
    int wallColor;
    switch (worldMap[mapY][mapX])
    {
    case 1:
        wallColor = 0xFF0000; // Red for walls
        break;
    case 2:
        wallColor = 0x00FF00; // Green for different walls
        break;
    case 3:
        wallColor = 0x0000FF; // Blue for other walls
        break;
    case 4:
        wallColor = 0xFFFFFF; // White for another type of wall
        break;
    case 5:
        wallColor = 0xFFFF00; // Yellow for yet another type of wall
        break;
    default:
        wallColor = 0x2F4F4F; // Default color for unknown values
        break;
    }
      if(side == 1) {wallColor = wallColor / 2;}

      //give x and y sides different brightness
    for (int y = drawStart; y <= drawEnd; y++)
    {
        mlx_pixel_put(prg->mlx->ptr, prg->mlx->window, x, y, wallColor);
    }
  }
 }

int main(int argc, char *argv[])
{
    t_prg prg;

    init_prg(&prg);
    if (argc != 2)
        exit_error(INCORRECT_USE, &prg);
    validate_map(argv[1], &prg);
    for (int i = 0; i < 3; i++)
        ft_printf(1, "RGB >%i<\n", prg.floor_vals[i]);
    for (int i = 0; i < 3; i++)
        ft_printf(1, "RGB >%i<\n", prg.ceiling_vals[i]);
    ft_printf(1, "VALID MAP\n");


    prg.mlx->ptr = mlx_init();
    if (!prg.mlx->ptr)
	{
		exit_success(&prg);
        ft_printf(1, "HELLO");

	}
    prg.mlx->window = mlx_new_window(prg.mlx->ptr, w, h, "cub3d"); 
    draw_walls(&prg);


	mlx_loop(prg.mlx->ptr);


    exit_success(&prg);
}