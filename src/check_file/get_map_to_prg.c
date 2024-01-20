/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_to_prg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:43 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:33:50 by lsoto-do         ###   ########.fr       */
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

void set_player_pos_and_mini_map(t_prg *prg, int x, int y)
{
	int new_y;

	PLAYER_X(prg) = x;
	PLAYER_Y(prg) = y;
	if (prg->camara_y == -1 || prg->camara_y == 1)
	{
		PLAYER_DIR_X(prg) = (((x + 1) * TILE_WIDTH) - (TILE_WIDTH / 2)) - 1;
		if (prg->camara_y == -1) //N
		{
			PLAYER_DIR_Y(prg) = ((y * TILE_HEIGHT));
			PLAYER_LEFT_X(prg) = ((x) * TILE_WIDTH);
			PLAYER_LEFT_Y(prg) = ((y + 1) * TILE_HEIGHT) - 1;
			PLAYER_RIGHT_Y(prg) = ((y + 1) * TILE_HEIGHT) - 1;
			PLAYER_RIGHT_X(prg) = ((x + 1) * TILE_WIDTH) - 1;
		} 
		else // S
		{
			PLAYER_DIR_Y(prg) = (((y + 1) * TILE_HEIGHT)) - 1;
			PLAYER_LEFT_X(prg) = ((x + 1) * TILE_WIDTH) - 1;
			PLAYER_LEFT_Y(prg) = ((y) * TILE_HEIGHT);
			PLAYER_RIGHT_X(prg) = ((x) * TILE_WIDTH);
			PLAYER_RIGHT_Y(prg) = ((y) * TILE_HEIGHT);
		}
	}
	else
	{
		PLAYER_DIR_Y(prg) = ((((y + 1) * TILE_HEIGHT) - (TILE_HEIGHT / 2)) - 1);
		if (prg->camara_x == 1) //E
		{
			PLAYER_DIR_X(prg) = ((x + 1) * TILE_WIDTH) - 1;
			PLAYER_LEFT_X(prg) = (x * TILE_WIDTH);
			PLAYER_LEFT_Y(prg) = (y * TILE_HEIGHT);
			PLAYER_RIGHT_X(prg) = (x * TILE_WIDTH);
			PLAYER_RIGHT_Y(prg) = ((y + 1)* TILE_HEIGHT) - 1;
		}
		else // W
		{
			PLAYER_DIR_X(prg) = ((x) * TILE_WIDTH);
			PLAYER_LEFT_X(prg) = ((x + 1) * TILE_WIDTH) - 1;
			PLAYER_LEFT_Y(prg) = ((y + 1) * TILE_HEIGHT) - 1;
			PLAYER_RIGHT_X(prg) = ((x + 1) * TILE_WIDTH) - 1;
			PLAYER_RIGHT_Y(prg) = ((y)* TILE_HEIGHT);
		}
	}
	PLAYER_CENTER_X(prg) = (PLAYER_DIR_X(prg) + PLAYER_LEFT_X(prg) + PLAYER_RIGHT_X(prg)) / 3;
	PLAYER_CENTER_Y(prg) = (PLAYER_DIR_Y(prg) + PLAYER_LEFT_Y(prg) + PLAYER_RIGHT_Y(prg)) / 3;
}

char set_player_info(t_prg *prg, char c, int y, int x)
{
	if (c == 'N' || c == 'S')
	{
		prg->camara_x = 0;
		prg->plane_y = 0;
		if (c == 'N')
			prg->camara_y = -1;
		else
			prg->camara_y = 1;
		prg->plane_x = 0.66 * (-prg->camara_y);

	}
	else if (c == 'E' || c == 'W')
	{
		prg->camara_y = 0;
		if (c == 'E')
			prg->camara_x = 1;
		else
			prg->camara_x = -1;
		prg->plane_y = 0.66 * (prg->camara_y);
	}
	set_player_pos_and_mini_map(prg, x, y);
	return ('0');
}

char *save_str_info_to_map(char *s, t_prg *prg, int y)
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
	}
	prg->map_w = ft_max(prg->map_w, x);
	return (res);
}

bool	get_map_to_prg(t_prg *prg, t_parseer *parse)
{
	int		i;
	int		y;
	t_list	*curr;
	t_list	*next;

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
