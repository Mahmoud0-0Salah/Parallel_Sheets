#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


typedef struct VectorData{int* a;int* b;int* c;int index} VectorData;

void* solve(void* arg)
{
	VectorData* v =(VectorData*) arg;
	v->c[v->index]=v->b[v->index]+v->a[v->index];

}

int main(int argc,char* argv[])
{
	if (argc!=2)
		exit(1);
	int n = atoi(argv[1]);

	int a[n];
	int b[n];
	int c[n];
	pthread_t th[n];
	VectorData data[n];
	for (int i=0;i<n;i++)
	{
		a[i]=i+1;
		b[i]=i+1;
		data[i].a=a;
		data[i].b=b;
		data[i].c=c;
		data[i].index=i;
		pthread_create(&th[i],NULL,solve,&data[i]);
	}

	for (int i=0;i<n;i++)
		pthread_join(th[i],NULL);
	for (int i=0;i<n;i++)
		printf("%d, ",c[i]);
	printf("\n");
}
