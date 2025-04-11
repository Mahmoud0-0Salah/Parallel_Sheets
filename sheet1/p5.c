#include <stdio.h>
#include <pthread.h>

typedef struct Counter{int v;pthread_mutex_t l;} Counter;

void *solve(void *argv)
{
	Counter* c =(Counter*) argv;
	pthread_mutex_lock(&c->l);
	for (int i=0;i<10000000;i++)
		c->v++;
	pthread_mutex_unlock(&c->l);
	return NULL;
}

int main(int argc,char *argv[])
{
	pthread_t th[3];
	Counter c;
	pthread_mutex_init(&c.l,NULL);
	c.v=0;
	for (int i=0;i<3;i++)
		pthread_create(&th[i], NULL, solve, &c);
	for (int i=0;i<3;i++)
		pthread_join(th[i],NULL);
	printf("%d\n",c.v);
}

