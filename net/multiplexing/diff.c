#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
 
int main(int argc, char *argv[])
{
    int epfd, nfds;
    struct epoll_event event, events[10];
    int i;
		
    epfd = epoll_create(10);
    event.data.fd = 0;
    //event.events = EPOLLIN | EPOLLET; 
    event.events = EPOLLIN; 
    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);
	
    while (1) 
    {
        
        nfds = epoll_wait(epfd, events, 10, -1); 
 
        for (i = 0; i < nfds; i++) 
        {
            if (events[i].events & EPOLLIN) 
            {
                printf("hello world\n");
            }
        }
    }
	
	return 0;
}
