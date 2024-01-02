#include <cub3d.h>

void exit_error(char *error)
{
    print_error(error);
    if (!error)
        exit(errno);
    else
        exit(EXIT_FAILURE);
}