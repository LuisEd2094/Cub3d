#include <cub3d.h>

void exit_error(char *error, t_prg *prg)
{
    free_prg_mallocs(prg);
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
            exit(errno);
        }
        else
        {
            ft_printf(STDERR_FILENO, prg->error_msg);
            exit(EXIT_FAILURE);
        }
    }
}