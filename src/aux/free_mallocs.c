/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mallocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:02 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:23:11 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_mallocs(t_prg *p)
{
	free_2d_array((void **)p->map);
	if (p->mlx)
		free(p->mlx);
	if (p->player)
		free(p->player);
}
