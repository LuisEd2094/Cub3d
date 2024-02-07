/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:13 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:23:19 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_prg_structs(t_prg *prg)
{
	prg->mlx.window = NULL;
}

static void	init_img_to_null(t_prg *prg)
{
	prg->img.img = NULL;
	prg->north_img.img = NULL;
	prg->south_img.img = NULL;
	prg->west_img.img = NULL;
	prg->east_img.img = NULL;
}

void	init_prg(t_prg *prg)
{
	init_prg_structs(prg);
	init_img_to_null(prg);
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
