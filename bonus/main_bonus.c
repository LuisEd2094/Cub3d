/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:43:41 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:36:56 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	init_mlx_variables(t_prg *prg)
{
	prg->mlx.window = mlx_new_window(prg->mlx.ptr, W, H, "cub3d");
	prg->img.img = mlx_new_image(prg->mlx.ptr, W, H);
	if (!prg->mlx.window || !prg->img.img)
		exit_error(NULL, prg);
	prg->img.addr = mlx_get_data_addr(prg->img.img, &prg->img.bpp, \
			&prg->img.line_length, &prg->img.endian);
	if (!prg->img.addr)
		exit_error(NULL, prg);
	mlx_do_key_autorepeaton(prg->mlx.ptr);
}

int	main(int argc, char *argv[])
{
	t_prg	prg;

	printf("%f\n", FLT_MAX);
	init_prg(&prg);
	if (argc != 2)
		exit_error(INCORRECT_USE, &prg);
	prg.mlx.ptr = mlx_init();
	if (!prg.mlx.ptr || errno != 60)
		exit_error(NULL, &prg);
	validate_map(argv[1], &prg);
	init_mlx_variables(&prg);
	init_maps_values(&prg);
	get_hooks(&prg);
	update_window(&prg);
	mlx_loop(prg.mlx.ptr);
	exit_success(&prg);
}
