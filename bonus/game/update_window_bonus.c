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

int	update_window(t_prg *prg)
{
	mlx_clear_window(prg->mlx.ptr, prg->mlx.window);
	raycaster(prg);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, prg->img.img, 0, 0);
}
#else

int	update_window(t_prg *prg)
{
	mlx_clear_window(prg->mlx.ptr, prg->mlx.window);
	draw_map(prg);
	raycaster(prg);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, \
			prg->img.img, 0, 0);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, \
			prg->mini_map.current_img->img, 0, 0);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, \
			prg->sprite[prg->i].img, W / 2 - 75, H - 193);
}
#endif
