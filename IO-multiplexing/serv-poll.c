#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <poll.h>

#define BUF_SIZE 100
#define FD_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    //fd_set reads, reads_bak;
	struct pollfd pfd[FD_SIZE] = {0};
    socklen_t adr_sz;
    int fd_max, str_len, fd_num, i;
    char buf[BUF_SIZE];
    int fd_nums = 0;
	int j = 0;

	if (argc != 2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
	if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

	/*
    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads); // register server sock to 'read' event
    fd_max = serv_sock;
	*/
	pfd[0].fd = serv_sock;
	pfd[0].events |= POLLIN;
    ++fd_nums;

    while (1)
    {
		/*
        reads_bak= reads;
        timeout.tv_sec = 3;
        timeout.tv_usec = 3000;
		*/
        if ((fd_num = poll(pfd, fd_nums, -1) < 0)) // start listening, re-listen each time
            break; // TODO: need modify, because of the signal

		for (j = 0; j < FD_SIZE; j++)	
		{		
			if (pfd[j].revents & POLLIN) // find sockets that have changed
			{
				if (pfd[j].fd == serv_sock) // if it's the server-side sock, accept the connection request
				{
					adr_sz = sizeof(clnt_adr);
					clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);

					pfd[fd_nums].fd = clnt_sock; // register one clnt_sock
					pfd[fd_nums].events |= POLLIN;
					++fd_nums;
					printf("Connected client: %d \n", clnt_sock);
				}
				else // not a server-side socket
				{
					str_len = read(pfd[j].fd, buf, BUF_SIZE); // variable i represents the client issuing the request currently
					if (str_len == 0)
					{
					   // FD_CLR(i, &reads);
						pfd[j].fd = 0;
						pfd[j].events = 0;
						close(i);
						printf("closed client: %d \n", i);
					}
					else
					{
						write(pfd[j].fd, buf, str_len);
					}
				}
			}
		}
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
