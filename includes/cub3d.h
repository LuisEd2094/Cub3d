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



// AUX FUNCTIONS 
bool    print_error(char *error);
void    exit_error(char *error);

// CHECK FILE FUNCTIONS
void    validate_map(char *file_name);
bool    parse_file(int fd);

#endif