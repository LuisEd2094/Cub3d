/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 check_if_inside_player_bonus.c						:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: lsoto-do <lsoto-do@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/02/05 12:18:00 by lsoto-do		   #+#	  #+#			  */
/*	 Updated: 2024/02/05 12:18:05 by lsoto-do		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	side_of_line(t_point *p1, t_point *p2, t_point *p3)
{
	return ((p2->x - p1->x) * (p3->y - p1->y) - (p3->x - p1->x) * \
			(p2->y - p1->y));
}

bool	calculate_if_inside_player(t_map *map, int x, int y)
{
	t_point	p3;
	int		side_a_b;
	int		side_b_c;
	int		side_c_a;

	p3.x = x;
	p3.y = y;
	side_a_b = side_of_line(&(map->a), &(map->b), &p3);
	side_b_c = side_of_line(&(map->b), &(map->c), &p3);
	side_c_a = side_of_line(&(map->c), &(map->a), &p3);
	return ((side_a_b >= 0 && side_b_c >= 0 && side_c_a >= 0) || \
			(side_a_b <= 0 && side_b_c <= 0 && side_c_a <= 0));
}
