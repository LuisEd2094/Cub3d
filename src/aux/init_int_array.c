/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_int_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:20:08 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:23:43 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	init_int_array(int *array, int size)
{
	int	i;

	i = -1;
	while (++i <= size)
		array[i] = 0;
}
