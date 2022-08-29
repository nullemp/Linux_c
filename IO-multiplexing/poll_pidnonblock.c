#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

int main(int argc, char **argv)
{
	fd_set rfds;
	struct timeval tv;
	int retval;
	int fd_save;
	fd_set rfds_bak;

	/* Watch stdin (fd 0) to see when it has input. */
	FD_ZERO(&rfds);
	fd_save = setnonblocking(0); // nonblock standard fd 0
	FD_SET(0, &rfds);
	/* Wait up to five seconds. */
	// tv.tv_sec = 5;
	// tv.tv_usec = 0;
	while(1)
	{
		rfds_bak = rfds;	
		retval = select(1, &rfds_bak, NULL, NULL, NULL);
		/* Don't rely on the value of tv now! */

		if (retval == -1)
		   perror("select()");
		else if (retval)
		   printf("Data is available now.\n");
		   /* FD_ISSET(0, &rfds) will be true. */
		else
		   printf("No data within five seconds.\n");

		exit(EXIT_SUCCESS);
	}
}


