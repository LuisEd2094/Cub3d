#include <cub3d.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit_error(INCORRECT_USE);
    validate_map(argv[1]);
}