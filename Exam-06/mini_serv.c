#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct  s_client
{
    int             id;
    int             socket;
    struct s_client *next; 
}               t_client;

t_client *clients = NULL;

fd_set masterfds;
fd_set readfds;
fd_set writefds;
int g_id = 0;
int fdmax;
int serverSocket;
char msg[42];
char str[42 * 4096];
char tmp[42 * 4096];
char buf[42 * 4096 + 42];

void    ft_free_all()
{
    t_client *temp = NULL;
    while (clients)
    {
        temp = clients->next;
        close(clients->socket);
        free(clients);
        clients = temp;
    }
}

void    ft_error(char *s, int status, int fd)
{
    write(fd, s, strlen(s));
    close(serverSocket);
    ft_free_all();
    exit(status);
}

int ft_addClient(int clientSocket)
{
    t_client *temp = clients;
    t_client *new;

    if (!(new = calloc(1, sizeof(t_client))))
        ft_error("Fatal error\n", 1, 2);
    new->id = g_id++;
    new->socket = clientSocket;
    new->next = NULL;
    if (!clients)
        clients = new;
    else
    {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
    return new->id;
}

void    ft_sendAll(int clientSocket, char *str_req)
{
    t_client *temp = clients;

    while (temp)
    {
        if (temp->socket != clientSocket && FD_ISSET(temp->socket, &writefds))
        {
            printf("%s", str_req);
            if (send(temp->socket, str_req, strlen(str_req), 0) < 0)
                ft_error("Fatal error\n", 1, 2);
        }
        temp = temp->next;
    }
}

void    ft_newClient()
{
    struct sockaddr_in clientaddr;
    int addrlen = sizeof(clientaddr);
    int clientSocket;

    if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientaddr, (socklen_t *)&addrlen)) < 0)
        ft_error("Fatal error\n", 1, 2);
    sprintf(msg, "server: client %d just arrived\n", ft_addClient(clientSocket));
    ft_sendAll(clientSocket, msg);
    FD_SET(clientSocket, &masterfds);
    if (clientSocket > fdmax)
        fdmax = clientSocket;
}

int ft_getId(int clientSocket)
{
    t_client *temp = clients;

    while (temp)
    {
        if (temp->socket == clientSocket)
            return temp->id;
        temp = temp->next;
    }   
    return -1;
}

int ft_rmClient(int clientSocket)
{
    t_client *temp = clients;
    t_client *del;

    int id = ft_getId(clientSocket);

    if (temp && temp->socket == clientSocket)
    {
        clients = temp->next;
        free(temp);
    }
    else
    {
        while (temp && temp->next && temp->next->socket != clientSocket)
            temp = temp->next;
        del = temp->next;
        temp->next = temp->next->next;
        free(del);
    }
    return id;
}

void    ft_exMsg(int clientSocket)
{
    int i = 0;
    int j = 0;

    while (str[i])
    {
        tmp[j] = str[i];
        j++;
        if (str[i] == '\n')
        {
            sprintf(buf, "client %d: %s", ft_getId(clientSocket), tmp);
            ft_sendAll(clientSocket, buf);
            j = 0;
            bzero(&tmp, strlen(tmp));
            bzero(&buf, strlen(buf));
        }
        i++;
    }
    bzero(&str, strlen(str));
}

int main(int ac, char **av)
{
    if (ac != 2)
        ft_error("Wrong number of arguments\n", 1, 2);

    struct sockaddr_in servaddr;
    uint16_t port = atoi(av[1]);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        ft_error("Fatal error\n", 1, 2);
    if (bind(serverSocket, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        ft_error("Fatal error\n", 1, 2);
    if (listen(serverSocket, 0) < 0)
        ft_error("Fatal error\n", 1, 2);

    FD_ZERO(&masterfds);
    FD_SET(serverSocket, &masterfds);
    fdmax = serverSocket;
    bzero(&tmp, sizeof(tmp));
    bzero(&buf, sizeof(buf));
    bzero(&str, sizeof(str));

    while (1)
    {
        readfds = writefds = masterfds;
        if (select(fdmax + 1, &readfds, &writefds, NULL, NULL) < 0)
            continue ;
        for (int i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &readfds))
            {
                if (i == serverSocket)
                {
                    bzero(&msg, sizeof(msg));
                    ft_newClient();
                    break ;
                }
                else
                {
                    int ret_recv = 1000;
                    while (ret_recv == 1000 || str[strlen(str) - 1] != '\n')
                    {
                        ret_recv = recv(i, str + strlen(str), 1000, 0);
                        if (ret_recv <= 0)
                            break ;
                    }
                    if (ret_recv <= 0)
                    {
                        bzero(&msg, sizeof(msg));
                        sprintf(msg, "server: client %d just left\n", ft_rmClient(i));
                        ft_sendAll(i, msg);
                        FD_CLR(i, &masterfds);
                        close(i);
                        break ;
                    }
                    else
                        ft_exMsg(i);
                }
            }
        }
    }
    ft_free_all();
    return 0;
}