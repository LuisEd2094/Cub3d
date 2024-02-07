#include "parse_file_bonus.h"

bool	return_error_invalid_line(char *line, t_prg *prg, int fd, bool set_msg)
{
	free(line);
	get_next_line(fd, 1);
	if (set_msg)
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
			return (return_error_invalid_line(line, prg, fd, 1));
		if (!line[0])
		{
			free(line);
			line = get_next_line(fd, 0);
			continue ;
		}
		if (!add_line_to_list(line, parse))
			return (return_error_invalid_line(line, prg, fd, 0));
		line = get_next_line(fd, 0);
	}
	if (!parse->found_player)
		prg->error_msg = NO_PLAYER;
	return (true);
}
