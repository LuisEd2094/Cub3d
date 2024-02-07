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

#include <cub3d.h>


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
	mlx_do_key_autorepeaton(prg->mlx.ptr); // ?
	prg->mini_map.t_img.img = mlx_new_image(prg->mlx.ptr, \
	ft_min(((prg->map_w + 1) * TILE_SIZE), MINI_MAP_SIZE), \
	ft_min((prg->map_h) * TILE_SIZE, MINI_MAP_SIZE));
	if (!prg->mini_map.t_img.img)
		exit_error(NULL, prg);
	prg->mini_map.t_img.addr = mlx_get_data_addr(prg->mini_map.t_img.img, \
	&prg->mini_map.t_img.bpp, &prg->mini_map.t_img.line_length, \
	&prg->mini_map.t_img.endian);
	if (!prg->mini_map.t_img.addr)
		exit_error(NULL, prg);
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
	get_hooks(&prg);
	update_window(&prg);
	mlx_loop(prg.mlx.ptr);
	exit_success(&prg);
}