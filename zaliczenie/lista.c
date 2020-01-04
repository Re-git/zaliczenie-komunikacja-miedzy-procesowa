#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ELEMS 3
#define THREADS_NUM 2

pthread_mutex_t mymutex;
pthread_cond_t is_cond_used;
pthread_cond_t is_cond_empty;
int used=0;
int empty=0;

typedef struct List
{
    int value;
    struct List* next;
} List;


int push_back(List** list,int arg)
{
    int counter=1;
    List* tmp = *list;
    while(tmp->next)
    {
        counter++;
        if(counter>=MAX_ELEMS) return -1;
        tmp = tmp->next;
    }
    tmp->next = (List*)malloc(sizeof(List));
    tmp = tmp->next;
    tmp->value = arg;
    return 0;
}

int pop_front(List** list)
{
    if(!(*list)) return -1;
    int value = (*list)->value;
    // List* tmp = *list;
    *list = (*list)->next;
    // free(tmp);
    return value;
}

void print(List* list)
{
    List* tmp = list;
    while(tmp)
    {
        printf("value:%d\n", tmp->value);
        tmp = tmp->next;
    }
}

List* makeList(int n)
{
    List* ptr = (List*)malloc(sizeof(List));
    ptr->value = n;
    return ptr;
}

void* readfun(void * arg)
{
    // pthread_mutex_lock(&mymutex);
    List* list = *(List**)arg;
    int result; 

    printf("before pop");
    result = pop_front(&list);
    printf("Popped: %d", result);
    // pthread_mutex_unlock(&mymutex);
    pthread_exit(NULL);
}

void* writefun(void* arg)
{
    // pthread_mutex_lock(&mymutex);
    printf("begin write");
    static int i=7;
    i++;
    List* list = *(List**)arg;
    printf("before push");
    push_back(&list, i);
    printf("after push");
    // pthread_mutex_unlock(&mymutex);
    pthread_exit(NULL);
}

int main()
{
    List* list = makeList(5);
    push_back(&list, 2);
    print(list);
    pop_front(&list);
    pop_front(&list);
    pop_front(&list);
    pop_front(&list);
    print(list);
    /*
    printf("Rozpoczynamy watki: \n");
// Threads
    pthread_t w_threads[2];
    pthread_t r_threads[2];
    for (int i = 0; i < THREADS_NUM; i++)
    {
        int result = pthread_create(&w_threads[i],NULL,writefun,&list);
        if(result<0) printf("Could not create thread %d", i+1);
    }
    for (int i = 0; i < THREADS_NUM; i++)
    {
        int result = pthread_create(&r_threads[i],NULL,readfun,&list);
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
    printf("Main thread end\n");
    */
    return 0;
}