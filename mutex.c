
/* **************************** The Race Condition ******************************
** The problem happens when you have threads handling the same variable at the 
** same time. It may happen that one thread interacts with the variable (eg incrementing) 
** while the other thread waits, keeping the original value. When the processor allows the 
** second thread to work, the interaction will happen with the wrong value as the first 
** thread incremented the value without the second thread being aware.
** To solve this problem we can use Mutex.
** Mutex works like a padlock, to allow all threads to work simultaneously.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

enum error
{
    STATE_OK,
    NON_CREATE_T1,
    NON_CREATE_T2,
    NON_JOIN_T1,
    NON_JION_T2,
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
    pthread_t t1;
    pthread_t t2;
    enum error resp;
    
    resp = STATE_OK;
    pthread_mutex_init(&mutex, NULL);
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        resp = NON_CREATE_T1;
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        resp = NON_CREATE_T2;
    if (pthread_join(t1, NULL) != 0)
        resp = NON_JOIN_T1;
    if (pthread_join(t2, NULL) != 0)
        resp = NON_JION_T2;
    printf("The number of emails: %d\n", mails);
    pthread_mutex_destroy(&mutex);
    return (resp);
}
