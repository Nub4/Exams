#ifndef MICRO_H
# define MICRO_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct      s_all
{
    char            **av;
    int             size;
    int             type;
    int             fd[2];
    struct s_all    *prev;
    struct s_all    *next;
}                   t_all;

#endif