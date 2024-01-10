#include "parse_file.h"



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