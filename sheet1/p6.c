#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct PrimeData{int s;int e;int* primes;int count; pthread_mutex_t lock;} PrimeData;

void* solve(void* argc)
{

	PrimeData* p = (PrimeData*) argc;
	//printf("%d, %d\n",p->s,p->e);
	for (int i=p->s;i<=p->e;i++)
	{
		int flag =0;
		if (i==1)
			continue;
		for (int j=2;j<=i/2;j++)
		{
			if (i%j==0)
			{
				flag =1;
				break;
			}
		}
		if (flag==0)
		{
			p->count++;
			p->primes = (int*) realloc(p->primes,p->count*sizeof(int));
			p->primes[p->count-1] = i;
		}
	}

	return p;

}


int main(int argc,char* argv[])
{
	if (argc!=3)
		exit(1);
	int l=atoi(argv[1]),r=atoi(argv[2]);
	int s = (r-l+1)/3;

	pthread_t th[3];
	PrimeData p[3];

	for (int i=0;i<3;i++)
	{
		p[i].s=l+s*i; p[i].e=p[i].s+s-1; p[i].primes=NULL; p[i].count=0; pthread_mutex_init(&p[i].lock,NULL);
	}
	p[2].e=r;

	for(int i=0;i<3;i++)
		pthread_create(&th[i],NULL,solve,&p[i]);

	PrimeData * ans[3];
	for(int i=0;i<3;i++)
		pthread_join(th[i],(void**)&ans[i]);

	printf("Total primes numbers = %d \nPrimes: ", ans[0]->count+ ans[1]->count + ans[2]->count);
	for (int j=0;j<3;j++)
	{
		for (int i=0;i<ans[j]->count;i++)
			printf("%d ",ans[j]->primes[i]);;
	}
	printf("\n");
	return 0;
}
