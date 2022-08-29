#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024
int main(int argc, char **argv)
{
	int bytes_num;	
	char buf[BUF_SIZE];
	while (1)
	{
		bytes_num = read(0, buf, BUF_SIZE);
		puts(buf);
	}
	exit(0);
}
