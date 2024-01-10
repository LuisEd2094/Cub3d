#include "parse_file.h"

bool free_list(t_parseer *parse, bool return_val)
{
    ft_lstclear(&(parse->list), free);
    return (return_val);
}