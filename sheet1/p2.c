#include<stdio.h>
#include<pthread.h>

typedef struct {int id;int res;} ThreadData;

void * solve(void* arg)
{
        ThreadData* data = (ThreadData*) arg;
	data->res=data->id*data->id;
	return data;
}

int main(int argc,char* argv[])
{
        pthread_t th[3];
        ThreadData data[3];
        for (int i=0;i<3;i++)
        {
                data[i].id=i+2;
                pthread_create(&th[i],NULL,solve,&data[i]);
        }
	ThreadData* ans;
        for (int i=0;i<3;i++)
        {
                pthread_join(th[i],(void**)&ans);
		printf("id = %d, res =%d\n",ans->id,ans->res);
        }
}



