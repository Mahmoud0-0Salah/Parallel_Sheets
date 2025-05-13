#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
typedef struct __node_t {
	int value;
	struct __node_t* next;
} node_t;

typedef struct __queue_t {
	node_t* head;
	node_t* tail;
	pthread_mutex_t head_lock, tail_lock;
} queue_t;

typedef struct data {
	queue_t* q;
	char* co;
} data;

void Queue_Init(queue_t* q) {
	node_t* tmp = malloc(sizeof(node_t));
	tmp->next = NULL;
	q->head = q->tail = tmp;
	pthread_mutex_init(&q->head_lock, NULL);
	pthread_mutex_init(&q->tail_lock, NULL);
}

void Queue_Enqueue(queue_t* q, int value) {
	node_t* tmp = malloc(sizeof(node_t));
	assert(tmp != NULL);
	tmp->value = value;
	tmp->next = NULL;

	pthread_mutex_lock(&q->tail_lock);
	q->tail->next = tmp;
	q->tail = tmp;
	pthread_mutex_unlock(&q->tail_lock);
}

int Queue_Dequeue(queue_t* q, int* value) {
	pthread_mutex_lock(&q->head_lock);
	node_t* tmp = q->head;
	node_t* newhead = q->head->next;

	if(newhead == NULL) {
		pthread_mutex_unlock(&q->head_lock);
		return -1;
	}

	*value = newhead->value;
	q->head = newhead;
	pthread_mutex_unlock(&q->head_lock);
	free(tmp);
	return 0;
}


void solve(void* argc){

	data* d = (data*) argc;
	for (int i=0;d->co[i]!='\0';i++)
	{
		if (d->co[i]=='E')
		{
			i++;
			Queue_Enqueue(d->q,d->co[i]-'0');
		}
		else
		{
			int temp;
			Queue_Dequeue(d->q,&temp);
		}
	}

	return;
}
int main(int argc,char* argv[])
{
	if (argc<2)
	{
		printf("Invalid argc\n");
		return;
	}
	queue_t q;
	Queue_Init(&q);
	data co[argc-1];
	pthread_t th[argc-1];
	for (int i=0;i<argc-1;i++)
	{
		co[i].co=argv[i+1];
		co[i].q=&q;
		pthread_create(&th[i],NULL,solve,&co[i]);
	}


	for (int i =0;i<argc-1;i++)
		pthread_join(th[i],NULL);


	int val;
	while(Queue_Dequeue(&q, &val) == 0) {
		printf("%d, ", val);
	}
	printf("\n");
}
