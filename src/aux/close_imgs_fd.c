/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_imgs_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:44 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:21:41 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	close_imgs_fd(t_prg *prg)
{
	if (prg->north_img)
		close(prg->north_img);
	if (prg->south_img)
		close(prg->south_img);
	if (prg->west_img)
		close(prg->west_img);
	if (prg->east_img)
		close(prg->east_img);
}
