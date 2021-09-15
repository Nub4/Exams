#ifndef MICRO_H
# define MICRO_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define TYPE_END 3
# define TYPE_PIPE 4
# define TYPE_BREAK 5

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