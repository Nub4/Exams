#include "micro.h"

void    ft_free_all(t_all *a)
{
    t_all *temp;
    int i;

    while (a)
    {
        temp = a->next;
        i = -1;
        while (++i < a->size)
            free(a->av[i]);
        free(a->av);
        free(a);
        a = temp;
    }
    a = NULL;
}

int ft_strlen(char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}

int ft_size_av(char **av)
{
    int i;

    i = 0;
    while (av[i] && strcmp(av[i], "|") != 0 && strcmp(av[i], ",") != 0)
        i++;
    return (i);
}

void    ft_exit(char *s, int ret)
{
    if (ret == 1)
        write(2, "error: fatal\n", 13);
    else if (ret == 2)
        write(2, "error: :cd bad arguments\n", 25);
    else if (ret == 3)
    {
        write(2, "error: cd: cannot change directory to ", 38);
        write(2, s, ft_strlen(s));
        write(2, "\n", 1);
    }
    else if (ret == 4)
    {
        write(2, "error: cannot execute ", 22);
        write(2, s, ft_strlen(s));
        write(2, "\n", 1);
    }
    exit(1);
}

char    *ft_strdup(char *s)
{
    int i;
    char *new;

    i = ft_strlen(s);
    if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = -1;
    while(s[++i])
        new[i] = s[i];
    new[i] = '\0';
    return (new);
}



t_all   *ft_lstlast(t_all *a)
{
    if (a)
        while (a->next)
            a = a->next;
    return (a);
}

void    ft_lstadd_back(t_all **a, t_all *new)
{
    t_all *temp;

    if (!a || !new)
        return ;
    if (!*a)
    {
        *a = new;
        return ;
    }
    temp = ft_lstlast(*a);
    temp->next = new;
    new->prev = temp;
}

int ft_check_end(char *av)
{
    if (!av)
        return (3);
    if (strcmp(av, "|") == 0)
        return (4);
    if (strcmp(av, ";") == 0)
        return (5);
    return (0);
}

int ft_parser_av(t_all **a, char **av)
{
    int size;
    t_all *new;

    size = ft_size_av(av);
    if (!(new = (t_all *)malloc(sizeof(t_all))))
        ft_exit(NULL, 1);
    if (!(new->av = (char **)malloc(sizeof(char *) * (size + 1))))
        ft_exit(NULL, 1);
    new->size = size;
    new->next = NULL;
    new->prev = NULL;
    new->av[size] = NULL;
    while (--size >= 0)
        new->av[size] = ft_strdup(av[size]);
    new->type = ft_check_end(av[new->size]);
    ft_lstadd_back(a, new);
    return (new->size);
}

void    ft_exec_cmd(t_all *temp, char **env)
{
    pid_t pid;
    int status;
    int pipe_open;

    pipe_open = 0;
    if (temp->type == 4 || (temp->prev && temp->prev->type == 4))
    {
        pipe_open = 1;
        if (pipe(temp->fd))
            ft_exit(NULL, 1);
    }
    pid = fork();
    if (pid < 0)
        ft_exit(NULL, 1);
    else if (pid == 0)
    {
        if (temp->type == 4 && dup2(temp->fd[1], 1) < 0)
            ft_exit(NULL, 1);
        if (temp->prev && temp->prev->type == 4 && dup2(temp->prev->fd[0], 0) < 0)
            ft_exit(NULL, 1);
        if (execve(temp->av[0], temp->av, env) < 0)
            ft_exit(temp->av[0], 4);
        exit(0);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (pipe_open)
        {
            close(temp->fd[1]);
            if (!temp->next || temp->type == 5)
                close(temp->fd[0]);
        }
        if (temp->prev && temp->prev->type == 4)
            close(temp->prev->fd[0]);
    }

}

void    ft_exec_cmds(t_all *a, char **env)
{
    t_all *temp;

    temp = a;
    while (temp)
    {
        if (strcmp("cd", temp->av[0]) == 0)
        {
            if (temp->size < 2)
                ft_exit(NULL, 2);
            else if (chdir(temp->av[1]))
                ft_exit(temp->av[1], 3);
        }
        else
            ft_exec_cmd(temp, env);
        temp = temp->next;
    }
}

int main(int ac, char **av, char **env)
{
    t_all *a;
    int i;

    a = NULL;
    i = 1;
    if (ac > 1)
    {
        while(av[i])
        {
            if (strcmp(av[i], ";") == 0)
            {
                i++;
                continue ;
            }
            i = i + ft_parser_av(&a, &av[i]);
            if (!av[i])
                break ;
            else
                i++;
        }
    }
    if (a)
        ft_exec_cmds(a, env);
    ft_free_all(a);
    return (0);
}