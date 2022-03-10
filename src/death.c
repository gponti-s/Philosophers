/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:15:46 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/08 17:28:42 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	msg_die(t_philosophers *ptr_philo)
{
	printf("[%ld] Philosopher  %lu died\n", get_time()
		- ptr_philo->info->init_time, ptr_philo->philosophers_id + 1);
}

static void	time_die(t_info *ptr_philo, size_t *count)
{
	pthread_mutex_lock(&(ptr_philo->locked));
	if (!ptr_philo->some_died && !ptr_philo->philosophers[*count].ate && !ptr_philo->philosophers[*count].must_eat
		&& (get_time() - ptr_philo->philosophers[*count].last_eat) >= ptr_philo->time_to_die)
	{
		pthread_mutex_unlock(&(ptr_philo->die));
		msg_die(ptr_philo->philosophers);
		if (ptr_philo->time_to_die)
			exit(EXIT_SUCCESS);
		ptr_philo->some_died = 1;
		pthread_mutex_unlock(&(ptr_philo->locked));
		pthread_exit(0);
	}
	if (ptr_philo->some_died)
	{
		pthread_mutex_unlock(&(ptr_philo->locked));
		pthread_mutex_unlock(&(ptr_philo->die));
		pthread_exit(0);
	}
	(*count)++;
	if (*count >= ptr_philo->number_of_philosophers && !ptr_philo->some_died)
		*count = 0;
	pthread_mutex_unlock(&(ptr_philo->locked));
}

void	*ft_die(void *philo)
{
	t_info	*ptr_philo;
	size_t	count;

	ptr_philo = (t_info *)philo;
	pthread_mutex_lock(&(ptr_philo->die));
	count = 0;
	while (count < ptr_philo->number_of_philosophers)
	{
		time_die(ptr_philo, &count);
		usleep(100);
	}
	return ((void *)0);
}
