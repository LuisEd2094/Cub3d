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


static void	init_prg_structs(t_prg *prg)
{	
	prg->mlx.window = NULL;
}


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
