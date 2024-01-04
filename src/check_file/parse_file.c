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
    return (0); //return 0 for valid maps
}

int check_for_identifiers(t_parseer *parse, char **elements, t_prg *prg)
{
    int i;
    int result;

    i = 0;
    while (i < ID_ARRAY_SIZE - 1 && !parse->error)
    {
        result = ft_strcmp(parse->valid_identifier[i], elements[0]);
        if (!result) // Found a match
            return (save_elem_to_prg(parse, elements, prg, i));
        i++;
    }
    return (result); // Went through everything with no match
} 

void check_valid_line(char *line)
{
    int i;

    i = ft_strlen(line);
    if (i == 1)
        return ;
    if (!ft_isalnum(line[i - 2]))
        exit_error(MISCONFIG);
}

bool check_elem_sizes_and_new_line(char **elements)
{
    if (check_2d_array_size(elements) > 2)
    {
        free_2d_array(elements);
        exit_error(MISCONFIG);
    }
    if (is_new_line(elements[0]))
    {
        free_2d_array(elements);
        return (1);
    }
    return (0);
}

void check_elemets(t_parseer *parse, char *line, t_prg *prg)
{
    char    **elements;
    int     result;

    check_valid_line(line);
    elements = ft_split(line, ' ');
    if (!elements)
        exit_error(NULL);
    if (check_elem_sizes_and_new_line(elements))
        return ;
    //for (int i = 0; elements[i]; ++i)
      //  ft_printf(1, "<%s> string\n", elements[i]);
    result = check_for_identifiers(parse, elements, prg);
    if (result)
        parse->error = 1;
    free_2d_array(elements);
}

void check_if_found_all(t_parseer *p)
{
    if (p->ids_found == ID_ARRAY_SIZE - 1)
        p->found_all = 1;
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