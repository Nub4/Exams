#include "micro.h"

int ft_print_exit(char *s, int ret, t_all *a)
{
    int i;

    i = -1;
    while (s[++i])
        write(1, &s[i], 1);
    if (ret == 2)
        fclose(a->f);
    else if (ret == 3)
    {
        fclose(a->f);
        free(a->array);
        a->array = NULL;
    }
    return (1);
}

int ft_background(t_all *a)
{
    int count;
    int i;

    i = -1;
    if ((count = fscanf(a->f, "%d %d %c\n", &a->b_width, &a->b_height, &a->b_c)) != 3)
        return (1);
    if (count == -1)
        return (1);
    if (a->b_width > 300 || a->b_width <= 0 || a->b_height > 300 || a->b_height <= 0)
        return (1);
    if (!(a->array = (char *)malloc(sizeof(char) * (a->b_width * a->b_height))))
        return (1);
    while (++i < a->b_height * a->b_width)
        a->array[i] = a->b_c;
    return (0);
}

int ft_intersect(t_all *a, int x, int y)
{
    float check;

    check = 1.00000000;
    if ((x < a->x) || (a->x + a->width < x) || (y < a->y) || (a->y + a->height < y))
        return (0);
    if (((x - a->x) < check) || ((a->x + a->width) - x < check) || ((y - a->y) < check) || ((a->y + a->height) - y < check))
        return (2);
    return (1);
}

void    ft_save(t_all *a)
{
    int x;
    int y;
    int hit;

    y = 0;
    while (y < a->b_height)
    {
        x = 0;
        while (x < a->b_width)
        {
            hit = ft_intersect(a, x, y);
            if ((hit == 2 && a->type == 'r') || (hit && a->type == 'R'))
                a->array[(y * a->b_width) + x] = a->c;
            x++;
        }
        y++;
    }
}

int ft_check(t_all *a)
{
    if ((a->type == 'R' || a->type == 'r') && a->width > 0 && a->height > 0)
        return (0);
    return (1);
}

int ft_draw(t_all *a)
{
    int count;

    while ((count = fscanf(a->f, "%c %f %f %f %f %c\n", &a->type, &a->x, &a->y, &a->width, &a->height, &a->c)) == 6)
    {
        if (ft_check(a) == 1)
            return (1);
        ft_save(a);
    }
    if (count != -1)
        return (1);
    return (0);
}

void    ft_print(t_all *a)
{
    int i;

    i = -1;
    while (++i < a->b_height)
    {
        write(1, a->array + (a->b_width * i), a->b_width);
        write(1, "\n", 1);
    }
}

int ft_execute(t_all *a, char **av)
{
    if (!(a->f = fopen(av[1], "r")))
        return (1);
    if (ft_background(a) == 1)
        return (2);
    if (ft_draw(a) == 1)
        return (3);
    ft_print(a);
    fclose(a->f);
    free(a->array);
    a->array = NULL;
    return (0);
}

int main(int ac, char **av)
{
    t_all a;
    int ret;

    if (ac != 2)
        return (ft_print_exit("Error: argument\n", 1, &a));
    ret = ft_execute(&a, av);
    if (ret)
        return (ft_print_exit("Error: Operation file corrupted\n", ret, &a));
    return (0);
}