/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:13 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/05 17:12:25 by apodader         ###   ########.fr       */
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


static t_img *init_img(void)
{
	t_img *img;

	img = (t_img *)malloc(sizeof(t_img));
	if (img)
		img->img = NULL;
	return (img);
}

static void	init_prg_structs(t_prg *prg)
{	
	prg->mlx.window = NULL;
	//&(prg->north_img) = init_img();
	// prg->south_img = init_img();
	// prg->west_img = init_img();
	// prg->east_img = init_img();
	//prg->img = init_img();
	// prg->door_img = init_img();  //
	// prg->sprite[0] = init_img(); //
	// prg->sprite[1] = init_img(); // bonus
	// prg->sprite[2] = init_img(); //
	//prg->player = (t_pc *)malloc(sizeof(t_pc));
	//prg->mini_map= (t_map *)malloc(sizeof(t_map));
}

// static void	init_mini_map_vals(t_map *map)
// {
// 	map->t_img = init_img();
// 	map->a = (t_point *)malloc(sizeof(t_point));
// 	map->b = (t_point *)malloc(sizeof(t_point));
// 	map->c = (t_point *)malloc(sizeof(t_point));
// }

void	init_prg(t_prg *prg)
{
	init_prg_structs(prg);
	prg->mini_map.t_img.img  = NULL;
	//init_mini_map_vals(prg->mini_map);
	prg->i = 1; // bonus
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
