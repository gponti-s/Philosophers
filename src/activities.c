/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:14:26 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/10 15:32:18 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_fork(t_philosophers *ptr_philo)
{
	size_t	f;

	f = (ptr_philo->philosophers_id + 1) % ptr_philo->info->number_of_philosophers;
	pthread_mutex_lock(&(ptr_philo->info->forks[ptr_philo->philosophers_id]));
	printf("[%ld] Philosopher %lu has taken a fork\n", get_time()
		- ptr_philo->info->init_time, ptr_philo->philosophers_id + 1);
	if (ptr_philo->info->number_of_philosophers == 1)
	{
		ft_sleep(ptr_philo->info->time_to_eat);
		pthread_mutex_unlock(&(ptr_philo->info->forks[ptr_philo->philosophers_id]));
		pthread_exit(0);
	}
	pthread_mutex_lock(&(ptr_philo->info->forks[f]));
	printf("[%ld] Philosopher %lu has taken a fork\n", get_time()
		- ptr_philo->info->init_time, ptr_philo->philosophers_id + 1);
	pthread_mutex_unlock(&(ptr_philo->info->forks[ptr_philo->philosophers_id]));
}

static void	philo_eat(t_philosophers *ptr_philo)
{
	printf("[%ld] Philosopher %lu is eating\n", get_time()
		- ptr_philo->info->init_time, ptr_philo->philosophers_id + 1);
	ptr_philo->ate = 1;
	ptr_philo->last_eat = get_time();
	(ptr_philo->eat_count)++;
	pthread_mutex_unlock(&(ptr_philo->info->locked));
	if (ptr_philo->info->philosopher_eat > 0 && ptr_philo->eat_count >= ptr_philo->info->philosopher_eat)
	{
		pthread_mutex_unlock(&(ptr_philo->info->forks[ptr_philo->philosophers_id]));
		pthread_mutex_unlock(&(ptr_philo->info->forks[(ptr_philo->philosophers_id + 1)
				% ptr_philo->info->number_of_philosophers]));
		ptr_philo->info->must_eat++;
		ptr_philo->must_eat = 1;
		if (ptr_philo->info->must_eat >= ptr_philo->info->number_of_philosophers)
		{
			ptr_philo->info->some_died = 1;
			printf("Philosopher satisfied!!!\n");
		}
		pthread_mutex_unlock(&(ptr_philo->info->locked));
		pthread_exit(0);
	}
	pthread_mutex_unlock(&(ptr_philo->info->locked));
	ft_sleep(ptr_philo->info->time_to_eat);
}

static void	another_fork(t_philosophers *ptr_philo)
{
	pthread_mutex_unlock(&(ptr_philo->info->forks[ptr_philo->philosophers_id]));
	pthread_mutex_unlock(&(ptr_philo->info->forks[(ptr_philo->philosophers_id + 1)
			% ptr_philo->info->number_of_philosophers]));
	ptr_philo->ate = 0;
	printf("[%ld] Philosopher %lu is sleeping\n", get_time()
		- ptr_philo->info->init_time, ptr_philo->philosophers_id + 1);
	ft_sleep(ptr_philo->info->time_to_sleep);
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
