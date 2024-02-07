/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:24 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:30:34 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

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
		}
	}
	return (true);
}
