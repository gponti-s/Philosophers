/* **************************** LOOP THREADS ******************************
** If you put into the same loop the thread_create and the thread_join, so 
** you will have one thread runing after other, in a row. But when we wotk
** with threads, we want threads runing in parallel, so the correct way to do
** this is puting the thread_creation e the thread_join in different loops. Threrefor
** we will creat all the threads, leave them work and than finish the threads.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

enum error
{
    STATE_OK,
    NON_CREATE_T1,
    NON_JOIN_T1,
};

pthread_mutex_t mutex;

void *roll_dice()
{
   int *resposta = malloc(sizeof(int));;
   int value = (rand() % 6) + 1;
   *resposta = value;
   printf("Thread result: %p\n", resposta);
   return ((void*) resposta);
}

int main(int argc, char **argv)
{
    pthread_t th;
    enum error resp;
    int *res;
    
    srand(time(NULL));
    resp = STATE_OK;
    pthread_mutex_init(&mutex, NULL);

    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        resp = NON_CREATE_T1;

    if (pthread_join(th, (void **) &res) != 0)
        resp = NON_JOIN_T1;

    printf("The Main result: %p\n", res);
    printf("%d\n", *res);
    free(res);
    return (resp);
}
