/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destoy_imgs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:37:59 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:11:44 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	run_mlx_destroy(t_img *img, t_mlx *mlx)
{
	if (img->img && mlx->ptr)
	{
		mlx_destroy_image(mlx->ptr, img->img);
		img->img = NULL;
		img = NULL;
	}
}

void	destroy_img(t_prg *prg)
{
	run_mlx_destroy(&(prg->img), &(prg->mlx));
	run_mlx_destroy(&(prg->north_img), &(prg->mlx));
	run_mlx_destroy(&(prg->south_img), &(prg->mlx));
	run_mlx_destroy(&(prg->west_img), &(prg->mlx));
	run_mlx_destroy(&(prg->east_img), &(prg->mlx));
	run_mlx_destroy(&(prg->big_map_info.map_img), &(prg->mlx));
	run_mlx_destroy(&(prg->mini_map_info.map_img), &(prg->mlx));
	run_mlx_destroy(&(prg->sprite[0]), &(prg->mlx));
	run_mlx_destroy(&(prg->sprite[1]), &(prg->mlx));
	run_mlx_destroy(&(prg->sprite[2]), &(prg->mlx));
}
