/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:14:26 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/11 18:51:42 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_fork(t_philosophers *p)
{
	size_t	f;

	f = (p->philosophers_id + 1) % p->info->number_of_philosophers;
	pthread_mutex_lock(&(p->info->forks[p->philosophers_id]));
	printf("[%ld] Philosopher %lu has taken a fork\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
	if (p->info->number_of_philosophers == 1)
	{
		ft_sleep(p->info->time_to_eat);
		pthread_mutex_unlock(&(p->info->forks[p->philosophers_id]));
		pthread_exit(0);
	}
	pthread_mutex_lock(&(p->info->forks[f]));
	printf("[%ld] Philosopher %lu has taken a fork\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
	pthread_mutex_unlock(&(p->info->forks[p->philosophers_id]));
}

static void	philo_eat(t_philosophers *p)
{
	printf("[%ld] Philosopher %lu is eating\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
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

static void	another_fork(t_philosophers *p)
{
	pthread_mutex_unlock(&(p->info->forks[p->philosophers_id]));
	pthread_mutex_unlock(&(p->info->forks[(p->philosophers_id + 1)
			% p->info->number_of_philosophers]));
	p->ate = 0;
	printf("[%ld] Philosopher %lu is sleeping\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
	ft_sleep(p->info->time_to_sleep);
}

void	*routine_philo(void *ptr)
{
	t_philosophers			*philo;

	philo = (t_philosophers *)ptr;
	if (philo->philosophers_id % 2)
		ft_sleep(philo->info->time_to_eat);
	while (1)
	{
		philo_fork(philo);
		philo_eat(philo);
		another_fork(philo);
		printf("[%ld] Philosopher %lu is thinking\n", get_time()
			- philo->info->init_time, philo->philosophers_id + 1);
		if (philo->info->some_died)
			pthread_exit(0);
	}
	pthread_exit(0);
}
