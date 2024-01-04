#include <cub3d.h>

void exit_error(char *error, t_prg *prg)
{
    if (error)
    {
        ft_printf(STDERR_FILENO, error);
        exit(EXIT_FAILURE);
    }   
    else
    {
        if (errno)
        {
            perror("Error");
            //should checkk mallocs tofree them
            exit(errno);
        }
        else
        {
            ft_printf(STDERR_FILENO, prg->error_msg);
            exit(EXIT_FAILURE);
        }
    }
}