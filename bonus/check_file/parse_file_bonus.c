/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:41:11 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 09:41:11 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>
#include "parse_file_bonus.h"

bool	parse_file(int fd, t_prg *prg)
{
	t_parseer	parse;

	init_parseer(&parse);
	if (!parse_for_ids(fd, prg, &parse) || (errno && (errno != 60)))
		return (false);
	if (!parse_map(fd, prg, &parse) || (errno && (errno != 60)))
		return (false);
	return (true);
}
