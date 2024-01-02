/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_format_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:15:24 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/07/05 10:02:58 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	c_left_space(t_flags flg, char arg, int fd)
{
	int		c_printed;
	int		i;

	i = 1;
	c_printed = 0;
	while (i++ < flg.width)
	{
		if (put_char(' ', fd) != 1)
			return (-1);
		c_printed++;
	}
	if (put_char(arg, fd) != 1)
		return (-1);
	c_printed++;
	return (c_printed);
}

int	c_right_space(t_flags flg, char arg, int fd)
{
	int		c_printed;
	int		i;

	i = 1;
	c_printed = 0;
	if (put_char(arg, fd) != 1)
		return (-1);
	c_printed++;
	while (i++ < flg.width)
	{
		if (put_char(' ', fd) != 1)
			return (-1);
		c_printed++;
	}
	return (c_printed);
}

int	c_format(const char *s, char arg, int fd)
{
	t_flags	flags;

	flags = check_flags(s, "c%");
	if (flags.dash)
		return (c_right_space(flags, arg, fd));
	else if (flags.width > 0)
		return (c_left_space(flags, arg, fd));
	else
		return (put_char(arg, fd));
}
