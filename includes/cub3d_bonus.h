/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apodader <apodader@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:05:54 by lsoto-do          #+#    #+#             */
/*   Updated: 2024/02/05 17:01:39 by apodader         ###   ########.fr       */
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
# include <error_messages_bonus.h>
# include <keys_bonus.h>
# include <mlx.h>
# include <config_bonus.h>

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

typedef struct s_map
{
	t_img	*current_img;
	t_point	a;
	t_point	b;
	t_point c;
	char	*pixel;
	bool	off_set_x;
	bool	off_set_y;
	int		current_max_size;
	int		current_num_tiles;
	int		pos_x;
	int		pos_y;
	int		max_w;
	int		max_h;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		x_pos;
	int		y_pos;
}	t_map;

typedef struct s_map_info
{
	t_img	map_img;
	bool	off_set_x;
	bool	off_set_y;
	int		max_size;
	int		num_tiles;
	int		max_w;
	int		max_h;
	int		start_x;
	int		start_y;
}	t_map_info;

typedef struct s_prg
{
	t_map_info	big_map_info;
	t_map_info	mini_map_info;
	t_img		north_img;
	t_img		south_img;
	t_img		west_img;
	t_img		east_img;
	t_img		door_img;
	t_img		sprite[3];
	t_img		img;
	t_img		*texture;
    t_mlx		mlx;
	t_map		mini_map;
	t_pc		player;
	t_ray		ray;
	double		camara_x;
	double		camara_y;
	double		plane_x;
	double		plane_y;
	char	**map;
	char	*error_msg;
	bool		current_map;
	int		i;
	int		floor_vals;
	int		ceiling_vals;
	int		map_h;
	int		map_w;
	int		mouse_delta;
	int		prev_mouse;
	int		*pixel;
	int		color;
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
void	perform_dda(t_prg *prg);
void	init_dda(t_prg *prg);
void	raycaster(t_prg *prg);			
void	ray_to_img(t_prg *prg, int i);
void	open_img(t_mlx *mlx, t_img *img, char *path);

//BONUS

void	init_maps_values(t_prg *prg);
int		rotate_player(t_prg *prg, int dir, int angle);
void	draw_map(t_prg *prg);
int		open_door(t_prg *prg);
void	get_y_values(t_prg *prg);
void	get_x_values(t_prg *prg);
bool	calculate_if_inside_player(t_map *map, int x, int y);
int		get_map_y_position(t_prg *prg);
void	copy_info_to_mini_map(t_map *mini_map, t_map_info *mini_map_info);
int		is_inside_map(int x, int y, t_prg *prg);

// INIT PRG

void	init_prg(t_prg *prg);
#endif
