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

char *check_img_file(char *img_file)
{
    // should check if it can open or something, not sure still but at the momment it just creates a new char*
    return (ft_strdup(img_file));
}

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
            prg->imgs[i] = check_img_file(elemts[1]);
            //ft_printf(1, "I just saved an addres <%s><%i>\n", prg->imgs[i], i);
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

    i = ft_strlen(line);
    if (i == 1)
        return (1);
    if (!ft_isalnum(line[i - 2]))
    {
        p->error_msg = MISCONFIG;
        return (0);
    }
    return (1);
}

bool check_elem_sizes_and_new_line(char **elements, t_prg *p)
{
    if (check_2d_array_size(elements) > 2)
    {
        free_2d_array(elements);
        p->error_msg = MISCONFIG;
        return (1);
    }
    if (is_new_line(elements[0]))
    {
        free_2d_array(elements);
        return (1);
    }
    return (0); // return 0 only if we shuld check the elemts, such as it has less than 3 values or it's not just a new line
}

void check_elemets(t_parseer *parse, char *line, t_prg *prg)
{
    char    **elements;

    if (!check_valid_line(line, prg))
        return ;
    elements = ft_split(line, ' ');
    if (!elements)
        return; 
    if (check_elem_sizes_and_new_line(elements, prg))
        return ;
    //for (int i = 0; elements[i]; ++i)
      //  ft_printf(1, "<%s> string\n", elements[i]);
    check_for_identifiers(parse, elements, prg);
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
        if (prg->error_msg || errno)
            return (false);
        check_if_found_all(&parse);
    }
    return (true);
}