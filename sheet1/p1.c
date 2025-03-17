#include <stdio.h>
#include <pthread.h>

typedef struct ThreadData{int id;} ThreadData;

void* solve(void* arg)
{
	ThreadData* info = (ThreadData*) arg;
	printf("%d\n",info->id);
	return NULL;
}

int main(int argc,char* argv[])
{
	ThreadData t1,t2;
	t1.id =1;
	t2.id =2;
	pthread_t T1,T2;
	pthread_create(&T1,NULL,solve,&t1);
	pthread_create(&T2,NULL,solve,&t2);
	pthread_join(T1,NULL);
	pthread_join(T2,NULL);
	return 0;
}
