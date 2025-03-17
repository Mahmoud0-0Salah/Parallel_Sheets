#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct PrimeData{int s;int e;int* primes;int count; pthread_mutex_t lock;} PrimeData;

void* solve(void* argc)
{

	PrimeData* p = (PrimeData*) argc;

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

	PrimeData p1,p2,p3;
	p1.s=l; p1.e=l+s; p1.primes=NULL; p1.count=0; pthread_mutex_init(&p1.lock,NULL);
	p2.s=l+s+1; p2.e=l+s+1+s; p2.primes=NULL; p2.count=0; pthread_mutex_init(&p2.lock,NULL);
	p3.s=l+s+s+2; p3.e=r; p3.primes=NULL; p3.count=0; pthread_mutex_init(&p3.lock,NULL);

	pthread_t t1,t2,t3;
	pthread_create(&t1,NULL,solve,&p1);
	pthread_create(&t2,NULL,solve,&p2);
	pthread_create(&t3,NULL,solve,&p3);

	PrimeData * ans1,*ans2,*ans3;
	pthread_join(t1,(void**)&ans1);
	pthread_join(t2,(void**)&ans2);
	pthread_join(t3,(void**)&ans3);

	printf("Total primes numbers = %d \nPrimes: ", ans1->count+ ans2->count + ans3->count);
	for (int i=0;i<ans1->count;i++)
		printf("%d ",ans1->primes[i]);;
	for (int i=0;i<ans2->count;i++)
		printf("%d ",ans2->primes[i]);;
	for (int i=0;i<ans3->count;i++)
		printf("%d ",ans3->primes[i]);
	printf("\n");
	return 0;
}
