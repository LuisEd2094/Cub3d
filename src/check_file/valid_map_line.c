#include "parse_file.h"

bool check_valid_char(char c, t_parseer *p)
{
    int i;

    i = 0;
    while (p->valid_map_chars[i])
    {
        if (p->valid_map_chars[i] == c)
        {
            if (i > 2)
            {
                if (!p->found_player)
                    p->found_player = 1;
                else
                    return (false);
            }
            return (true);
        }
        i++;
    }
    return (false);
}



bool check_if_new_line(char *line, t_parseer *p)
{
    if (!line[0] && !p->found_map)
        return (true);
    else if (!line[0] && p->found_map && !p->found_new_line_btwn_maps)
    {
        p->found_new_line_btwn_maps = 1;
        return (true);
    }
    return (false);   
}

bool valid_map_line(char * line, t_parseer *p)
{
    int i;
    bool has_space;
    bool has_char;

    if (check_if_new_line(line, p))
        return (true);
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