#include <cub3d.h>



void    validate_map(char *file_name, t_prg *prg)
{
    int fd;

    if (check_file_name(file_name, ".cub", ft_strlen(".cub")))
        exit_error(INCORRECT_FILE, prg);
    if (errno)
        return ;
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_error(NULL, prg);
    if(!parse_file(fd, prg) || errno)
    {
        close(fd);
        exit_error(NULL, prg);
    }
    close(fd);
}
