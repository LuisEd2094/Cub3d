/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_new_line_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:39:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:12:59 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_new_line(char *element)
{
	int	i;

	i = -1;
	while (element[++i])
	{
		if (element[i] != '\n')
			return (false);
	}
	return (true);
}
