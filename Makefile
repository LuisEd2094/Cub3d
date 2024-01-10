NAME        = cub3D
CFLAGS      = -g  #-fsanitize=address #-Wall -Wextra  -Werror #
RM          = rm -f
CK_FD_PATH		= check_file/
AUX_PATH		= aux/
SRCS_PATH           = src/
OBJS_PATH           = obj/
CC = cc

#BUILT INS variables


## Add new path, just need name/
MAKE_OBJ_DIR		= $(OBJS_PATH) $(addprefix $(OBJS_PATH), \
									$(CK_FD_PATH), \
									$(AUX_PATH), \
									)
										
#Add new path to objects

DEPS_PATH	= deps/
LIB_PATH	= 	./libft
LIB			=	$(LIB_PATH)/libft.a 
LDFLAGS		= 	-L$(LIB_PATH) -lft 

INCS        = -I./includes/
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
				

CK_FILES	=	$(addprefix $(CK_FD_PATH), $(CHECK))

AUX 		=	close_imgs_fd.c exit_error.c exit_success.c init_prg.c \
				init_int_array.c check_file_extension.c is_new_line.c \
				free_mallocs.c
				
AUX_FILES	= 	$(addprefix $(AUX_PATH), $(AUX))

DEPS		= 	$(addprefix $(DEPS_PATH),	$(SRC:.c=.d) \
											$(CHECK:.c=.d)\
											$(AUX:.c=.d)) 
										
										

#add .d files to deps

SRC			+= $(CK_FILES) $(AUX_FILES)
## add to sercs

OBJS        =	$(addprefix $(OBJS_PATH), $(SRC:.c=.o)) 
				

all: make_lib $(NAME)


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(MAKE_OBJ_DIR) $(DEPS_PATH)
			@echo "$(CYAN)Compiling $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o  $@
			@mv $(basename $@).d $(DEPS_PATH)


$(NAME): $(OBJS) $(LIB) Makefile
	@$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LINEFLAGS) $(LIB)-o $(NAME) $(LDFLAGS)
	@echo "$(LIGHT_GREEN)Created $(NAME) executable$(DEF_COLOR)"

make_lib:
	@$(MAKE) -s -C $(LIB_PATH)
	@echo "$(BLUE)Done checking Libft! $(DEF_COLOR)"


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


clean: clean_lib clean_objects

fclean:  clean_objects fclean_lib
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) executable cleaned!$(DEF_COLOR)"

clean_objects:
	@echo "$(GREEN)$(NAME) Objects and Dependencies cleaned!$(DEF_COLOR)"
	@$(RM) -r $(OBJS_PATH) $(DEPS_PATH)


re: fclean all 

.PHONY: all fclean clean re 