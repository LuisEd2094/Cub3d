/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:05:54 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/08 10:00:23 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <get_next_line.h>
# include <ft_printf.h>
# include <libft.h>
# include <error_messages.h>
# include <keys.h>
# include <mlx.h>
# include <config.h>

// Have to define FLT_MAX since we use it to avoid division by 0 but norm
// doesn't like float.h
# define FLT_MAX 340282346638528859811704183484516925440.000000

typedef struct s_point
{
	int x;
	int y;
}	t_point;


typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	hit_box_angle;

}	t_pc;

typedef struct s_ray
{
	double	ray_end_x;
	double 	ray_end_y;
	double	img_step;
	double	y_img;
	double	camera;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_disy_y;
	double	wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	int		end_p;
	int		start_p;

} t_ray;


typedef struct  t_s_mlx
{
    void    *ptr;
    void    *window;
}   t_mlx;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;


typedef struct s_prg
{
	t_img	north_img; //0
	t_img	south_img; // 1
	t_img	west_img; //2
	t_img	east_img; //3
	t_img	img;
	t_img	*texture;
    t_mlx	mlx;
	t_pc	player;
	t_ray	ray;
	double	camara_x;
	double	camara_y;
	double	plane_x;
	double	plane_y;
	int		*pixel;
	int		i;
	int		floor_vals;
	int		ceiling_vals;
	int		map_h;
	int		map_w;
	int		color;
	char	**map;
	char	*error_msg;
}	t_prg;



// AUX FUNCTIONS 
void	init_int_array(int *array, int size);
void	free_memory(t_prg *prg);
void	exit_success(t_prg *p);
void	exit_error(char *error, t_prg *prg);
int		check_if_invalid_ext(char *file_name, \
		char *extension, int extension_len);
bool	is_new_line(char *element);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
void	destroy_img(t_prg *prg);


// CHECK FILE FUNCTIONS
void	validate_map(char *file_name, t_prg *prg);
bool	parse_file(int fd, t_prg *prg);
char	set_player_info(t_prg *prg, char c, int y, int x);

// GAME FUNCTIONS

void	get_hooks(t_prg *prg);
void	update_window(t_prg *prg);
int		make_move(t_prg *prg, int dir, int side);
int		rotate_player(t_prg *prg, int dir);
void	perform_dda(t_prg *prg);
void	init_dda(t_prg *prg);
void	raycaster(t_prg *prg);			
void	ray_to_img(t_prg *prg, int i);	

// INIT PRG

void	init_prg(t_prg *prg);
#endif
