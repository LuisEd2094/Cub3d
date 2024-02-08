/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_img_file_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:40:00 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:15:24 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file_bonus.h"

void	open_img(t_mlx *mlx, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx->ptr, path, &img->width, &img->height);
	if (img->img)
		img->addr = mlx_get_data_addr(img->img, &img->bpp, \
		&img->line_length, &img->endian);
}

void	check_img_file(char **elemts, t_prg *p)
{
	if (check_2d_array_size(elemts) > 2)
		p->error_msg = MISCONFIG;
	else if (check_if_invalid_ext(elemts[1], ".xpm", ft_strlen(".xpm")))
		p->error_msg = INCORRECT_FILE;
	else
	{
		if (ft_strcmp(elemts[0], "NO") == 0)
			open_img(&(p->mlx), &(p->north_img), elemts[1]);
		else if (ft_strcmp(elemts[0], "SO") == 0)
			open_img(&(p->mlx), &(p->south_img), elemts[1]);
		else if (ft_strcmp(elemts[0], "WE") == 0)
			open_img(&(p->mlx), &(p->west_img), elemts[1]);
		else
			open_img(&(p->mlx), &(p->east_img), elemts[1]);
	}
}
