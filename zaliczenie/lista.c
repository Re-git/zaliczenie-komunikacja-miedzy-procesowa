#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ELEMS 3
#define THREADS_NUM 3

pthread_mutex_t mymutex;
int is_full = 0;
pthread_cond_t list_cond_full, list_cond_empty;
int is_empty = 0;

typedef struct List
{
    int value;
    struct List* next;
} List;


int push_back(List** list,int arg)
{
    if(*list==NULL)
    {
        *list = (List*)malloc(sizeof(List));
        (*list)->value = arg;
        printf("dodalem %d do listy\n", (*list)->value);
        return 0;
    }
    int counter=1;
    List* tmp = *list;
    while(tmp->next)
    {
        counter++;
        if(counter>=MAX_ELEMS)
        {
            return -1;
        }
        tmp = tmp->next;
    }
    tmp->next = (List*)malloc(sizeof(List));
    tmp = tmp->next;
    tmp->value = arg;
    printf("dodalem %d do listy\n", tmp->value);
    return 0;
}

int pop_front(List** list)
{
    if(!(*list)) 
    {
        printf("Lista jest pusta, nic nie robie\n");
        return -1;
    }
    int value = (*list)->value;
    List* tmp = *list;
    *list = (*list)->next;
    free(tmp);
    printf("Usuwam %d z listy \n", value);
    return value;
}

void print(List* list)
{
    pthread_mutex_lock(&mymutex);
    List* tmp = list;
    printf("Czytam stan listy:\n");
    if(!(tmp)) printf("Lista jest pusta!\n");
    while(tmp)
    {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
    pthread_mutex_unlock(&mymutex);
}

void* readfun(void * arg)
{
    while(1)
    {
        pthread_mutex_lock(&mymutex);
        if(is_full == 0)
				pthread_cond_wait(&list_cond_full, &mymutex);
         
        pop_front((List**)arg);
        is_full = 0;
			pthread_cond_signal(&list_cond_empty);
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(NULL);
}

void* writefun(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mymutex);
        if(is_full == 1)
                pthread_cond_wait(&list_cond_empty, &mymutex);
        static int i=0;
        i++;
        push_back((List**)arg, i);
        is_full = 1;
		pthread_cond_signal(&list_cond_full);
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(NULL);
}

int main()
{
    List* head = NULL;

    printf("\nRozpoczynamy watki: \n\n");
    pthread_t w_threads[THREADS_NUM];
    pthread_t r_threads[THREADS_NUM];
    pthread_mutex_init(&mymutex,NULL);
    for (int i = 0; i < THREADS_NUM; i++)
    {
        int result = pthread_create(&w_threads[i],NULL,writefun,&head);
        if(result<0) printf("Could not create thread %d", i+1);
    }
    for (int i = 0; i < THREADS_NUM; i++)
    {
        int result = pthread_create(&r_threads[i],NULL,readfun,&head);
        if(result<0) printf("Could not create thread %d", i+1);
    }
    for (int i = 0; i < THREADS_NUM; i++)
    {
        pthread_join(w_threads[i],NULL);
    }
    for (int i = 0; i < THREADS_NUM; i++)
    {
        pthread_join(r_threads[i],NULL);
    }

    print(head);
    printf("\nMain thread end\n");

    pthread_mutex_destroy(&mymutex);
	pthread_cond_destroy(&list_cond_empty);
	pthread_cond_destroy(&list_cond_full);
    return 0;
}