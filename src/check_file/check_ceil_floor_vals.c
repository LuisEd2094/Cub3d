/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ceil_floor_vals.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:07 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:28:18 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file.h"

bool	validate_value(char **values, t_parseer *p, int *out_l)
{
	int	j;
	int	k;
	int	l;

	l = *out_l;
	j = -1;
	while (values[++j])
	{
		k = 0;
		while (ft_isdigit(values[j][k]))
			k++;
		if (values[j][k])
			return (1);
		if (!check_if_int(values[j]))
			return (1);
		else
		{
			if (++l > 3)
				return (1);
			else
				p->rgb_str[l] = ft_strdup(values[j]);
		}
	}
	*out_l = l;
	return (0);
}

bool	check_rgb(char **elem, t_parseer *p)
{
	int		i;
	int		l;
	char	**values;
	bool	error;

	i = 0;
	l = -1;
	while (elem[++i])
	{
		values = ft_split(elem[i], ',');
		if (!values)
			return (0);
		error = validate_value(values, p, &l);
		free_2d_array((void **)values);
		if (error)
			return (0);
	}
	return (1);
}

void	get_rgb_vals(char **rgb_array, int array[4], t_prg *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		array[j] = ft_atoi(rgb_array[i]);
		if (array[j] < 0 || array[j] > 255)
		{
			p->error_msg = RGB_ERROR;
			return ;
		}
		j++;
		i++;
	}
}

void	free_2d_array_content(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
}

void	check_ceil_floor_vals(t_prg *p, char **elem, t_parseer *parse)
{
	if (!check_rgb(elem, parse))
		p->error_msg = RGB_ERROR;
	else
	{
		if (ft_strcmp(elem[0], "F") == 0)
			get_rgb_vals(parse->rgb_str, p->floor_vals, p);
		else
			get_rgb_vals(parse->rgb_str, p->ceiling_vals, p);
	}
	free_2d_array_content(parse->rgb_str);
}
