#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ELEMS 3
#define THREADS_NUM 3

pthread_mutex_t mymutex;
// pthread_cond_t list_cond_full, list_cond_empty;
// int is_full = 0;
// int is_empty = 0;

typedef struct List
{
    int value;
    struct List* next;
} List;


int push_back(List** list,int arg)
{
    if(*list==NULL)
    {
        // printf("lista jest pusta\n");
        *list = (List*)malloc(sizeof(List));
        (*list)->value = arg;
        printf("dodalem %d do listy\n", (*list)->value);
        return 0;
    }
    int counter=1;
    List* tmp = *list;
    while(tmp->next)
    {
        // if(is_full==1)
        // {
        //     pthread_cond_wait(&list_cond_empty, &mymutex);
        // }
        counter++;
        if(counter>=MAX_ELEMS)
        {
            // is_full = 1;
            // pthread_cond_signal(&list_cond_full);
            return -1;
        }
        tmp = tmp->next;
    }
    tmp->next = (List*)malloc(sizeof(List));
    tmp = tmp->next;
    tmp->value = arg;
    printf("dodalem %d do listy\n", tmp->value);
    // is_empty=0;
    return 0;
}

int pop_front(List** list)
{
    // if(is_empty==1)
    // {
    //     pthread_cond_wait(&list_cond_full, &mymutex);
    // }
    if(!(*list)) 
    {
        printf("Lista jest pusta, nic nie robie\n");
        // is_empty = 1;
        // pthread_cond_signal(&list_cond_empty);
        return -1;
    }
    int value = (*list)->value;
    List* tmp = *list;
    *list = (*list)->next;
    free(tmp);
    printf("Usuwam %d z listy \n", value);
    // is_full = 0;
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

List* makeList(int n)
{
    List* ptr = (List*)malloc(sizeof(List));
    ptr->value = n;
    return ptr;
}

void* readfun(void * arg)
{
    while(1)
    {
        pthread_mutex_lock(&mymutex);
        // printf("<-- Watek czytajacy rozpoczyna\n");
        int result; 
        result = pop_front((List**)arg);
        // printf("<-- Watek czytajacy konczy\n\n");
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(NULL);
}

void* writefun(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mymutex);
        // printf("--> Watek dodajacy rozpoczyna\n");
        static int i=0;
        i++;
        push_back((List**)arg, i);
        // printf("--> Watek dodajacy konczy\n\n");
        pthread_mutex_unlock(&mymutex);
    }
    pthread_exit(NULL);
}

int main()
{
    List* head = NULL;

    printf("\n\n");
    print(head);
    push_back(&head, 5);
    printf("adres listy: %p\n\n", head);
    print(head);
    pop_front(&head);
    print(head);

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
	// pthread_cond_destroy(&list_cond_empty);
	// pthread_cond_destroy(&list_cond_full);
    return 0;
}