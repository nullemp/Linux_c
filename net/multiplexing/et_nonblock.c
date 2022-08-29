#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int epfd, nfds;
    int i;
    struct epoll_event event, events[10];
    char buf[5];
    int flag;
	
    epfd = epoll_create(10);
    event.data.fd = 0;
    //event.events = EPOLLIN | EPOLLET; 
    event.events = EPOLLIN; 
    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);
 
#if 1 
	flag = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, flag | O_NONBLOCK);
#endif	
 
    while (1)
    {
        int i;
        int num = 0;
        char c;
		ssize_t ret;
		char buf[5];
        nfds = epoll_wait(epfd, events, 5, -1); 
		
        for (i = 0; i < nfds; ++i) 
        {
            if (events[i].events & EPOLLIN) 
            {
				memset(buf, '\0', 5); 
				ret = read(0, buf, 5);
				if(ret < 0)
				{
					if (errno == EAGAIN)
						break;
					else
						return -1;
				}
				puts(buf);
            }
            
        }
    }
	
    return 0;
}
