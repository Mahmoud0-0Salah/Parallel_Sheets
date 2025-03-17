#include <stdio.h>
#include <pthread.h>

typedef struct ThreadResult{int id;int res;} ThreadResult;

void *solve(void *argv)
{

	ThreadResult* r = (ThreadResult*) argv;
	r->res=r->id*r->id;
//	printf("%d  %d\n",r->res,r->id);

	return r;
}

int main(int argc,char *argv[])
{
	pthread_t t1,t2,t3;
	ThreadResult r1,r2,r3;
	r1.id =2; r2.id =3; r3.id =4;
	pthread_create(&t1,NULL,solve,&r1);
	pthread_create(&t2,NULL,solve,&r2);
	pthread_create(&t3,NULL,solve,&r3);
	ThreadResult* ans;

	pthread_join(t1,(void **)&ans);
	printf("%d  %d\n",ans->res,ans->id);

	pthread_join(t2,(void **)&ans);
	printf("%d  %d\n",ans->res,ans->id);

	pthread_join(t3,(void **)&ans);
	printf("%d  %d\n",ans->res,ans->id);
	return 0;
}
