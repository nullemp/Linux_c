#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	if (fork())
		while(1)
			sleep(100);
}
