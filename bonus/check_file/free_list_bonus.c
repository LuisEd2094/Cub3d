/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:25:28 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:32:21 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file_bonus.h"

bool	free_list(t_parseer *parse, bool return_val)
{
	ft_lstclear(&(parse->list), free);
	return (return_val);
}
