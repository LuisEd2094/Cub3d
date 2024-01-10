#include "parse_file.h"


void check_img_file(char **elemts, t_prg *p)
{
    if (check_2d_array_size(elemts) > 2)
        p->error_msg = MISCONFIG;
    else if (check_if_invalid_ext(elemts[1], ".xml", ft_strlen(".xml")))
        p->error_msg = INCORRECT_FILE;
    else
    {
        if (ft_strcmp(elemts[0], "NO") == 0)
            p->north_img = open(elemts[1], O_RDONLY);
        else if (ft_strcmp(elemts[0], "SO") == 0)
            p->south_img = open(elemts[1], O_RDONLY);
        else if (ft_strcmp(elemts[0], "WE") == 0)
            p->west_img = open(elemts[1], O_RDONLY);
        else
            p->east_img = open(elemts[1], O_RDONLY);
    }
}