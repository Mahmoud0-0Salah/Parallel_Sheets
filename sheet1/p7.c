#include <stdio.h>
#include<pthread.h>
#include <time.h>
#include <stdlib.h>


typedef struct{int s;int e;int v;int *arr} data;
int found=0;

void* solve(void* argc)
{
	data *d =(data*)argc;
	for (int i =d->s;i<d->e&&found==0;i++)
	{
		if (d->arr[i]==d->v)
		{

			printf("%d %d\n",d->arr[i],d->v);
			found=1;
			return;
		}
	}
	return;
}


int main(int argc,char* argv[])
{
	srand(time(NULL));
	if (argc!=4)
	{
		printf("Invalid argc\n");
		return;
	}

	int s =atoi(argv[1]),th=atoi(argv[2]),v=atoi(argv[3]);
	//printf("%d",th);
	int arr[s];
	for (int i=0;i<s;i++)
		arr[i]=rand()%(s+1);
	pthread_t threads[th];
	data d[th];
	for (int i=0;i<th;i++)
	{
		d[i].v=v;

		if (i==0)
			d[i].s=0;
		else
			d[i].s=d[i-1].e;
		d[i].e=d[i].s+(s/th);
		d[i].arr=arr;
//		printf("%d %d\n",arr[i],i);
		if(i==th-1)
			d[i].e=s;
		pthread_create(&threads[i],NULL,solve,&d[i]);
	}
	for (int i=0;i<th;i++)
		pthread_join(threads[i],NULL);
	if (found==0)
		printf("V not Found \n");
	else
		printf("V Found \n");
}
