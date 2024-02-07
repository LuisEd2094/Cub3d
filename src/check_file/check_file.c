/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:16 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:30:36 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	validate_map(char *file_name, t_prg *prg)
{
	int	fd;

	if (check_if_invalid_ext(file_name, ".cub", ft_strlen(".cub")))
		exit_error(INCORRECT_FILE, prg);
	if (errno && errno != 11)
		return ;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit_error(NULL, prg);
	if (!parse_file(fd, prg) || errno && errno != 11)
	{
		close(fd);
		exit_error(NULL, prg);
	}
	close(fd);
}
