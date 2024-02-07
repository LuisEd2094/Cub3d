
#include "parse_file_bonus.h"

bool	check_adjecent_values(t_prg *prg, int i, int j)
{
	if (prg->map[i][j - 1] == ' ' || prg->map[i][j + 1] == ' ' \
		|| prg->map[i - 1][j] == ' ' || prg->map[i + 1][j] == ' ')
		return (false);
	if ((prg->map[i][j - 1] == '1' && prg->map[i][j + 1] == '1'))
		return (true);
	if ((prg->map[i - 1][j] == '1' && prg->map[i + 1][j] == '1'))
		return (true);
	return (false);
}

bool	set_door_error(t_prg *prg)
{
	prg->error_msg = DOOR_ERROR;
	return (false);
}

bool	check_door(t_prg *prg, int i, int j, t_parseer *parse)
{
	if (i == 0 || j == 0)
		return (set_door_error(prg));
	else if (!prg->map[i][j + 1] || prg->map[i][j + 1] == ' ')
		return (set_door_error(prg));
	else if (parse->next_line && j < parse->next_len && \
			parse->next_line[j] == ' ')
		return (set_door_error(prg));
	else if (!parse->next_line || j >= parse->next_len)
		return (set_door_error(prg));
	else if (parse->prev_len > 0 && parse->prev_len <= j)
		return (set_door_error(prg));
	else if (!check_adjecent_values(prg, i, j))
		return (set_door_error(prg));
	return (true);
}

bool	check_map_borders(t_prg *prg, t_parseer *parse)
{
	int	i;
	int	j;

	i = -1;
	while (prg->map[++i])
	{
		j = -1;
		prepare_parse_vals(prg, parse, i);
		while (prg->map[i][++j])
		{
			if (prg->map[i][j] == '0')
			{
				if (!check_zero(prg, i, j, parse))
					return (false);
			}
			else if (prg->map[i][j] == ' ')
			{
				if (!check_space(prg, i, j, parse))
					return (false);
			}
			else if (prg->map[i][j] == '2')
			{
				if (!check_door(prg, i, j, parse))
					return (false);
			}
		}
	}
	return (true);
}
