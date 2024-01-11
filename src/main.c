/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:02 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:19:27 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char *argv[])
{
	t_prg	prg;

	init_prg(&prg);
	if (argc != 2)
		exit_error(INCORRECT_USE, &prg);
	validate_map(argv[1], &prg);
	for (int i = 0; i < 3; i++)
		ft_printf(1, "RGB >%i<\n", prg.floor_vals[i]);
	for (int i = 0; i < 3; i++)
		ft_printf(1, "RGB >%i<\n", prg.ceiling_vals[i]);
	ft_printf(1, "VALID MAP\n");
	exit_success(&prg);
}
