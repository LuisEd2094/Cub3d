/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 rotate_player.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lsoto-do <lsoto-do@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/02/06 13:41:41 by lsoto-do		   #+#	  #+#			  */
/*	 Updated: 2024/02/06 13:41:51 by lsoto-do		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <cub3d.h>

int	rotate_player(t_prg *prg, int dir)
{
	double	cam_x;
	double	plane_x;
	double	rads;

	rads = M_PI / 180.0 * ROTATION_ANGLE * dir;
	cam_x = prg->camara_x;
	plane_x = prg->plane_x;
	prg->camara_x = cam_x * cos(rads) - prg->camara_y * sin(rads);
	prg->camara_y = cam_x * sin(rads) + prg->camara_y * cos(rads);
	prg->plane_x = plane_x * cos(rads) - prg->plane_y * sin(rads);
	prg->plane_y = plane_x * sin(rads) + prg->plane_y * cos(rads);
	update_window(prg);
	return (0);
}
