/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:14:26 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/17 20:31:42 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* This function make a philosopher take the forks */

static void	philo_fork(t_philosophers *p)
{
	size_t	f;

	f = (p->philosophers_id + 1) % p->info->number_of_philosophers;
	pthread_mutex_lock(&(p->info->forks[p->philosophers_id]));
	print_routine(p, FORK);
	if (p->info->number_of_philosophers == 1)
	{
		ft_sleep(p->info->time_to_eat);
		pthread_mutex_unlock(&(p->info->forks[p->philosophers_id]));
		pthread_exit(0);
	}
	pthread_mutex_lock(&(p->info->forks[f]));
	print_routine(p, FORK);
	pthread_mutex_unlock(&(p->info->forks[p->philosophers_id]));
}

/* This function will add information about eating (start eat time) and check how many times philosophers ate */

static void	philo_eat(t_philosophers *p)
{
	print_routine(p, EATING);
	p->ate = 1;
	p->last_eat = get_time();
	(p->eat_count)++;
	pthread_mutex_unlock(&(p->info->locked));
	if (p->info->philosopher_eat > 0
		&& p->eat_count >= p->info->philosopher_eat)
	{
		pthread_mutex_unlock(&(p->info->forks[p->philosophers_id]));
		pthread_mutex_unlock(&(p->info->forks[(p->philosophers_id + 1)
				% p->info->number_of_philosophers]));
		p->info->must_eat++;
		p->must_eat = 1;
		if (p->info->must_eat >= p->info->number_of_philosophers)
		{
			p->info->some_died = 1;
			ft_putstr_fd("Philosopher satisfied!!!\n", 1);
		}
		pthread_mutex_unlock(&(p->info->locked));
		pthread_exit(0);
	}
	pthread_mutex_unlock(&(p->info->locked));
	ft_sleep(p->info->time_to_eat);
}

/* This function releases the forks and starts sleep time */

static void	another_fork(t_philosophers *p)
{
	pthread_mutex_unlock(&(p->info->forks[p->philosophers_id]));
	pthread_mutex_unlock(&(p->info->forks[(p->philosophers_id + 1)
			% p->info->number_of_philosophers]));
	p->ate = 0;
	print_routine(p, SLEEPING);
	ft_sleep(p->info->time_to_sleep);
}

/* This function guarantees that philosophers will do the routine alternatively */

void	*routine_philo(void *ptr)
{
	t_philosophers			*philo;

	philo = (t_philosophers *)ptr;
	if (philo->philosophers_id % 2)
	{
		print_routine(philo, THINKING);
		ft_sleep(philo->info->time_to_eat);
	}
	while (1)
	{
		philo_fork(philo);
		philo_eat(philo);
		another_fork(philo);
		print_routine(philo, THINKING);
		if (philo->info->some_died)
			pthread_exit(0);
	}
	pthread_exit(0);
}
