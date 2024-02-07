/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destoy_imgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:18:49 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:19:15 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
}