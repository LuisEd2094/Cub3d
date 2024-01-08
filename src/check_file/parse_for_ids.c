#include <cub3d.h>
#include "parse_file.h"

void save_elem_to_prg(t_parseer *parse, char **elemts, t_prg *prg, int i)
{
    if (parse->identifiers[i])
        prg->error_msg = REPEATED;
    else
    {
        parse->identifiers[i] = 1;
        parse->ids_found += 1;
        if (i < 4) // IS N/S/E/W
        {
            check_img_file(elemts, prg);
        }
        else
        {
            check_ceil_floor_vals(prg, elemts, parse);
        }
    }
}

void check_for_identifiers(t_parseer *parse, char **elements, t_prg *prg)
{
    int i;

    i = 0;
    while (i < ID_ARRAY_SIZE - 1 && !prg->error_msg)
    {
        if (ft_strcmp(parse->valid_identifier[i], elements[0]) == 0) // Found a match
            return (save_elem_to_prg(parse, elements, prg, i));
        i++;
    }
    prg->error_msg = MISCONFIG;
    return; // Went through everything with no match
} 

bool check_valid_line(char *line, t_prg *p)
{
    int i;

    if (!line[0])
        return (0);
    if (!ft_isalnum(line[ft_strlen(line) - 1]))
    {
        p->error_msg = MISCONFIG;
        return (0);
    }
    return (1);
}


void check_elements(t_parseer *parse, char *line, t_prg *prg)
{
    char    **elements;

    if (!check_valid_line(line, prg))
        return ;
    elements = ft_split(line, ' ');
    if (!elements)
        return; 
    check_for_identifiers(parse, elements, prg);
    free_2d_array(elements);
}

void check_if_found_all(t_parseer *p)
{
    if (p->ids_found == ID_ARRAY_SIZE - 1)
        p->found_all = 1;
}

bool    parse_for_ids(int fd, t_prg *prg, t_parseer *parse)
{
    char    *line;

    line = "";
    while(line && !parse->found_all)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        check_elements(parse, line, prg);
        free(line);
        if (prg->error_msg || errno)
            return (false);
        check_if_found_all(parse);
    }
    return (true);
}