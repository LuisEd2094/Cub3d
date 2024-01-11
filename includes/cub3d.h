/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:05:54 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/01/11 10:07:26 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include "error_messages.h"

# ifndef RGB_ARRAY
#  define RGB_ARRAY 3
# endif

typedef struct s_prg
{
	int		north_img; //0
	int		south_img; // 1
	int		west_img; //2
	int		east_img; //3
	int		floor_vals[4];
	int		ceiling_vals[4];
	int		player_pos[3];
	char	**map;
	char	*error_msg;
}	t_prg;

// AUX FUNCTIONS 
bool	print_error(char *error);
void	init_int_array(int *array, int size);
void	exit_success(t_prg *p);
void	exit_error(char *error, t_prg *prg);
void	close_imgs_fd(t_prg *prg);
int		check_if_invalid_ext(char *file_name, \
		char *extension, int extension_len);
bool	is_new_line(char *element);
void	free_mallocs(t_prg *p);

// CHECK FILE FUNCTIONS
void	validate_map(char *file_name, t_prg *prg);
bool	parse_file(int fd, t_prg *prg);

// INIT PRG

void	init_prg(t_prg *prg);
#endif
