/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:11 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:30:12 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

void	save_elem_to_prg(t_parseer *parse, char **elemts, t_prg *prg, int i)
{
	if (parse->identifiers[i])
		prg->error_msg = REPEATED;
	else
	{
		parse->identifiers[i] = 1;
		parse->ids_found += 1;
		if (i < 4)
			check_img_file(elemts, prg);
		else
			check_ceil_floor_vals(prg, elemts, parse);
	}
}

void	check_for_identifiers(t_parseer *parse, char **elements, t_prg *prg)
{
	int	i;

	i = 0;
	while (parse->valid_identifier[i] && !prg->error_msg)
	{
		if (ft_strcmp(parse->valid_identifier[i], elements[0]) == 0)
			return (save_elem_to_prg(parse, elements, prg, i));
		i++;
	}
	prg->error_msg = MISCONFIG;
	return ;
}

bool	check_valid_line(char *line, t_prg *p)
{
	if (!line[0])
		return (0);
	if (!ft_isalnum(line[ft_strlen(line) - 1]))
	{
		p->error_msg = MISCONFIG;
		return (0);
	}
	return (1);
}

void	check_elements(t_parseer *parse, char *line, t_prg *prg)
{
	char	**elements;

	if (!check_valid_line(line, prg))
		return ;
	elements = ft_split(line, ' ');
	if (!elements)
		return ;
	check_for_identifiers(parse, elements, prg);
	free_2d_array((void **)elements);
}
