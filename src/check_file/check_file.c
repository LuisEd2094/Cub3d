#include "cub3d.h"
#include <errno.h>
int    check_file_name(char *file_name)
{
    int     file_name_len;
    char    **split;
    char    *file;
    int     compare;

    split = ft_split(file_name, '/');
    if (!split)
        exit_error();
    file = split[check_2d_array_size(split) - 1];
    file_name_len = ft_strlen(file);
    if (file_name_len < 5)
    {
        free_2d_array(split);
        return (0);
    }
    compare = ft_strcmp(".cub", &file[file_name_len - 4]);
    free_2d_array(split);
    return (compare);
}


bool    valid_map(char *file_name)
{
    if (check_file_name(file_name))
        return (false);
    return (true);
}
