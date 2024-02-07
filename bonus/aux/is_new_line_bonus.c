/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_new_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:24:52 by lsoto-do         ###   ########.fr       */
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
