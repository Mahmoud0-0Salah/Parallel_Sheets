#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct {int* arr;int s;int e;int res;} SumData;

void * solve(void* arg)
{
        SumData* s= (SumData*) arg;
        for (int i = s->s;i<=s->e;i++)
                s->res+=s->arr[i];
        return s;
}

int main(int argc,char* argv[])
{
        int ans =0;
        int arr[] ={1,2,3,4,5,6};
        pthread_t th[2];
        SumData data[2];
        data[0].arr=arr;data[0].s=0;data[0].e=2;
        data[1].arr=arr;data[1].s=3;data[1].e=5;

        pthread_create(&th[0],NULL,solve,&data[0]);
        pthread_create(&th[1],NULL,solve,&data[1]);

        SumData* r;
        pthread_join(th[0],(void )&r);
        ans+=r->res;
        pthread_join(th[0],(void )&r);
        ans+=r->res;
        printf("result = %d\n",ans);
}