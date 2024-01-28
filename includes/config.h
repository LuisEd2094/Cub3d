#ifndef CONFIG_H
# define CONFIG_H

#define w 800
#define h 600

# define TILE_SIZE	64
# define MINI_MAP_SIZE TILE_SIZE * 8

# define MOVE_SPEED 0.125
# define DOORS_PIXELS (TILE_SIZE / 4)
# define MOVE_PIXELS (TILE_SIZE * (MOVE_SPEED) +  (TILE_SIZE * (MOVE_SPEED / 2))) // I want to use ints since those operations are cheaper
# define HIT_BOX    MOVE_SPEED * 2
# define ROTATION_ANGLE 45

#endif