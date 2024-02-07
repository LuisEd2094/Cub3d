/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:39 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:20:50 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	check_if_invalid_ext(char *file_name, char *extension, int extension_len)
{
	int		file_name_len;
	char	**split;
	char	*file;
	int		compare;

	split = ft_split(file_name, '/');
	if (!split)
		return (0);
	file = split[check_2d_array_size(split) - 1];
	file_name_len = ft_strlen(file);
	if (file_name_len < 5)
	{
		free_2d_array((void **)split);
		return (1);
	}
	compare = ft_strcmp(extension, &file[file_name_len - extension_len]);
	free_2d_array((void **)split);
	return (compare);
}
