/* ************* Pass Arguments Problems ****************
** To pass arguments to a thread we use the pthread_create, 
** in the fouth position, which means that the argument will
** fill the paramenters requested by the function in the 
** second position.
** The problem is that when dealing with pointers, we must 
** not pass the same address to be used by all threads at the 
** same time. We need to create a specific space in memory 
** that each thread will interact with. To do this we need
** to use dynamic allocation - malloc.
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void    *routine(void *arg)
{
    int index = *(int *)arg;
    printf("%d\n", primes[index]);
    free(arg);
}

int main(int argc, char **argv)
{
    pthread_t th[10];

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int)); //with this we avoid problems of using the same address for each thread.
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            perror("Failed to create thread");
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
     
    return 0;
}