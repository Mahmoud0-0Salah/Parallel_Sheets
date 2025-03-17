#include <stdio.h>
#include <pthread.h>

typedef struct Counter{int v;pthread_mutex_t l;} Counter;

void *solve(void *argv)
{
	Counter* c = (Counter*) argv;
	pthread_mutex_lock(&c->l);
	for (int i=0;i<100000000;i++)
		c->v++;
	pthread_mutex_unlock(&c->l);

        //printf("c.v  =  %d\n",c->v);
        return NULL;
}

int main(int argc,char *argv[])
{
        pthread_t t1,t2,t3;
        Counter c;
	c.v=0;
	pthread_mutex_init(&c.l,NULL);
        pthread_create(&t1,NULL,solve,&c);
        pthread_create(&t2,NULL,solve,&c);
        pthread_create(&t3,NULL,solve,&c);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
        printf("c.v  =  %d\n",c.v);
        return 0;
}

