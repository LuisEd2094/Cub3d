#include <cub3d.h>

int    check_file_name(char *file_name)
{
    int     file_name_len;
    char    **split;
    char    *file;
    int     compare;

    split = ft_split(file_name, '/');
    if (!split)
        exit_error(NULL);
    file = split[check_2d_array_size(split) - 1];
    file_name_len = ft_strlen(file);
    if (file_name_len < 5)
    {
        free_2d_array(split);
        return (1);
    }
    compare = ft_strcmp(".cub", &file[file_name_len - 4]);
    free_2d_array(split);
    return (compare);
}


void    validate_map(char *file_name, t_prg *prg)
{
    int fd;

    if (check_file_name(file_name))
        exit_error(INCORRECT_FILE);
    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        exit_error(NULL);
    if(!parse_file(fd, prg))
    {
        close(fd);
        exit_error(MISCONFIG);
    }
    ft_printf(1, "VALID MAP\n");
    close(fd);
}
