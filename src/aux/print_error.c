#include "ft_printf.h"
#include <stdbool.h>

bool print_error(char *error)
{
    ft_printf(STDERR_FILENO, error);
    return (0);
}