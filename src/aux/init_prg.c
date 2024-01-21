/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:13 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:24:24 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_str_array(char **array, int size)
{
	int	i;

	i = -1;
	while (++i <= size)
		array[i] = NULL;
}

void	init_prg(t_prg *prg)
{
	prg->mlx = (t_mlx *)malloc(sizeof (t_mlx));
	prg->player = (t_pc *)malloc(sizeof (t_pc));
	prg->ray = (t_ray *)malloc(sizeof (t_ray));
	if (!prg->mlx || !prg->player || !prg->ray)
		exit_error(NULL, prg);
	prg->player->dir = (t_point *)malloc(sizeof (t_point));
	prg->player->left_corner = (t_point *)malloc(sizeof (t_point));
	prg->player->right_corner = (t_point *)malloc(sizeof (t_point));
	prg->player->center = (t_point *)malloc(sizeof (t_point));
	prg->ray->start = (t_point *)malloc(sizeof (t_point));
	prg->ray->end = (t_point *)malloc(sizeof (t_point));
	prg->ray->direction = (t_point *)malloc(sizeof (t_point));
	if (!prg->player->dir || !prg->player->left_corner  || !prg->player->right_corner || !prg->player->center \
		|| !prg->ray->distance|| !prg->ray->start || !prg->ray->end || !prg->ray->direction)
		exit_error(NULL, prg);
	prg->north_img = 0;
	prg->south_img = 0;
	prg->west_img = 0;
	prg->east_img = 0;
	init_int_array(prg->floor_vals, RGB_ARRAY);
	init_int_array(prg->ceiling_vals, RGB_ARRAY);
	prg->camara_x = 0;
	prg->camara_y = 0;
	prg->error_msg = NULL;
	prg->map = NULL;
	prg->map_h = 0;
	prg->map_w = 0;
	errno = 0;
}
