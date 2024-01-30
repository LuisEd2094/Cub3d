#include <cub3d.h>

void    set_up_ray_values(t_prg *prg)
{
    RAY_START_X(prg) = PLAYER_CENTER_X(prg);
	RAY_START_Y(prg) = PLAYER_CENTER_Y(prg);
    MAP_DX(prg) = abs(RAY_END_X(prg) - RAY_START_X(prg)) * TILE_SIZE;
    MAP_DY(prg) = abs(RAY_END_Y(prg) - RAY_START_Y(prg)) * TILE_SIZE;
    if (RAY_START_X(prg) < RAY_END_X(prg))
        MAP_SX(prg) = 1;
    else
        MAP_SX(prg) = -1;
    if (RAY_START_Y(prg) < RAY_END_Y(prg))
        MAP_SY(prg) = 1;
    else
        MAP_SY(prg) = -1;
    MAP_ERR(prg) = MAP_DX(prg) - MAP_DY(prg);

}
void draw_ray(t_prg *prg) 
{
    set_up_ray_values(prg);
    while (1) 
    {
      	MAP_PIXEL(prg) = MAP_GET_PIXEL(prg, RAY_START_X(prg), RAY_START_Y(prg));  
		*(unsigned int*)MAP_PIXEL(prg) = RGB_BLUE;
        if (RAY_START_X(prg) == RAY_END_X(prg) && RAY_START_Y(prg) == RAY_END_Y(prg))
            break;
        MAP_E2(prg) = 2 * MAP_ERR(prg);
        if (MAP_E2(prg) > -MAP_DY(prg)) {
            MAP_ERR(prg) -= MAP_DY(prg);
            RAY_START_X(prg) += MAP_SX(prg);
        }
        if (MAP_E2(prg) < MAP_DX(prg)) {
            MAP_ERR(prg) += MAP_DX(prg);
            RAY_START_Y(prg) += MAP_SY(prg);
        }
    }
}