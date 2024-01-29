/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 update_window.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lsoto-do <lsoto-do@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/01/27 11:35:21 by lsoto-do		   #+#	  #+#			  */
/*	 Updated: 2024/01/27 11:35:21 by lsoto-do		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <cub3d.h>


#if BONUS_FLAG == 0

void update_window(t_prg *prg)
{
	mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
	raycaster(prg);
	mlx_put_image_to_window(prg->mlx->ptr, prg->mlx->window, prg->img->img, 0, 0);
}
#else

void update_window(t_prg *prg)
{
	mlx_clear_window(prg->mlx->ptr, prg->mlx->window);
	draw_map(prg);
	raycaster(prg);
	mlx_put_image_to_window(prg->mlx->ptr, prg->mlx->window, prg->img->img, 0, 0);
  	mlx_put_image_to_window(prg->mlx->ptr, prg->mlx->window, prg->mini_map->t_img->img, 0, 0);
	// this hit boxes will go away, but they don't seem to be working 100% correctly
	mlx_pixel_put(MLX_PTR(prg), MLX_WIN(prg), HIT_BOX_CENTER(prg)->x, PLAYER_CENTER_Y(prg), 0x000000);
	mlx_pixel_put(MLX_PTR(prg), MLX_WIN(prg),  PLAYER_CENTER_X(prg), HIT_BOX_CENTER(prg)->y, 0x000000);
}
#endif
