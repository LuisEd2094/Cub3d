#include "parse_file.h"

bool init_map(t_parseer *p, t_prg *prg)
{
    p->list_size = ft_lstsize(p->list);
    prg->map =(char **)malloc(sizeof(char *) * (p->list_size + 1));
    if (!prg->map)
        return (false);
    return (true);
}



bool get_map_to_prg(t_prg *prg, t_parseer *parse)
{
    int i; 
    t_list *curr;
    t_list *next;

    if (!init_map(parse, prg))
        return (free_list(parse, false));
    i = -1;
    curr = parse->list;
    while (++i < parse->list_size)
    {
        prg->map[i] = ft_strdup(curr->content);
        if (!prg->map[i])
            return (free_list(parse, false));
        curr = curr->next;
    }
    prg->map[i] = NULL;
    return (check_map_borders(prg, parse));
}