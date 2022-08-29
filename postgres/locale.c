#include <stdio.h>
#include <langinfo.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	char *sys;
	sys = nl_langinfo(CODESET);
	puts(sys);
	return 0;
}
