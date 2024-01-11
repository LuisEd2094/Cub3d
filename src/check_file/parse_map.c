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
    if (!line)
        prg->error_msg = NO_MAP;
    return (line);
}

bool init_map(t_parseer *p, t_prg *prg)
{
    p->list_size = ft_lstsize(p->list);
    prg->map =(char **)malloc(sizeof(char *) * (p->list_size + 1));
    if (!prg->map)
        return (false);
    return (true);
}

void prepare_parse_vals(t_prg *prg, t_parseer *parse, int i)
{
    if (i > 0)
        parse->prev_len = ft_strlen(prg->map[i - 1]);
    if (prg->map[i + 1])
    {
        parse->next_len = ft_strlen(prg->map[i + 1]);
        parse->next_line = prg->map[i + 1];
    }
    else
    {
        parse->next_len = 0;
        parse->next_line = NULL;
    }
}

bool check_map_borders(t_prg *prg, t_parseer *parse)
{
    int i;
    int j;

    i = -1;
    while (prg->map[++i])
    {
        j = -1;
        prepare_parse_vals(prg,parse, i);
        while (prg->map[i][++j])
        {
            if (prg->map[i][j] == '0')
            {
                if (i == 0 || j == 0)
                {
                    prg->error_msg = OPEN_MAP;
                    return (false);
                }
                else if (prg->map[i][j + 1] && prg->map[i][j + 1] == ' ')
                {
                    prg->error_msg = OPEN_MAP;
                    return (false);
                }
                else if (parse->next_line && j < parse->next_len && parse->next_line[j] == ' ')
                {
                    prg->error_msg = OPEN_MAP;
                    return (false);
                }
                else if (!parse->next_line || j >= parse->next_len)
                {
                    prg->error_msg = OPEN_MAP;
                    return (false);
                }
                else if (parse->prev_len > 0 && parse->prev_len <= j)
                {
                    prg->error_msg = OPEN_MAP;
                    return (false);
                }
            }
            else if (prg->map[i][j] == ' ')
            {
                if (prg->map[i][j + 1] && prg->map[i][j + 1] == '0')
                {
                    prg->error_msg = OPEN_MAP;
                    return (false);
                }
                else if (parse->next_line && j < parse->next_len && parse->next_line[j] == '0')
                {
                    prg->error_msg = OPEN_MAP;
                    return (false);
                }
            }
        }
    }
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