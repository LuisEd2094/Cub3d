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

static t_img *init_img(void)
{
	t_img *img;

	img = (t_img *)malloc(sizeof (t_img));
	if (img)
		img->img = NULL;
	return (img);
}

static void	init_prg_structs(t_prg *prg)
{	
	prg->mlx = (t_mlx *)malloc(sizeof (t_mlx));
	if (prg->mlx)
		prg->mlx->window = NULL;
	prg->north_img = init_img();
	prg->south_img = init_img();
	prg->west_img =init_img();
	prg->east_img =init_img();
	prg->img = init_img();
	prg->player = (t_pc *)malloc(sizeof (t_pc));
	prg->ray = (t_ray *)malloc(sizeof (t_ray));
	prg->mini_map= (t_map *)malloc(sizeof (t_map));
}

static void	init_mini_map_vals(t_map *map)
{
	map->t_img = init_img();
	map->a = (t_point *)malloc(sizeof(t_point));
	map->b = (t_point *)malloc(sizeof(t_point));
	map->c = (t_point *)malloc(sizeof(t_point));
}

static bool	check_correct_inits(t_prg *prg)
{
	if (!prg->player->center || !prg->player->hit_box_center \
		|| !prg->player->hit_box_left || !prg->player->hit_box_right \
		|| !prg->ray->start || !prg->ray->end \
		|| !prg->mini_map || !prg->mini_map->t_img \
		|| !prg->mini_map->a || !prg->mini_map->b \
		|| !prg->mini_map->c )
		return (0);
	return (1);
}

void	init_prg(t_prg *prg)
{
	init_prg_structs(prg);
	if (!prg->mlx || !prg->player || !prg->ray || !prg->img || !prg->mini_map \
		|| !prg->north_img || !prg->west_img || !prg->south_img || !prg->east_img)
		exit_error(NULL, prg);
	init_player(prg->player);
	init_ray(prg->ray);
	init_mini_map_vals(prg->mini_map);
	if (!check_correct_inits(prg))
		exit_error(NULL, prg);
	prg->floor_vals = 0;
	prg->ceiling_vals = 0;
	prg->camara_x = 0;
	prg->camara_y = 0;
	prg->error_msg = NULL;
	prg->map = NULL;
	prg->map_h = 0;
	prg->map_w = 0;
	errno = 0;
}