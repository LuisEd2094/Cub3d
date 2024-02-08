/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_to_prg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:43 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:31:31 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

bool	init_map(t_parseer *p, t_prg *prg)
{
	p->list_size = ft_lstsize(p->list);
	prg->map = (char **)malloc(sizeof(char *) * (p->list_size + 1));
	if (!prg->map)
		return (false);
	return (true);
}

char	*save_str_info_to_map(char *s, t_prg *prg, int y)
{
	int		x;
	char	*res;

	res = ft_strdup(s);
	if (!res)
		return (NULL);
	x = -1;
	while (res[++x])
	{
		if (res[x] != '0' && res[x] != '1' && res[x] != ' ')
			res[x] = set_player_info(prg, res[x], y, x);
		prg->map_w = ft_max(prg->map_w, x);
	}
	return (res);
}


bool	get_map_to_prg(t_prg *prg, t_parseer *parse)
{
	int		i;
	int		y;
	t_list	*curr;

	if (!init_map(parse, prg))
		return (free_list(parse, false));
	i = -1;
	y = -1;
	curr = parse->list;
	while (++i < parse->list_size)
	{
		y++;
		prg->map[i] = save_str_info_to_map(curr->content, prg, y);
		if (!prg->map[i])
			return (free_list(parse, false));
		curr = curr->next;
	}
	prg->map[i] = NULL;
	prg->map_h = parse->list_size;
	return (check_map_borders(prg, parse));
}
