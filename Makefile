# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apodader <apodader@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 10:05:31 by lsoto-do          #+#    #+#              #
#    Updated: 2024/02/02 14:01:30 by apodader         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
NAME_BONUS	= $(NAME)_bonus
CFLAGS      = -O3 -g -Wall -Wextra  -Werror #-fsanitize=address
RM          = rm -f
CK_FD_PATH		= check_file/
GAME_PATH		= game/
AUX_PATH		= aux/
BONUS_PATH		= bonus/
SRCS_PATH           = src/
OBJS_PATH           = obj/
BONUS_OBJS_PATH		= $(OBJS_PATH)$(BONUS_PATH)
CC = cc

GOALS_CONTAIN_BONUS := $(if $(filter bonus,$(MAKECMDGOALS)),yes,no)
ifeq ($(GOALS_CONTAIN_BONUS),yes)
    RE_RULE_TARGET := fclean bonus
else
    RE_RULE_TARGET := fclean all
endif

OS			:= $(shell uname -s)
DEPS_PATH	=	deps/
LIB_PATH	= 	./libft
LIB			=	$(LIB_PATH)/libft.a 

#BUILT INS variables


## Add new path, just need name/
MAKE_OBJ_BASE_DIR   = $(OBJS_PATH)
MAKE_OBJ_DIR		=  $(addprefix $(OBJS_PATH), \
									$(CK_FD_PATH), \
									$(AUX_PATH), \
									$(GAME_PATH), \
									)

MAKE_OBJ_DIR_BONUS	= $(addprefix $(BONUS_OBJS_PATH), $(CK_FD_PATH), \
											$(AUX_PATH), \
											$(GAME_PATH))
										
#Add new path to objects


ifeq ($(OS), Linux)
MLX_PATH = ./minilibx-linux/
FRAME = -lXext -lX11 -lm -lz
KEYS = -D LINUX_KEYS=1
else
MLX_PATH = ./minilibx_opengl_20191021/
FRAME = -framework OpenGL -framework AppKit
KEYS = -D LINUX_KEYS=0
endif



LDFLAGS		= 	-L$(LIB_PATH) -lft -lm -L$(MLX_PATH) -lmlx $(FRAME)

INCS        = -I./includes/ -I$(LIB_PATH)/includes -I$(MLX_PATH)
#Colors


DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
LIGHT_GREEN = \033[1;92m

###

SRC         =	main.c

CHECK		=	check_file.c parse_file.c init_parseer.c parse_for_ids.c \
				check_img_file.c check_ceil_floor_vals.c check_elements.c \
				parse_map.c get_map_to_list.c free_list.c valid_map_line.c \
				get_map_to_prg.c check_map_borders.c helpers_border.c  set_player_info.c
				
CK_FILES	=	$(addprefix $(CK_FD_PATH), $(CHECK))

AUX 		=	exit_error.c exit_success.c init_prg.c \
				init_int_array.c check_file_extension.c is_new_line.c \
				ft_max.c ft_min.c destoy_imgs.c \
				free_memory.c 
				
AUX_FILES	= 	$(addprefix $(AUX_PATH), $(AUX))

GAME		=	hooks.c  update_window.c \
				make_move.c rotate_player.c raycaster.c \
				dda.c ray_to_img.c

GAME_FILES	=	$(addprefix $(GAME_PATH), $(GAME))

BONUS		=	draw_map_bonus.c open_door_bonus.c \
				check_if_inside_player_bonus.c get_coordinates_bonus.c \
				init_main_mini_map_bonus.c 
				

BONUS_FILE	=	$(addprefix $(BONUS_PATH)$(GAME_PATH), $(BONUS))

DEPS		= 	$(addprefix $(DEPS_PATH),	$(SRC:.c=.d) \
											$(CHECK:.c=.d)\
											$(AUX:.c=.d) \
											$(GAME:.c=.d) \
											$(BONUS:.c=.d),\
											$(CHECK:%.c=%_bonus.d)\
											$(AUX:%.c=%_bonus.d) \
											$(GAME:%.c=%_bonus.d) \
											$(BONUS:%.c=%_bonus.d),\
											$(SRC:%.c=%_bonus.d)\
											) 
										
										

#add .d files to deps

SRC			+= $(CK_FILES) $(AUX_FILES) $(GAME_FILES)

SRC_BONUS   =	$(addprefix $(BONUS_PATH), $(SRC:%.c=%_bonus.c)) $(BONUS_FILE)
## add to sercs

OBJS        =	$(addprefix $(OBJS_PATH), $(SRC:.c=.o)) 

OBJS_BONUS	=	$(addprefix $(OBJS_PATH), $(SRC_BONUS:.c=.o))
				

all:  make_mlx make_lib $(NAME)


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c Makefile| $(MAKE_OBJ_BASE_DIR) $(MAKE_OBJ_DIR) $(DEPS_PATH)
		@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
		@$(CC) $(CFLAGS) $(INCS) $(KEYS) -MMD -MP -c $< -o  $@
		@mv $(basename $@).d $(DEPS_PATH)


$(NAME): $(OBJS) $(LIB) $(L_MLX) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LINEFLAGS) $(LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(LIGHT_GREEN)Created $(NAME) executable$(DEF_COLOR)"

bonus: make_mlx make_lib $(NAME_BONUS)


$(BONUS_OBJS_PATH)%.o: $(BONUS_PATH)%.c Makefile | $(MAKE_OBJ_BASE_DIR) $(MAKE_OBJ_DIR_BONUS) $(DEPS_PATH)
	@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCS) $(KEYS) -MMD -MP -c $< -o  $@
	@mv $(basename $@).d $(DEPS_PATH)

# SHOULD HAVE A RULE TO MAKE SRS_BONUS

$(NAME_BONUS): $(OBJS_BONUS) $(LIB) $(L_MLX) Makefile 
	@$(CC) $(CFLAGS) $(INCS) $(OBJS_BONUS) $(LINEFLAGS) $(LIB)-o $(NAME_BONUS) $(LDFLAGS)
	@echo "$(LIGHT_GREEN)Created $(NAME_BONUS) executable$(DEF_COLOR)"

make_lib:
	@$(MAKE) -s -C $(LIB_PATH)
	@echo "$(BLUE)Done checking Libft! $(DEF_COLOR)"

make_mlx:
	@$(MAKE) -s -C $(MLX_PATH)
	@echo "$(BLUE)Done checking MLX! $(DEF_COLOR)"

$(MAKE_OBJ_BASE_DIR):
	@echo "$(GREEN)Creating $(NAME) Obj Dir $(DEF_COLOR)"
	@mkdir -p $(MAKE_OBJ_BASE_DIR)

$(MAKE_OBJ_DIR_BONUS):
	@echo "$(GREEN)Creating $(NAME_BONUS) Obj Dir $(DEF_COLOR)"
	@mkdir -p $(MAKE_OBJ_DIR_BONUS)

$(MAKE_OBJ_DIR):
	@echo "$(GREEN)Creating $(NAME) Obj Dir $(DEF_COLOR)"
	@mkdir -p $(MAKE_OBJ_DIR)

$(DEPS_PATH):
	@echo "$(GREEN)Creating $(NAME) Deps Dir $(DEF_COLOR)"
	@mkdir -p $(DEPS_PATH)

-include $(DEPS)

fclean_lib:
	@$(MAKE) fclean -s -C $(LIB_PATH)

clean_lib:
	@$(MAKE) clean -s -C $(LIB_PATH) 

fclean_mlx:
	@$(MAKE) clean -s -C $(MLX_PATH) 


clean: clean_lib clean_objects

fclean:  clean_objects fclean_lib fclean_mlx
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"

clean_objects:
	@echo "$(GREEN)$(NAME) Objects and Dependencies cleaned!$(DEF_COLOR)"
	@$(RM) -r $(OBJS_PATH) $(DEPS_PATH)

re: $(RE_RULE_TARGET)

.PHONY: all fclean clean re bonus clean_objects clean_lib fclean_lib make_mlx make_lib 
