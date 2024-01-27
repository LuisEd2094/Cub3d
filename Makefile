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
CFLAGS      = -g  #-fsanitize=address #-Wall -Wextra  -Werror #
RM          = rm -f
CK_FD_PATH		= check_file/
GAME_PATH		= game/
AUX_PATH		= aux/
BONUS_PATH		= bonus/
SRCS_PATH           = src/
OBJS_PATH           = obj/
CC = cc
BONUS_FLAG 	= 0
HIDDEN_BONUS_FILE	= .bonus_checker
MACRO_FLAG = $(shell cat $(HIDDEN_BONUS_FILE) 2>/dev/null)

# Check if the target is 'bonus' and set BONUS_FLAG accordingly

GOALS_CONTAIN_BONUS := $(if $(filter bonus,$(MAKECMDGOALS)),yes,no)
ifeq ($(GOALS_CONTAIN_BONUS),yes)
    BONUS_FLAG := 1
endif
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
MAKE_OBJ_DIR		= $(OBJS_PATH) $(addprefix $(OBJS_PATH), \
									$(CK_FD_PATH), \
									$(AUX_PATH), \
									$(GAME_PATH), \
									)

MAKE_OBJ_DIR_BONUS	= $(addprefix $(OBJS_PATH),	$(BONUS_PATH))
OBJS_BONUS_DIR = $(MAKE_OBJ_DIR_BONUS)
										
#Add new path to objects


ifeq ($(OS), Linux)
MLX_PATH = ./minilibx-linux/
FRAME = -lXext -lX11 -lm -lz
KEYS = -D LINUX_KEYS=1
else
MLX_PATH = ./minilibx_opengl_20191021/
FRAME = -framework OpenGL -framework AppKit
KEYS = 
endif



LDFLAGS		= 	-L$(LIB_PATH) -lft -lm -L$(MLX_PATH) -lmlx $(FRAME)

INCS        = -I./includes/ -I$(LIB_PATH)/includes
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
				free_mallocs.c ft_max.c ft_min.c
				
AUX_FILES	= 	$(addprefix $(AUX_PATH), $(AUX))

GAME		=	hooks.c  update_window.c \
				make_move.c ray.c rotate_player.c raycaster.c

GAME_FILES	=	$(addprefix $(GAME_PATH), $(GAME))


## B_FLAG_FILES ARE FILES USED BY THE BONUS AND NORMAL GAME. They compile differenly depending on the Bonus flag passed, so we need to check and compile them directly
#if we change from one program to the other

## BONUS FILES are just the bonus files, they are not used by the normal program

B_FLAG_FILE	=	$(SRCS_PATH)$(CK_FD_PATH)check_map_borders.c $(SRCS_PATH)$(CK_FD_PATH)init_parseer.c \
				$(SRCS_PATH)$(CK_FD_PATH)get_map_to_prg.c $(SRCS_PATH)$(GAME_PATH)update_window.c \
				$(SRCS_PATH)$(GAME_PATH)make_move.c $(SRCS_PATH)$(GAME_PATH)rotate_player.c \
				$(SRCS_PATH)$(GAME_PATH)hooks.c

BONUS		=	draw_map_bonus.c triangle_bonus.c open_door_bonus.c

BONUS_FILE	=	$(addprefix $(BONUS_PATH), $(BONUS))

DEPS		= 	$(addprefix $(DEPS_PATH),	$(SRC:.c=.d) \
											$(CHECK:.c=.d)\
											$(AUX:.c=.d) \
											$(GAME:.c=.d) \
											$(BONUS:.c=.d)) 
										
										

#add .d files to deps

SRC			+= $(CK_FILES) $(AUX_FILES) $(GAME_FILES)
## add to sercs

OBJS        =	$(addprefix $(OBJS_PATH), $(SRC:.c=.o)) 

OBJS_BONUS	=	$(addprefix $(OBJS_PATH), $(BONUS_FILE:.c=.o))
				

all: check_files_bonus_flag make_mlx make_lib $(NAME)


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(MAKE_OBJ_DIR) $(DEPS_PATH)
		@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
		@$(CC) $(CFLAGS) $(INCS) $(KEYS) -DBONUS_FLAG=$(BONUS_FLAG) -MMD -MP -c $< -o  $@
		@mv $(basename $@).d $(DEPS_PATH)


$(NAME):  $(HIDDEN_BONUS_FILE) $(OBJS) $(LIB) $(L_MLX) Makefile
	@$(CC) $(CFLAGS) $(OBJS) $(LINEFLAGS) $(LIB) $(LDFLAGS) -o $(NAME)
	@echo "$(LIGHT_GREEN)Created $(NAME) executable$(DEF_COLOR)"

bonus: check_files_bonus_flag make_mlx make_lib $(NAME_BONUS)


$(MAKE_OBJ_DIR_BONUS)%.o: $(SRCS_PATH)$(BONUS_PATH)%.c | $(MAKE_OBJ_DIR) $(MAKE_OBJ_DIR_BONUS) $(DEPS_PATH) 
	@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(INCS) $(KEYS) -DBONUS_FLAG=$(BONUS_FLAG) -MMD -MP -c $< -o  $@
	@mv $(basename $@).d $(DEPS_PATH)

# SHOULD HAVE A RULE TO MAKE SRS_BONUS

$(NAME_BONUS):  $(HIDDEN_BONUS_FILE) $(OBJS) $(OBJS_BONUS) Makefile 
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(OBJS_BONUS) $(LINEFLAGS) $(LIB)-o $(NAME_BONUS) $(LDFLAGS)
	@echo "$(LIGHT_GREEN)Created $(NAME_BONUS) executable$(DEF_COLOR)"

$(HIDDEN_BONUS_FILE):
	@if [ ! -e $(HIDDEN_BONUS_FILE) ]; then \
		echo $(BONUS_FLAG) > $(HIDDEN_BONUS_FILE); \
	fi
	
check_files_bonus_flag:
	@if ([ "$(strip $(MACRO_FLAG))" = "0" ] && [ $(BONUS_FLAG) -eq 1 ]) || ([ "$(strip $(MACRO_FLAG))" = "1" ] && [  $(BONUS_FLAG) -eq 0 ]) ; then \
		echo "$(GREEN)Recompiling files with bonus flag $(DEF_COLOR)";\
		for file in $(B_FLAG_FILE); do \
			obj_file=obj/$${file#src/}; \
			echo "$(CYAN)Compiling $$file $(DEF_COLOR)"; \
			$(CC) $(CFLAGS) $(INCS) $(KEYS) -DBONUS_FLAG=$(BONUS_FLAG) -MMD -MP -c $$file -o $${obj_file%.c}.o; \
			mv $${obj_file%.c}.d $(DEPS_PATH);\
		done; \
		echo $(BONUS_FLAG) > $(HIDDEN_BONUS_FILE);\
	fi 

make_lib:
	@$(MAKE) -s -C $(LIB_PATH)
	@echo "$(BLUE)Done checking Libft! $(DEF_COLOR)"

make_mlx:
	@$(MAKE) -s -C $(MLX_PATH)
	@echo "$(BLUE)Done checking MLX! $(DEF_COLOR)"

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
	@$(RM) $(HIDDEN_BONUS_FILE)
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"

clean_objects:
	@echo "$(GREEN)$(NAME) Objects and Dependencies cleaned!$(DEF_COLOR)"
	@$(RM) -r $(OBJS_PATH) $(DEPS_PATH)

re: $(RE_RULE_TARGET)

.PHONY: all fclean clean re bonus clean_objects clean_lib fclean_lib make_mlx make_lib check_files_bonus_flag
