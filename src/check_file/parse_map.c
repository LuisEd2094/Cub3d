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