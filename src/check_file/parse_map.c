#include "parse_file.h"

char *get_start_map(int fd, t_prg *prg)
{
    char *line;
    
    line = get_next_line(fd);
    while (line && is_new_line(line))
    {
        free(line);
        line = get_next_line(fd);
        if (!line)
            break;
    }
    if (!line || !is_new_line(line))
    {
        prg->error_msg = NO_MAP;
    }
    return (line);

}

bool check_valid_char(char c, t_parseer *p)
{
    int i;

    i = 0;
    while (p->valid_map_chars[i])
    {
        if (p->valid_map_chars[i] == c)
            return (true);
        i++;
    }
    return (false);
}


bool valid_map_line(char * line, t_parseer *p)
{
    int i;
    bool has_space;
    bool has_char;

    if (!line[0] && !p->found_map)
        return (true);
    if (!line[0] && p->found_map && !p->found_new_line_btwn_maps)
    {
        p->found_new_line_btwn_maps = 1;
        return (true);
    }
    i = -1;
    has_space = 0;
    has_char = 0;
    while (line[++i])
    {
        if (!check_valid_char(line[i], p) || p->found_new_line_btwn_maps)
            return (false);
        if (line[i] == ' ' && !has_space)
            has_space = 1;
        if (!has_char && line[i] != ' ')
            has_char = 1;
    }
    if (!p->found_map)
        p->found_map = 1; // first time we find a valid line we mark it, so we can check later if there is a line in the middle of the map
    return (!(has_space && !has_char));
}


bool parse_map(int fd, t_prg *prg, t_parseer *parse)
{
    char *line;
    t_list *node;

    line = get_start_map(fd, prg);
    if (!line)
        return (false);
    while (line)
    {
        if (line[ft_strlen(line) - 1] == '\n')
            line[ft_strlen(line) - 1] = '\0';
        if (!valid_map_line(line, parse))
        {
            ft_lstclear(&(parse->list), free);
            free(line);
            prg->error_msg = WRONG_MAP;
            return (false);
        }
        if (!line[0])
        {
            free(line);
            line = get_next_line(fd);
            continue ;
        }
        node = ft_lstnew(line);
        if (!node)
        {
            ft_lstclear(&(parse->list), free);
            free(line);
            return (false);
        }
        ft_lstadd_back(&(parse->list), node);
        line = get_next_line(fd);
    }


    ft_lstiter(parse->list, (void *)(printf));
    ft_lstclear(&(parse->list), free);
    return (true);
}