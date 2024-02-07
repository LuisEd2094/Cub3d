/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:02 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/02 15:15:38 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>


void	init_mlx_variables(t_prg *prg)
{
	prg->mlx.window = mlx_new_window(prg->mlx.ptr, W, H, "cub3d");
	prg->img.img = mlx_new_image(prg->mlx.ptr, W, H);
	if (!prg->mlx.window || !prg->img.img)
		exit_error(NULL, prg);
	prg->img.addr = mlx_get_data_addr(prg->img.img, &prg->img.bpp,
		&prg->img.line_length, &prg->img.endian);
	if (!prg->img.addr)
		exit_error(NULL, prg);
	mlx_do_key_autorepeaton(prg->mlx.ptr);
}


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


void	init_maps_values(t_prg *prg)
{
	prg->mini_map_info.map_img.img = mlx_new_image(prg->mlx.ptr, \
	ft_min(((prg->map_w + 1) * TILE_SIZE), MINI_MAP_SIZE), \
	ft_min((prg->map_h) * TILE_SIZE, MINI_MAP_SIZE));
	prg->mini_map_info.map_img.addr = mlx_get_data_addr(prg->mini_map_info.map_img.img, \
	&prg->mini_map_info.map_img.bpp, &prg->mini_map_info.map_img.line_length, \
	&prg->mini_map_info.map_img.endian);
	if (!prg->mini_map_info.map_img.addr)
		exit_error(NULL, prg);


	prg->big_map_info.map_img.img = mlx_new_image(prg->mlx.ptr, \
	ft_min(((prg->map_w + 1) * TILE_SIZE), BIG_MAP_SIZE), \
	ft_min((prg->map_h) * TILE_SIZE, BIG_MAP_SIZE));
	prg->big_map_info.map_img.addr = mlx_get_data_addr(prg->big_map_info.map_img.img, \
	&prg->big_map_info.map_img.bpp, &prg->big_map_info.map_img.line_length, \
	&prg->big_map_info.map_img.endian);
	if (!prg->big_map_info.map_img.addr)
		exit_error(NULL, prg);



	prg->mini_map_info.max_w = ft_min((prg->map_w + 1) * TILE_SIZE, MINI_MAP_SIZE);
	prg->mini_map_info.max_h = ft_min((prg->map_h) * TILE_SIZE, MINI_MAP_SIZE);
	prg->mini_map_info.off_set_x = (prg->map_w + 1) * TILE_SIZE > MINI_MAP_SIZE;
	prg->mini_map_info.off_set_y = (prg->map_h) * TILE_SIZE > MINI_MAP_SIZE;
	prg->mini_map_info.max_size = MINI_MAP_SIZE;
	prg->mini_map_info.num_tiles = MAX_NUM_TILES;
	
	
	prg->big_map_info.max_w = ft_min((prg->map_w + 1) * TILE_SIZE, BIG_MAP_SIZE);
	prg->big_map_info.max_h = ft_min((prg->map_h) * TILE_SIZE, BIG_MAP_SIZE);
	prg->big_map_info.off_set_x = (prg->map_w + 1) * TILE_SIZE > BIG_MAP_SIZE;
	prg->big_map_info.off_set_y = (prg->map_h) * TILE_SIZE > BIG_MAP_SIZE;
	prg->big_map_info.max_size = BIG_MAP_SIZE;
	prg->big_map_info.num_tiles = BIG_NUM_TILES;

	prg->current_map = 0;
	copy_info_to_mini_map(&(prg->mini_map), &(prg->mini_map_info));

}

int	main(int argc, char *argv[])
{
	t_prg	prg;

	if (argc != 2)
		exit_error(INCORRECT_USE, &prg);
	init_prg(&prg);
	prg.mlx.ptr = mlx_init();
	if (!prg.mlx.ptr)
		exit_error(NULL, &prg);
	validate_map(argv[1], &prg);
	init_mlx_variables(&prg);
	init_maps_values(&prg);
	get_hooks(&prg);
	update_window(&prg);
	mlx_loop(prg.mlx.ptr);
	exit_success(&prg);
}