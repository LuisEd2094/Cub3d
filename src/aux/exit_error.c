#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void    exit_error(void)
{
    perror("Error");
    exit(errno);
}