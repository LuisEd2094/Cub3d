#include <cub3d.h>

int open_door(t_prg *prg)
{
    int map_x;
    int map_y;

    HIT_BOX_ANGLE(prg) = atan2(CAMARA_Y(prg), CAMARA_X(prg));
    map_x = (PLAYER_CENTER_X(prg) + /*(DOORS_PIXELS * 1)*/32 * cos(HIT_BOX_ANGLE(prg))) / TILE_SIZE;
    map_y = (PLAYER_CENTER_Y(prg) + /*(DOORS_PIXELS * 1)*/32 * sin(HIT_BOX_ANGLE(prg))) / TILE_SIZE;

    if (map_y == (int)PLAYER_Y(prg) && map_x == (int)PLAYER_X(prg))
        return (0);
    if (MAP(prg)[map_y][map_x] == '2')
        MAP(prg)[map_y][map_x] = '3';
    else if (MAP(prg)[map_y][map_x] == '3')
        MAP(prg)[map_y][map_x] = '2';
    update_window(prg);
    return (0);
}