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

void	update_window(t_prg *prg)
{
	mlx_clear_window(prg->mlx.ptr, prg->mlx.window);
	raycaster(prg);
	mlx_put_image_to_window(prg->mlx.ptr, prg->mlx.window, prg->img.img, 0, 0);
}
