#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>

typedef struct  s_all
{
    char        *array;
    FILE        *f;

    int         b_width;
    int         b_height;
    char        b_c;

    char        type;
    float       x;
    float       y;
    float       rad;
    char        c;
}               t_all;

#endif
