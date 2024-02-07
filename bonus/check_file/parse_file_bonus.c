/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:55 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/06 13:32:04 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "parse_file.h"

bool	parse_file(int fd, t_prg *prg)
{
	t_parseer	parse;

	init_parseer(&parse);
	if (!parse_for_ids(fd, prg, &parse) || errno && errno != 11)
		return (false);
	if (!parse_map(fd, prg, &parse) || errno && errno != 11)
		return (false);
	// if bonus need to get max value for map 
/* 	prg->mini_map.mini_max_w = ft_min((prg->map_w + 1) * TILE_SIZE, MINI_MAP_SIZE);
	prg->mini_map.mini_max_h = ft_min((prg->map_h) * TILE_SIZE, MINI_MAP_SIZE);
	prg->mini_map.off_set_x = (prg->map_w + 1) * TILE_SIZE > MINI_MAP_SIZE;
	prg->mini_map.off_set_y = (prg->map_h) * TILE_SIZE > MINI_MAP_SIZE;
	prg->mini_map.big_max_w = ft_min((prg->map_w + 1) * TILE_SIZE, BIG_MAP_SIZE);
	prg->mini_map.big_max_h = ft_min((prg->map_h) * TILE_SIZE, BIG_MAP_SIZE);
	prg->mini_map.big_offset_x = (prg->map_w + 1) * TILE_SIZE > BIG_MAP_SIZE;
	prg->mini_map.big_offset_y = (prg->map_h) * TILE_SIZE > BIG_MAP_SIZE; */
	return (true);
}
