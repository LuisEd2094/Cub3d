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

void check_img_file(char **elemts, t_prg *p)
{
    // should check if it can open or something, not sure still but at the momment it just creates a new char*
    if (check_2d_array_size(elemts) > 2)
        p->error_msg = MISCONFIG;
    else
    {
        if (ft_strcmp(elemts[0], "NO") == 0)
            p->north_img = ft_strdup(elemts[1]);
        else if (ft_strcmp(elemts[0], "SO") == 0)
            p->south_img = ft_strdup(elemts[1]);
        else if (ft_strcmp(elemts[0], "WE") == 0)
            p->west_img = ft_strdup(elemts[1]);
        else
            p->east_img = ft_strdup(elemts[1]);
    }
}

bool check_rgb(char **elem, t_parseer *p)
{
    int     i;
    int     j;
    int     k;
    int     l;
    char    **values;
    bool    error;

    i = -1;
    error =  0;
    l = -1;
    while (elem[++i])
    {
        values = ft_split(elem[i], ','); // cgecj what this prints
        if (!values)
            return (0);
        j = -1;
        while(values[++j] )
        {
            k = -1;
            while(ft_isdigit(values[j][k]))
                k++;
            if (values[j][k])
                error = 1;
            if (!check_if_int(values[j]))
                error = 1;
            else
            {
                l++;
                if (l > 3)
                    error = 1;
                else 
                    p->rgb_str[l] = ft_strdup(values[j]);
            }
        }
        free_2d_array(values);
        if (error)
            return (0);

    }
    return (1);
    

    for (int i = 0; elem[i]; ++i)
        ft_printf(1, "%s\n", elem[i]);
    if (elem)
        return 1;
}

void get_rgb_vals(char **elem, int array[4], t_prg *p)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (i < 3 && j < 3)
    {
        array[j] = ft_atoi(elem[i]);
        if (array[j] < 0 || array[j] > 255)
        {
            p->error_msg = RGB_ERROR;
            return;
        }
        j++;
        i++;
    }
}

void check_ceil_floor_vals(t_prg *p, char **elem, t_parseer *parse)
{
    if (!check_rgb(elem, parse))
        p->error_msg = RGB_ERROR;
    else
    {
        if (ft_strcmp(elem[0], "F") == 0)
            get_rgb_vals(parse->rgb_str, p->floor_vals, p);
        else
            get_rgb_vals(parse->rgb_str, p->ceiling_vals, p);
        free_2d_array(parse->rgb_str);
    }
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
            check_img_file(elemts, prg);
            //ft_printf(1, "I just saved an addres <%s><%i>\n", prg->imgs[i], i);
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
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        check_elements(&parse, line, prg);
        free(line);
        if (prg->error_msg || errno)
            return (false);
        check_if_found_all(&parse);
    }
    return (true);
}