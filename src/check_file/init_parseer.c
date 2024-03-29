/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parseer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:48 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:58:34 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

void	set_valid_identifiers(t_parseer *p)
{
	p->valid_identifier[0] = "NO";
	p->valid_identifier[1] = "SO";
	p->valid_identifier[2] = "WE";
	p->valid_identifier[3] = "EA";
	p->valid_identifier[4] = "F";
	p->valid_identifier[5] = "C";
	p->valid_identifier[6] = NULL;
}

void	set_booleans(t_parseer *parse)
{
	init_int_array(parse->identifiers, ID_ARRAY_SIZE);
	parse->rgb_str[0] = NULL;
	parse->rgb_str[1] = NULL;
	parse->rgb_str[2] = NULL;
	parse->rgb_str[3] = NULL;
	parse->found_player = 0;
	parse->ids_found = 0;
	parse->found_all = 0;
	parse->found_new_line_btwn_maps = 0;
	parse->list = NULL;
	parse->list_size = 0;
	parse->found_map = 0;
}

void	set_valid_char_map(t_parseer *p)
{
	p->valid_map_chars[0] = 'W';
	p->valid_map_chars[1] = 'S';
	p->valid_map_chars[2] = 'E';
	p->valid_map_chars[3] = 'N';
	p->valid_map_chars[4] = ' ';
	p->valid_map_chars[5] = '0';
	p->valid_map_chars[6] = '1';
	p->valid_map_chars[7] = '\0';
}

void	init_parseer(t_parseer *parse)
{
	set_booleans(parse);
	set_valid_identifiers(parse);
	set_valid_char_map(parse);
	parse->prev_len = 0;
	parse->next_len = 0;
	parse->next_line = NULL;
}
