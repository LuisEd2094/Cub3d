#include <cub3d.h>
#include "parse_file.h"


void    set_valid_identifiers(t_parseer *p)
{
    p->valid_identifier[0] = "NO";
    p->valid_identifier[1] = "SO";
    p->valid_identifier[2] = "WE";
    p->valid_identifier[3] = "EA";
    p->valid_identifier[4] = "F";
    p->valid_identifier[5] = "C";
    p->valid_identifier[6] = NULL;
    
}
void    set_booleans(t_parseer* parse)
{
    init_int_array(parse->identifiers, ID_ARRAY_SIZE);
    parse->ids_found = 0;
    parse->found_all = 0;
    parse->error = 0;
}


void    init_parseer(t_parseer *parse)
{
    set_booleans(parse);
    set_valid_identifiers(parse);
}


bool is_new_line(char *element)
{
    int i;

    i = -1;
    while (element[++i])
    {
        if (element[i] != '\n')
            return (false);
    }
    return (true);
}

int save_elem_to_prg(t_parseer *parse, char **elemts, t_prg *prg, int i)
{
    if (parse->identifiers[i])
        return (1);
    else
    {
        parse->identifiers[i] = 1;
        parse->ids_found += 1;
    }
    return (0);
}

int check_for_identifiers(t_parseer *parse, char **elements, t_prg *prg)
{
    int i;
    int result;

    i = 0;
    while (i < ID_ARRAY_SIZE && !parse->error)
    {
        result = ft_strcmp(parse->valid_identifier[i], elements[0]);
        if (!result) // Found a match
            return (save_elem_to_prg(parse, elements, prg, i));
        i++;
    }
    return (result); // Went through everything with no match
} 


void check_elemets(t_parseer *parse, char *line, t_prg *prg)
{
    char    **elements;
    int     i;
    int     result;

    elements = ft_split(line, ' ');
    if (!elements)
        exit_error(NULL);
    if (is_new_line(elements[0]))
    {
        free_2d_array(elements);
        return ;
    }
    result = check_for_identifiers(parse, elements, prg);
    if (result)
        parse->error = 1;
    free_2d_array(elements);
}

void check_if_found_all(t_parseer *p)
{
    if (p->ids_found == ID_ARRAY_SIZE - 1)
        p->found_all = 1;
    ft_printf(1, "<%i> ids found\n", p->ids_found);
}

bool parse_file(int fd, t_prg *prg)
{
    t_parseer   parse;
    char        *line;

    init_parseer(&parse);
    line = "";
    while(line && !parse.found_all)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        check_elemets(&parse, line, prg);
        free(line);
        if (parse.error)
            return (false);
        check_if_found_all(&parse);
    }
    return (true);
}