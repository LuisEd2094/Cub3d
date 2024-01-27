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

static void	init_str_array(char **array, int size)
{
	int	i;

	i = -1;
	while (++i <= size)
		array[i] = NULL;
}

static void	init_player(t_pc *player)
{
	player->dir = (t_point *)malloc(sizeof (t_point));
	player->left_corner = (t_point *)malloc(sizeof (t_point));
	player->right_corner = (t_point *)malloc(sizeof (t_point));
	player->center = (t_point *)malloc(sizeof (t_point));
	player->hit_box_center = (t_point *)malloc(sizeof (t_point));
	player->hit_box_left = (t_point *)malloc(sizeof (t_point));
	player->hit_box_right = (t_point *)malloc(sizeof (t_point));
}

static void	init_ray(t_ray *ray)
{
	ray->start = (t_point *)malloc(sizeof (t_point));
	ray->end = (t_point *)malloc(sizeof (t_point));
}

static void	init_prg_structs(t_prg *prg)
{	
	prg->mlx = (t_mlx *)malloc(sizeof (t_mlx));
	prg->player = (t_pc *)malloc(sizeof (t_pc));
	prg->ray = (t_ray *)malloc(sizeof (t_ray));
	prg->img = (t_img *)malloc(sizeof (t_img));
	prg->mini_map= (t_map *)malloc(sizeof (t_map));
}

static void	init_mini_map_img(t_map *map)
{
	map->t_img = (t_img *)malloc(sizeof(t_img));
	map->t_img->img = NULL;
}

static bool	check_correct_inits(t_prg *prg)
{
	if (!prg->player->dir \
		|| !prg->player->left_corner || !prg->player->right_corner \
		|| !prg->player->center	|| !prg->player->hit_box_center \
		|| !prg->player->hit_box_left || !prg->player->hit_box_right \
		|| !prg->ray->start || !prg->ray->end \
		|| !prg->mini_map)
		return (0);
	return (1);
}

void	init_prg(t_prg *prg)
{
	init_prg_structs(prg);
	if (!prg->mlx || !prg->player || !prg->ray || !prg->img || !prg->mini_map)
		exit_error(NULL, prg);
	prg->img->img = NULL;
	init_player(prg->player);
	init_ray(prg->ray);
	init_mini_map_img(prg->mini_map);
	if (!check_correct_inits(prg))
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