/* ************** The difference between Threads and Process *****************
** 1 - Processes are run by different processes with different ids, 
**      while Threads run in a single process;
** 2 -  Each process handles each variable autonomously (changing one 
**      variable does not change it for all processes), whereas Treads share 
**      the same variable values.
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


void *routine()
{
    printf("First Thread.\n");
    sleep(3);
    printf("ending\n");
}

int main(int argc, char **argv)
{
    pthread_t t1;
    pthread_t t2;
    enum error resp;
    
    resp = STATE_OK;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        resp = NON_CREATE_T1;
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        resp = NON_CREATE_T2;
    if (pthread_join(t1, NULL) != 0)
        resp = NON_JOIN_T1;
    if (pthread_join(t2, NULL) != 0)
        resp = NON_JION_T2;
    printf("%d\n", resp);
    return (resp);
}
