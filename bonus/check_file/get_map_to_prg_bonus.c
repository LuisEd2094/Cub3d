
#include "parse_file_bonus.h"

bool	init_map(t_parseer *p, t_prg *prg)
{
	p->list_size = ft_lstsize(p->list);
	prg->map = (char **)malloc(sizeof(char *) * (p->list_size + 1));
	if (!prg->map)
		return (false);
	return (true);
}

void	set_player_pos_and_mini_map(t_prg *prg, int x, int y)
{
	prg->player.x = x + 0.5;
	prg->player.y = y + 0.5;
}

char	set_player_info(t_prg *prg, char c, int y, int x)
{
	if (c == 'N' || c == 'S')
	{
		prg->camara_x = 0;
		prg->plane_y = 0;
		if (c == 'N')
		{
			prg->camara_y = -1;
			prg->plane_x = 0.66;
		}
		else
		{
			prg->camara_y = 1;
			prg->plane_x = -0.66;
		}
	}
	else if (c == 'E' || c == 'W')
	{
		prg->camara_y = 0;
		prg->plane_x = 0;
		if (c == 'E')
		{
			prg->camara_x = 1;
			prg->plane_y = 0.66;
		}
		else
		{
			prg->camara_x = -1;
			prg->plane_y = -0.66;
		}
	}
	prg->player.angle = atan2(prg->camara_y, prg->camara_x);
	set_player_pos_and_mini_map(prg, x, y);
	return ('0');
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
		if (res[x] != '0' && res[x] != '1' && res[x] != ' ' && res[x] != '2')
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
