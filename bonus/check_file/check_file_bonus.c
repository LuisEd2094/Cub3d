/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:39:50 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 09:39:50 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	validate_map(char *file_name, t_prg *prg)
{
	int	fd;

	if (check_if_invalid_ext(file_name, ".cub", ft_strlen(".cub")))
		exit_error(INCORRECT_FILE, prg);
	if ((errno && (errno != 60)))
		exit_error(NULL, prg);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_error(NULL, prg);
	if (!parse_file(fd, prg) || (errno && (errno != 60)))
	{
		close(fd);
		exit_error(NULL, prg);
	}
	close(fd);
	open_img(&(prg->mlx), &(prg->door_img), "./imgs/door.xpm");
	open_img(&(prg->mlx), &(prg->sprite[0]), "./imgs/sprite1.xpm");
	open_img(&(prg->mlx), &(prg->sprite[1]), "./imgs/sprite2.xpm");
	open_img(&(prg->mlx), &(prg->sprite[2]), "./imgs/sprite3.xpm");
	if (errno && errno != 60)
		exit_error(NULL, prg);
}
