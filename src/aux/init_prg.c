/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:13 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:24:24 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_str_array(char **array, int size)
{
	int	i;

	i = -1;
	while (++i <= size)
		array[i] = NULL;
}

void	init_prg(t_prg *prg)
{
	prg->north_img = 0;
	prg->south_img = 0;
	prg->west_img = 0;
	prg->east_img = 0;
	init_int_array(prg->floor_vals, RGB_ARRAY);
	init_int_array(prg->ceiling_vals, RGB_ARRAY);
	prg->camara_x = 0;
	prg->camara_y = 0;
	prg->player_y = 0;
	prg->player_x = 0;
	prg->error_msg = NULL;
	prg->map = NULL;
	errno = 0;
}