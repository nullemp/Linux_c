#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 500
int main()
{
	struct inv {
	int int_v;
	char variable_name [MAX_LENGTH];	
};

printf ("the ret is %d ", sizeof(((struct inv *) NULL)->variable_name));


	return 0;
}
