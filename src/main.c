#include <cub3d.h>

int main(int argc, char *argv[])
{
    t_prg prg;

    if (argc != 2)
        exit_error(INCORRECT_USE);
    init_prg(&prg);
    validate_map(argv[1], &prg);
}