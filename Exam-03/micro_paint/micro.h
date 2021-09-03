#ifndef MICRO_H
# define MICRO_H

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
    float       width;
    float       height;
    char        c;
}               t_all;

#endif