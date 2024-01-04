#include <cub3d.h>

int main(int argc, char *argv[])
{
    t_prg prg;

    if (argc != 2)
        exit_error(INCORRECT_USE, NULL);
    init_prg(&prg);
    validate_map(argv[1], &prg);
    //for (int i = 0; prg.imgs[i]; i++)
        //ft_printf(1, "I have the address  <%s>\n", prg.imgs[i]);

    exit_success(&prg);
}