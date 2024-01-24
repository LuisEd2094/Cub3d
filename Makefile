# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 10:05:31 by lsoto-do          #+#    #+#              #
#    Updated: 2024/01/11 10:05:32 by lsoto-do         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3D
NAME_BONUS	= $(NAME)_bonus
CFLAGS      = -g -fsanitize=address #-Wall -Wextra  -Werror #
RM          = rm -f
CK_FD_PATH		= check_file/
GAME_PATH		= game/
AUX_PATH		= aux/
BONUS_PATH		= bonus/
SRCS_PATH           = src/
SRCS_PATH_BONUS		= src_bonus/
OBJS_PATH           = obj/
OBJS_PATH_BONUS		= obj_bonus/
OS			:= $(shell uname -s)

CC = cc

#BUILT INS variables


## Add new path, just need name/
MAKE_OBJ_DIR		= $(OBJS_PATH) $(addprefix $(OBJS_PATH), \
									$(CK_FD_PATH), \
									$(AUX_PATH), \
									$(GAME_PATH), \
									)

MAKE_OBJ_BONUS		=  $(OBJS_PATH_BONUS) $(addprefix $(OBJS_PATH_BONUS), $(BONUS_PATH))



ifeq ($(OS), Linux)
MLX_PATH = ./minilibx-linux/
FRAME = -lXext -lX11 -lm -lz
KEYS = -D LINUX_KEYS=1
else
MLX_PATH = ./minilibx_opengl_20191021/
FRAME = -framework OpenGL -framework AppKit
KEYS = 
endif



#Add new path to objects

L_MLX = $(MLX_PATH)libmlx.a

DEPS_PATH	= deps/
LIB_PATH	= 	./libft
LIB			=	$(LIB_PATH)/libft.a 
LDFLAGS		= 	-L$(LIB_PATH) -lft -lm -L$(MLX_PATH) -lmlx $(FRAME)

INCS        = -I./includes/ -I$(LIB_PATH)/includes
INCS_BONUS	= ./includes/bonus.h
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
				get_map_to_prg.c check_map_borders.c
				

CK_FILES	=	$(addprefix $(CK_FD_PATH), $(CHECK))

AUX 		=	close_imgs_fd.c exit_error.c exit_success.c init_prg.c \
				init_int_array.c check_file_extension.c is_new_line.c \
				free_mallocs.c ft_max.c
				
AUX_FILES	= 	$(addprefix $(AUX_PATH), $(AUX))

GAME		=	hooks.c update_window.c make_move.c ray.c

GAME_FILES	=	$(addprefix $(GAME_PATH), $(GAME))

BONUS		=	draw_map_bonus.c triangle_bonus.c

BONUS_FILES = 	$(addprefix $(BONUS_PATH), $(BONUS))

DEPS		= 	$(addprefix $(DEPS_PATH),	$(SRC:.c=.d) \
											$(CHECK:.c=.d)\
											$(AUX:.c=.d) \
											$(GAME:.c=.d))

DEPS_BONUS	=	$(addprefix $(DEPS_PATH), $(BONUS:.c=.d))
										
										

#add .d files to deps

SRC			+= $(CK_FILES) $(AUX_FILES) $(GAME_FILES)

SRC_BONUS	= $(BONUS_FILES)

## add to sercs

OBJS        =	$(addprefix $(OBJS_PATH), $(SRC:.c=.o)) 

OBJS_BONUS	=	$(addprefix $(OBJS_PATH_BONUS), $(SRC_BONUS:.c=.o)) 
				

all: make_mlx make_lib $(NAME)


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(MAKE_OBJ_DIR) $(DEPS_PATH)
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCS) $(KEYS) -MMD -MP -c $< -o  $@
			@mv $(basename $@).d $(DEPS_PATH)


$(NAME): $(OBJS) $(LIB) $(L_MLX) Makefile
	@echo "$(SRCS_PATH_BONUS) $(SRCS_PATH)"
	@$(CC) $(CFLAGS) $(OBJS) $(LINEFLAGS) $(LIB) $(LDFLAGS) -o $(NAME) 
	@echo "$(LIGHT_GREEN)Created $(NAME) executable$(DEF_COLOR)"

bonus: make_mlx make_lib $(NAME_BONUS)

$(OBJS_PATH_BONUS)%.o: $(SRCS_PATH_BONUS)%.c | $(MAKE_OBJ_BONUS) $(DEPS_PATH)
			@echo "hello"
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCS_BONUS) $(KEYS) -MMD -MP -c $< -o  $@
			@mv $(basename $@).d $(DEPS_PATH)
 #$(OBJS) SHOULD BE NEXT TO BOUS
$(NAME_BONUS) : $(OBJS_BONUS) #$(LIB) $(L_MLX) Makefile
		@echo "hello 2"
		@$(CC) $(CFLAGS)  $(OBJS_BONUS) $(LINEFLAGS) $(LIB) $(LDFLAGS) -o $(NAME_BONUS) 
		@echo "$(LIGHT_GREEN)Created $(NAME_BONUS) executable$(DEF_COLOR)"

make_lib:
	@$(MAKE) -s -C $(LIB_PATH)
	@echo "$(BLUE)Done checking Libft! $(DEF_COLOR)"
make_mlx:
	@$(MAKE) -s -C $(MLX_PATH)
	@echo "$(BLUE)Done checking MLX! $(DEF_COLOR)"

$(MAKE_OBJ_BONUS):
	@echo "$(GREEN)Creating $(NAME) Obj_Bonus Dir $(DEF_COLOR)"
	@mkdir -p $(MAKE_OBJ_BONUS)

$(MAKE_OBJ_DIR):
	@echo "$(GREEN)Creating $(NAME) Obj Dir $(DEF_COLOR)"
	@mkdir -p $(MAKE_OBJ_DIR)

$(DEPS_PATH):
	@echo "$(GREEN)Creating $(NAME) Deps Dir $(DEF_COLOR)"
	@mkdir -p $(DEPS_PATH)

-include $(DEPS) $(DEPS_BONUS)

fclean_lib:
	@$(MAKE) fclean -s -C $(LIB_PATH)

clean_lib:
	@$(MAKE) clean -s -C $(LIB_PATH) 


clean: clean_lib clean_objects

fclean:  clean_objects fclean_lib
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"

clean_objects:
	@echo "$(GREEN)$(NAME) Objects and Dependencies cleaned!$(DEF_COLOR)"
	@$(RM) -r $(OBJS_PATH) $(DEPS_PATH)


re: fclean all 

.PHONY: all fclean clean re 
