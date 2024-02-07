/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:26:09 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:36:49 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

char	*get_start_map(int fd, t_prg *prg)
{
	char	*line;

	line = get_next_line(fd, 0);
	while (line && is_new_line(line))
	{
		free(line);
		line = get_next_line(fd, 0);
		if (!line)
			break ;
	}
	if (!line)
		prg->error_msg = NO_MAP;
	return (line);
}

bool	parse_map(int fd, t_prg *prg, t_parseer *parse)
{
	char	*line;

	line = get_start_map(fd, prg);
	if (!line)
		return (false);
	if (!get_map_to_list(fd, prg, parse, line) || !parse->found_player)
		return (free_list(parse, false));
	if (!get_map_to_prg(prg, parse))
		return (free_list(parse, false));
	return (free_list(parse, true));
}
