/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:24:49 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:09:40 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

void	*ft_free_strs_line(char **str, char **str2);
char	*get_next_line(int fd);
char	*read_file(int fd, char *buffer, int bytes_read);
char	*join_buff(char *buffer, char *reader);
char	*buffer_prep(char *buffer);
char	*parse_line(char *buffer);

#endif
