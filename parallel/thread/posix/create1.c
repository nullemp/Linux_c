#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void *func(void *p)
{
	puts("thread is working!");
	// return NULL;
	pthread_exit(NULL);
}
int main(int argc, char **argv)
{
	pthread_t tid;
	int err;
	puts("begin");
	err = pthread_create(&tid, NULL, func, NULL);
	if (err)
	{
		fprintf(stderr, "pthead_create():%s\n", strerror(err));
		exit(1);
	}
	pthread_join(tid, NULL);
	puts("end");
	// if the machine has multiple cores, the func can't run possible? if no pthread_join?
	exit(0);

}
