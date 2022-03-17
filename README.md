# Philosophers
This project involves knowledge of creating threads and using mutexes.

## HOW TO USE ##

Use the "make" command to compile the program: % make.
Examples of execution:
% ./philo 1 800 200 200 - Philosopher should not eat and die.
% ./philo 5 800 200 200 - No Philosopher should die.
% ./philo 5 800 200 200 7 - No Philosopher should die and it should stop after they have all eaten at least 7 times.
% ./philo 4 410 200 200 - No Philosopher should die.
% ./philo 4 310 200 100 - One Philosopher should die. 
But before running, let's understand the project better in the following lines.


## THE PROJECT (OVERVIEW) ##

One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table. 
The philosophers alternatively 
- eat, 
- think, or 
- sleep.
None of them should do more than one activity at the same time.
There are also forks on the table. There are as many forks as philosophers. A philosopher has to take their right and their left forks to eat, one in each hand.
When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
We need to keep in mind that:
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- Philosophers should avoid dying!


## GLOBAL RULES ##

- Global variables are forbidden!
- The program should take the following arguments:
    - number_of_philosophers => Each philosopher has a number ranging from 1 to number_of_philosophers. Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.
    - time_to_die => (milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die. A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
    - time_to_eat => (milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
    - time_to_sleep => (milliseconds): The time a philosopher will spend sleeping.
    - number_of_times_each_philosopher_must_eat => (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
The number of forks will be the same of number of philosophers.


## EXTERNAL FUNCTIONS ALLOWED ##

The project must be written using only these functions:
- memset, 
- printf, 
- malloc, 
- free, 
- write,
- usleep, 
- gettimeofday, 
- pthread_create,
- pthread_detach, 
- pthread_join, 
- pthread_mutex_init,
- pthread_mutex_destroy, 
- pthread_mutex_lock,
- pthread_mutex_unlock
