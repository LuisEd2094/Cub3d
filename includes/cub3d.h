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
# include <get_next_line.h>
# include <ft_printf.h>
# include <libft.h>
# include "error_messages.h"
# include "mlx.h"
# include <math.h>
# include "keys.h"


# ifndef RGB_ARRAY
#  define RGB_ARRAY 3
# endif

# define TILE_HEIGHT 32
# define TILE_WIDTH	32

typedef struct s_player
{
	double	x;
	double	y;
	double	width_start;
	double	width_end;
	double	height_start;
	double	height_end;
}	t_pc;

#define PLAYER(prg) (prg->player)
#define PLAYER_X(prg) (prg->player->x)
#define PLAYER_Y(prg) (prg->player->y)
#define PLAYER_WIDTH_START(prg) (prg->player->width_start)
#define PLAYER_WIDTH_END(prg) (prg->player->width_end)
#define PLAYER_HEIGHT_START(prg) (prg->player->height_start)
#define PLAYER_HEIGHT_END(prg) (prg->player->height_end)



typedef struct  t_s_mlx
{
    void    *ptr;
    void    *window;
}   t_mlx;

typedef struct s_prg
{
	int		north_img; //0
	int		south_img; // 1
	int		west_img; //2
	int		east_img; //3
	int		floor_vals[4];
	int		ceiling_vals[4];
	double	camara_x;
	double	camara_y;
	double	plane_x;
	double	plane_y;
	int		map_h;
	int		map_w;
	int		map_tile_h;
	int		map_tile_w;
	char	**map;
	char	*error_msg;
    t_mlx   *mlx;
	t_pc	*player;
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
int		ft_max(int a, int b);


// CHECK FILE FUNCTIONS
void	validate_map(char *file_name, t_prg *prg);
bool	parse_file(int fd, t_prg *prg);

// INIT PRG

void	init_prg(t_prg *prg);
#endif
