#include<stdio.h>
#include<pthread.h>


pthread_mutex_t l;
pthread_cond_t c,c2;
int flag =0;

void Pong()
{
	for (int i=0;i<5;i++)
	{
		pthread_mutex_lock(&l);
	        while(flag==0)
        	        pthread_cond_wait(&c,&l);
		printf("-Pong\n");
		flag=0;
		pthread_cond_signal(&c2);
		pthread_mutex_unlock(&l);
	}
}


void Ping()
{

        for (int i=0;i<5;i++) 
        {
                pthread_mutex_lock(&l);
                while(flag==1)
                        pthread_cond_wait(&c2,&l);
                printf("--Ping\n");
		flag=1;
		pthread_cond_signal(&c);
                pthread_mutex_unlock(&l);
        }
}

int main(int argc,char* argv[])
{

        pthread_cond_init(&c,NULL);
        pthread_cond_init(&c2,NULL);
        pthread_mutex_init(&l,NULL);
        pthread_t a,b;
        pthread_create(&a,NULL,Ping,NULL);
        pthread_create(&b,NULL,Pong,NULL);
        pthread_join(a,NULL);
	pthread_join(b,NULL);

}
