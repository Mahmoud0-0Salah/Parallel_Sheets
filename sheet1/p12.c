#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

const int N = 5;

int times=0;
pthread_cond_t c;
pthread_mutex_t l;
void barrier_wait(int id){
	pthread_mutex_lock(&l);
	times++;
	while (times <N)
		pthread_cond_wait(&c,&l);
	pthread_mutex_unlock(&l);
	pthread_cond_broadcast(&c);
    //Fill this function
}
void* doTask(void* arg){
    int id = (int)arg;
    printf("%d Stage 1\n", id);
   
    barrier_wait(id);
    printf("%d Stage 2\n", id);
    return NULL;
}
int main(){

	pthread_cond_init(&c,NULL);
	pthread_mutex_init(&l,NULL);

    pthread_t threads[N];
    for(int i = 0; i < N ; i++){
        pthread_create(threads + i, NULL, doTask, i);
    }
    for(int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
}
