/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:40:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:17:32 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_file_bonus.h"

bool	free_list(t_parseer *parse, bool return_val)
{
	ft_lstclear(&(parse->list), free);
	return (return_val);
}
