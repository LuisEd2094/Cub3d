#include "cub3d.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        ft_printf(STDERR_FILENO, INCORRECT_USE);
    else if (!valid_map(argv[1]))
        ft_printf(STDERR_FILENO, INCORRECT_FILE);

    ft_printf(1, "Valid map");
    exit(EXIT_SUCCESS);
}