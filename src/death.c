/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:15:46 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/11 18:50:27 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	msg_die(t_philosophers *p)
{
	printf("[%ld] Philosopher  %lu died\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
}

static void	time_die(t_info *p, size_t *count)
{
	pthread_mutex_lock(&(p->locked));
	if (!p->some_died && !p->philosophers[*count].ate
		&& !p->philosophers[*count].must_eat
		&& (get_time() - p->philosophers[*count].last_eat) >= p->time_to_die)
	{
		pthread_mutex_unlock(&(p->die));
		msg_die(p->philosophers);
		if (p->time_to_die)
			exit(EXIT_SUCCESS);
		p->some_died = 1;
		pthread_mutex_unlock(&(p->locked));
		pthread_exit(0);
	}
	if (p->some_died)
	{
		pthread_mutex_unlock(&(p->locked));
		pthread_mutex_unlock(&(p->die));
		pthread_exit(0);
	}
	(*count)++;
	if (*count >= p->number_of_philosophers && !p->some_died)
		*count = 0;
	pthread_mutex_unlock(&(p->locked));
}

void	*ft_die(void *philo)
{
	t_info	*p;
	size_t	count;

	p = (t_info *)philo;
	pthread_mutex_lock(&(p->die));
	count = 0;
	while (count < p->number_of_philosophers)
	{
		time_die(p, &count);
		usleep(100);
	}
	return ((void *)0);
}
