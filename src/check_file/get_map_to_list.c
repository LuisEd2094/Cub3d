/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_to_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:33 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:32:55 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

bool	return_error_invalid_line(char *line, t_prg *prg)
{
	free(line);
	prg->error_msg = WRONG_MAP;
	return (false);
}

bool	add_line_to_list(char *line, t_parseer *parse)
{
	t_list	*node;

	node = ft_lstnew(line);
	if (!node)
	{
		ft_lstclear(&(parse->list), free);
		free(line);
		return (false);
	}
	ft_lstadd_back(&(parse->list), node);
	return (true);
}

bool	get_map_to_list(int fd, t_prg *prg, t_parseer *parse, char *line)
{
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!valid_map_line(line, parse))
			return (return_error_invalid_line(line, prg));
		if (!line[0])
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!add_line_to_list(line, parse))
			return (false);
		line = get_next_line(fd);
	}
	if (!parse->found_player)
		prg->error_msg = NO_PLAYER;
	return (true);
}
