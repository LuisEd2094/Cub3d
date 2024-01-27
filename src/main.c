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
	prg.img->img = mlx_new_image(prg.mlx->ptr, w, h);
	if (!prg.mlx->window || !prg.img->img)
		exit_error(NULL, &prg);
	prg.img->addr = mlx_get_data_addr(prg.img->img, &prg.img->bpp,
		&prg.img->line_length, &prg.img->endian);
	if (!prg.img->addr)
		exit_error(NULL, &prg);

	prg.mini_map->t_img->img = mlx_new_image(prg.mlx->ptr, ft_min(((prg.map_w + 1) * TILE_SIZE), MINI_MAP_SIZE), ft_min((prg.map_h) * TILE_SIZE, MINI_MAP_SIZE));
	if (!prg.mini_map->t_img->img)
		exit_error(NULL, &prg);
	prg.mini_map->t_img->addr = mlx_get_data_addr(prg.mini_map->t_img->img, &prg.mini_map->t_img->bpp, &prg.mini_map->t_img->line_length, &prg.mini_map->t_img->endian);
	if (!prg.mini_map->t_img->addr)
		exit_error(NULL, &prg);// should have a better check, should clean the image
	get_hooks(&prg);
	update_window(&prg);
	mlx_loop(prg.mlx->ptr);
	exit_success(&prg);
}