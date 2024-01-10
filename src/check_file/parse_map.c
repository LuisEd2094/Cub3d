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
        prg->error_msg = NO_MAP;
    return (line);
}

bool get_map_to_prg(t_prg *prg, t_parseer *parse)
{
    int i; 
    int size;
    t_list *node;

    size = ft_lstsize(parse->list);
    prg->map =(char **)malloc(sizeof(char *) * (size + 1));
    if (!prg->map)
        return (free_list(parse, false));
    i = -1;
    node = parse->list;
    while (++i < size)
    {
        prg->map[i] = ft_strdup(node->content);
        if (!prg->map[i])
            return (free_list(parse, false));
        node = node->next;
    }
    prg->map[i] = NULL;
    return (true);
}

bool parse_map(int fd, t_prg *prg, t_parseer *parse)
{
    char *line;

    line = get_start_map(fd, prg);
    if (!line)
        return (false);
    if (!get_map_to_list(fd, prg, parse, line) || !parse->found_player) // get_map sets found player
        return (free_list(parse, false));
    if (!get_map_to_prg(prg, parse))
        return(free_list(parse, false));
    ft_lstiter(parse->list, (void *)(printf));
    return (free_list(parse, true));
}