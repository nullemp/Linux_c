#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_childproc(int sig);
int setnonblock(int fd);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len, state;
    char buf[BUF_SIZE];

    if (argc != 2)
    {
        printf("Usgae : %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = read_childproc; // proventing zombie process
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);         // register signal handler
    
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // create server-side socket
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1) // assign ip address and port
        error_handling("bind() error");
    
    if (listen(serv_sock, 5) == -1) // socket referred to by sockfd as a passive socket, that will be used to accept incomming connections requestions 
        error_handling("listen() error");

    while (1)
    {
        adr_sz = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
        if (clnt_sock == -1)
            continue;
        else
            puts("new client connected...");
        pid = fork(); // child process also has socket fd
        if (pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        if (pid == 0) // child process
        {
            close(serv_sock); // close the passive socket in the child proscess
           /*
			while ((str_len = read(clnt_sock, buf, BUFSIZ)) != 0)
                write(clnt_sock, buf, str_len);
			*/
			setnonblock(clnt_sock);
			while(1)
			{
				str_len = read(clnt_sock, buf, BUFSIZ);
				if (str_len == 0)
					break;
				else if (str_len < 0)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
					{
						// just to verify happened EAGAIN
						fprintf(stderr, "Error! %s\n", strerror(errno));	
						continue;
					}
					else
						break;
				}
				else
				{
					write(clnt_sock, buf, str_len);
				}
			}
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }
        else // parent process
            close(clnt_sock); 
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
void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id: %d \n", pid);
}

int setnonblock(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

