#include<stdio.h>
#include<pthread.h>

typedef struct {int id;} ThreadData;

void * solve(void* arg)
{
	ThreadData* data = (ThreadData*) arg;
	printf("%d\n",data->id);
}

int main(int argc,char* argv[])
{
	pthread_t th[3];
	ThreadData data[3];
	for (int i=0;i<3;i++)
	{
		data[i].id=i+1;
		pthread_create(&th[i],NULL,solve,&data[i]);
	}
	for (int i=0;i<3;i++)
	{
		pthread_join(th[i],NULL);
	}
}
