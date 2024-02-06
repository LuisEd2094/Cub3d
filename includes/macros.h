//# PLAYER MACROS
#define PLAYER(prg) (prg->player)
#define PLAYER_X(prg) (prg->player->x)
#define PLAYER_Y(prg) (prg->player->y)
#define PLAYER_DIR_X(prg) (prg->player->dir->x)
#define PLAYER_DIR_Y(prg) (prg->player->dir->y)
#define PLAYER_LEFT_X(prg) (prg->player->left_corner->x)
#define PLAYER_LEFT_Y(prg) (prg->player->left_corner->y)
#define PLAYER_RIGHT_X(prg) (prg->player->right_corner->x)
#define PLAYER_RIGHT_Y(prg) (prg->player->right_corner->y)
#define PLAYER_CENTER(prg) (prg->player->center)
#define PLAYER_CENTER_X(prg) (prg->player->center->x)
#define PLAYER_CENTER_Y(prg) (prg->player->center->y)
#define PLAYER_ANGLE(prg) (prg->player->angle)
#define HIT_BOX_CENTER(prg) (prg->player->hit_box_center)
#define HIT_BOX_LEFT(prg)	(prg->player->hit_box_left)
#define HIT_BOX_RIGHT(prg)	(prg->player->hit_box_right)
#define HIT_BOX_ANGLE(prg) (prg->player->hit_box_angle)

//RAY MACROS
#define RAY_START_X(prg) (prg->ray->start->x)
#define RAY_START_Y(prg) (prg->ray->start->y)
#define RAY_END_X(prg) (prg->ray->end->x)
#define RAY_END_Y(prg) (prg->ray->end->y)
#define RAY_DIRECTION_X(prg) (prg->ray->dir_x)
#define RAY_DIRECTION_Y(prg) (prg->ray->dir_y)
#define RAY_DELTA_X(prg) (prg->ray->delta_dist_x)
#define RAY_DELTA_Y(prg) (prg->ray->delta_dist_y)
#define RAY_STEP_X(prg) (prg->ray->map_step_x)
#define RAY_STEP_Y(prg) (prg->ray->map_step_y)
#define RAY_DIST_X(prg) (prg->ray->side_dist_x)
#define RAY_DIST_Y(prg) (prg->ray->side_dist_y)
#define RAY_MAP_X(prg)	(prg->ray->map_x)
#define RAY_MAP_Y(prg)	(prg->ray->map_y)

// MLX MACROS
#define MLX_PTR(prg) (prg->mlx->ptr)
#define MLX_WIN(prg) (prg->mlx->window)
#define MAP(prg) (prg->map)

//CAMARA MACROS
#define CAMARA_X(prg) (prg->camara_x)
#define CAMARA_Y(prg) (prg->camara_y)

// MAP MACROS
#define MAP_IMG(prg) (prg->mini_map.t_img.img)
#define MAP_ADDR(prg) (prg->mini_map.t_img.addr)
#define MAP_BPP(prg) (prg->mini_map.t_img.bpp)
#define MAP_LINE(prg) (prg->mini_map.t_img.line_length)
#define MAP_ENDIAN(prg) (prg->mini_map.t_img.endian)
#define MAP_GET_PIXEL(prg, x,y) (MAP_ADDR(prg) + (y * MAP_LINE(prg) + x * (MAP_BPP(prg) / 8)))
#define MAP_W(prg) ((prg->map_w + 1) * TILE_SIZE)
#define MAP_H(prg) ((prg->map_h) * TILE_SIZE)
#define MAP_MAX_W(prg) (prg->mini_map.max_w)
#define MAP_MAX_H(prg) (prg->mini_map.max_h)
#define MAP_X(prg) (prg->mini_map.x_pos)
#define MAP_Y(prg) (prg->mini_map.y_pos)
#define MAP_DX(prg) (prg->mini_map.dx)
#define MAP_DY(prg) (prg->mini_map.dy)
#define MAP_SX(prg) (prg->mini_map.sx)
#define MAP_SY(prg) (prg->mini_map.sy)
#define MAP_ERR(prg) (prg->mini_map.err)
#define MAP_E2(prg) (prg->mini_map.e2)
#define MAP_PIXEL(prg) (prg->mini_map.pixel)
#define MAP_A_X(prg) (prg->mini_map.a.x)
#define MAP_B_X(prg) (prg->mini_map.b.x)
#define MAP_C_X(prg) (prg->mini_map.c.x)
#define MAP_A_Y(prg) (prg->mini_map.a.y)
#define MAP_B_Y(prg) (prg->mini_map.b.y)
#define MAP_C_Y(prg) (prg->mini_map.c.y)
