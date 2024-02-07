#include <cub3d_bonus.h>

void	copy_info_to_mini_map(t_map *mini_map, t_map_info *mini_map_info)
{
	mini_map->current_img = &(mini_map_info->map_img);
	mini_map->current_max_size =mini_map_info->max_size;
	mini_map->current_num_tiles = mini_map_info->num_tiles;
	mini_map->max_h = mini_map_info->max_h;
	mini_map->max_w = mini_map_info->max_w;
	mini_map->off_set_x = mini_map_info->off_set_x;
	mini_map->off_set_y = mini_map_info->off_set_y;
};


void    init_maps_img(t_prg *p, t_map_info *map, int size, int tiles)
{
    map->map_img.img = mlx_new_image(p->mlx.ptr, \
	ft_min(((p->map_w + 1) * TILE_SIZE), size), \
	ft_min((p->map_h) * TILE_SIZE, size));
	map->map_img.addr = mlx_get_data_addr(map->map_img.img, \
	&map->map_img.bpp, &map->map_img.line_length, \
	&map->map_img.endian);
	if (!map->map_img.addr)
		exit_error(NULL, p);
	map->max_w = ft_min((p->map_w + 1) * TILE_SIZE, size);
	map->max_h = ft_min((p->map_h) * TILE_SIZE, size);
	map->off_set_x = (p->map_w + 1) * TILE_SIZE > size;
	map->off_set_y = (p->map_h) * TILE_SIZE > size;
	map->max_size = size;
	map->num_tiles = tiles;
}

void	init_maps_values(t_prg *p)
{
    init_maps_img(p, &(p->mini_map_info), \
                MINI_MAP_SIZE, MAX_NUM_TILES);
    init_maps_img(p, &(p->big_map_info), \
                BIG_MAP_SIZE, BIG_NUM_TILES);
	p->current_map = 0;
	copy_info_to_mini_map(&(p->mini_map), &(p->mini_map_info));

}