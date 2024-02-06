//# PLAYER MACROS

// MLX MACROS
#define MLX_PTR(prg) (prg->mlx->ptr)
#define MLX_WIN(prg) (prg->mlx->window)
#define MAP(prg) (prg->map)

//CAMARA MACROS
#define CAMARA_X(prg) (prg->camara_x)
#define CAMARA_Y(prg) (prg->camara_y)

// MAP MACROS
#define MAP_IMG(prg) (prg->mini_map.t_img.img)
#define MAP_ENDIAN(prg) (prg->mini_map.t_img.endian)
//#define (prg->mini_map.t_img.addr) + (y * prg->mini_map.t_img.line_length + x * (prg->mini_map.t_img.bpp / 8)) ((prg->mini_map.t_img.addr) + (y * prg->mini_map.t_img.line_length + x * (prg->mini_map.t_img.bpp / 8)))
/* #define (prg->map_w + 1) * TILE_SIZE ((prg->map_w + 1) * TILE_SIZE)
#define (prg->map_h) * TILE_SIZE ((prg->map_h) * TILE_SIZE) */
/* #define prg->mini_map.max_w (prg->mini_map.max_w)
#define prg->mini_map.max_h (prg->mini_map.max_h)
#define prg->mini_map.x_pos (prg->mini_map.x_pos)
#define prg->mini_map.y_pos (prg->mini_map.y_poss) */
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
