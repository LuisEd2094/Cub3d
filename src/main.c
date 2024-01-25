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
	ft_printf(1, "VALID MAP\n");
	for (int i = 0; prg.map[i]; ++i)
		ft_printf(1, "%s\n", prg.map[i]);
	exit_success(&prg);

}
