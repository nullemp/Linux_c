#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char portNumberStr[32];
	unsigned short portNumber = 9190;
	snprintf(portNumberStr, sizeof(portNumberStr), "%d", portNumber);
	puts(portNumberStr);
	exit(0);
}
