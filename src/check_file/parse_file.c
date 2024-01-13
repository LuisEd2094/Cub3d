/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:55 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:34:47 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "parse_file.h"

bool	parse_file(int fd, t_prg *prg)
{
	t_parseer	parse;

	init_parseer(&parse);
	if (!parse_for_ids(fd, prg, &parse) || errno)
		return (false);
	if (!parse_map(fd, prg, &parse) || errno)
		return (false);
	return (true);
}
