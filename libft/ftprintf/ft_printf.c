/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:16:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/05/10 16:52:48 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	ck_format(const char *source)
{
	char	*set;
	int		i;
	int		j;

	i = 0;
	j = 0;
	set = "csipduxX%";
	while (!is_in_set(source[j], set))
		j++;
	i = 0;
	while (set[i])
	{
		if (source[j] == set[i])
			return (set[i]);
		i++;
	}
	return (0);
}

int	ft_format(const char *s, va_list ap, int i, int fd)
{
	if (ck_format(&s[i]) == 'c')
		return (c_format(&s[i], va_arg(ap, int), fd));
	else if (ck_format(&s[i]) == 's')
		return (s_format(&s[i], va_arg(ap, char *), fd));
	else if (ck_format(&s[i]) == 'i' || ck_format(&s[i]) == 'd')
		return (i_format(&s[i], va_arg(ap, int), fd));
	else if (ck_format(&s[i]) == 'p')
		return (p_format(&s[i], va_arg(ap, unsigned long), fd));
	else if (ck_format(&s[i]) == 'u')
		return (u_format(&s[i], va_arg(ap, unsigned long), fd));
	else if (ck_format(&s[i]) == 'x' || ck_format(&s[i]) == 'X')
		return (x_format(&s[i], va_arg(ap, unsigned int), fd));
	else if (ck_format(&s[i]) == '%')
		return (c_format(&s[i], ck_format(&s[i]), fd));
	else
		return (-1);
}

int	count_move_i(int temp, int *i, const char *s)
{
	int	c_count;

	if (s[*i] == '%')
	{
		c_count = temp;
		*i += i_mover(&s[*i]);
	}
	else
	{
		c_count = 1;
		*i += 1;
	}
	return (c_count);
}

int	ft_printf(int fd, const char *s, ...)
{
	va_list	ap;
	int		i;
	int		c_count;
	int		temp;

	i = 0;
	c_count = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
			temp = ft_format(s, ap, (i + 1), fd);
		else
			temp = put_char(s[i], fd);
		if (temp == -1)
			return (-1);
		c_count += temp;
		if (temp == 1 && s[i] != '%')
			i++;
		else
			i += i_mover (&s[i]);
	}
	va_end(ap);
	return (c_count);
}
