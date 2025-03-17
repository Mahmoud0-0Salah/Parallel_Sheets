#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct VectorData{int* a;int* b;int* c;int index} VectorData;

void* solve(void* arg)
{
	VectorData* v =(VectorData*) arg;
	v->c[v->index] = v->a[v->index] + v->b[v->index];
}

int main(int argc,char* argv[])
{
	if (argc!=2)
		exit(1);
	int n = atoi(argv[1]);

	int a[n];
	int b[n];
	int c[n];
	for (int i=1;i<=n;i++)
	{
		a[i-1]=i;
		b[i-1]=i;
	}
	pthread_t t1;
	VectorData v1;
	v1.a=a;v1.b=b;v1.c=c;
	for (int i=0;i<n;i++)
	{
		v1.index=i;
		pthread_create(&t1,NULL,solve,&v1);
		pthread_join(t1,NULL);
	}
	for (int i=0;i<n;i++)
		printf("%d\n",c[i]);
}
