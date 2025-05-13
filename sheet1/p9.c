#include<stdio.h>
#include<pthread.h>


pthread_mutex_t l;
pthread_cond_t c;
int flag =0;

void RunA()
{
	printf("a Wait b\n");
	while(flag==0)
		pthread_cond_wait(&c,&l);
}


void RunB()
{
	sleep(2);
	printf("b finish\n");
	flag=1;
	pthread_cond_signal(&c);
}

int main(int argc,char* argv[])
{

	pthread_cond_init(&c,NULL);
	pthread_mutex_init(&l,NULL);
	pthread_t a,b;
	pthread_create(&a,NULL,RunA,NULL);
	pthread_create(&b,NULL,RunB,NULL);
	printf("main wait b\n");
	while(flag==0);

}
