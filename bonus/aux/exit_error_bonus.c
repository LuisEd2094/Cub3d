/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:38:10 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:12:03 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	exit_error(char *error, t_prg *prg)
{
	free_memory(prg);
	if (error)
	{
		ft_printf(STDERR_FILENO, error);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (prg->error_msg)
		{
			ft_printf(STDERR_FILENO, prg->error_msg);
			exit(EXIT_FAILURE);
		}
		else
		{
			perror("Error");
			exit(errno);
		}
	}
}
