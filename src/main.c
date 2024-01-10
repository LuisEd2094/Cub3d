#include <cub3d.h>

int main(int argc, char *argv[])
{
    t_prg prg;

    init_prg(&prg);
    if (argc != 2)
        exit_error(INCORRECT_USE, &prg);
    validate_map(argv[1], &prg);
    for (int i = 0; i < 3; i++)
        ft_printf(1, "RGB >%i<\n", prg.floor_vals[i]);
    for (int i = 0; i < 3; i++)
        ft_printf(1, "RGB >%i<\n", prg.ceiling_vals[i]);
    ft_printf(1, "VALID MAP\n");

    exit_success(&prg);
}