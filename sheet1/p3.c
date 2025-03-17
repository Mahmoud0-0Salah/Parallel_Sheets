#include <stdio.h>
#include <pthread.h>

typedef struct SumData{int *arr;int s;int e;int res;} SumData;

void *solve(void *argv)
{
	SumData* sum = (SumData*)argv;
	for (int i=sum->s;i<=sum->e;i++)
	{
		//printf("%d\n",sum->arr[i]);
		sum->res+=sum->arr[i];

	}
        return sum;
}

int main(int argc,char *argv[])
{
        pthread_t t1,t2;
        SumData  s1,s2;
	int arr[] ={1,2,3,4,5,6};
	s1.arr=arr;s1.s=0;s1.e=2;s1.res=0;
	s2.arr=arr;s2.s=3;s2.e=5;s2.res=0;
        pthread_create(&t1,NULL,solve,&s1);
        pthread_create(&t2,NULL,solve,&s2);


	SumData *r;
	int ans;
        pthread_join(t1,(void **)&r);
	ans=r->res;
        pthread_join(t2,(void **)&r);
	ans+=r->res;
        printf("ans = %d\n",ans);
        return 0;
}
