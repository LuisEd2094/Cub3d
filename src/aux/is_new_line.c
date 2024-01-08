#include <stdbool.h>

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