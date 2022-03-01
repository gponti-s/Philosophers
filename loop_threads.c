#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


/* **************************** LOOP THREADS ******************************
** If you put into the same loop the thread_create and the thread_join, so 
** you will have one thread runing after other, in a row. But when we wotk
** with threads, we want threads runing in parallel, so the correct way to do
** this is puting the thread_creation e the thread_join in different loops. Threrefor
** we will creat all the threads, leave them work and than finish the threads.
*/


enum error
{
    STATE_OK,
    NON_CREATE_T1,
    NON_CREATE_T2,
    NON_CREATE_T3,
    NON_CREATE_T4,
    NON_JOIN_T1,
    NON_JION_T2,
    NON_JION_T3,
    NON_JION_T4,
};

int mails = 0;
pthread_mutex_t mutex;

void *routine()
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char **argv)
{
    pthread_t th[4];
    enum error resp;
    int i;
    
    resp = STATE_OK;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < 4; i++)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
            resp = i;
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 4; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            resp = i + 4;
        printf("Thread %d finshed execution\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("The number of emails: %d\n", mails);
    return (resp);
}
