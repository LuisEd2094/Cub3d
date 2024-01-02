#include <cub3d.h>

bool print_error(char *error)
{
    if (!error)
        perror("Error");
    else 
        ft_printf(STDERR_FILENO, error);
    return (0);
}