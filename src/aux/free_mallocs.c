/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mallocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:02 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/02 14:06:22 by apodader         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void free_player(t_pc * player)
// {
// 	if (player)
// 	{
// 		if (player->center)
// 			free(player->center);
// 		if (player->hit_box_center)
// 			free(player->hit_box_center);
// 		if (player->hit_box_left)
// 			free(player->hit_box_left);
// 		if (player->hit_box_right)
// 			free(player->hit_box_right);		
// 		free(player);
// 	}
// }

// void free_ray(t_ray *r)
// {
// 	if (r)
// 	{
// 		if (r->end)
// 			free(r->end);
// 		if (r->start)
// 			free(r->start);
// 		free(r);
// 	}
// }

void free_img(t_img *img)
{
	if (img)
		free(img);
}

// void	free_mini_map(t_map *map)
// {
// 	if (map)
// 	{
// 		if (map->t_img)
// 			free(map->t_img);
// 		if (map->a)
// 			free(map->a);
// 		if (map->b)
// 			free(map->b);
// 		if (map->c)
// 			free(map->c);
// 		free(map);
// 	}
// }

// void	free_mlx(t_prg *prg)
// {
// 		if (prg->mlx)
// 	{
// 		if (prg->mlx->window)
// 			mlx_destroy_window(prg->mlx->ptr, prg->mlx->window);
// 		free(prg->mlx);
// 	}

// }

void	free_mallocs(t_prg *prg)
{
	free_2d_array((void **)prg->map);
	//free_mlx(prg);
	//free_player(prg->player);
	//free_ray(prg->ray);
	//free_img(prg->img);
	// free_img(&(prg->north_img));
	// free_img(prg->south_img);
	// free_img(prg->west_img);
	// free_img(prg->east_img);
	// free_img(prg->door_img);
	// free_img(prg->sprite[0]);
	// free_img(prg->sprite[1]);
	// free_img(prg->sprite[2]);

	//free_mini_map(prg->mini_map);
}
