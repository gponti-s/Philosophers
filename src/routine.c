/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:42:18 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/11 18:43:19 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo(t_info *p, e_prog_state prog_state)
{
	size_t	count;

	if (pthread_create(&(p->death), NULL, &ft_die, (void *)(p)))
		prog_state = THREADS_INICIALIZER_FAIL;
	pthread_detach(p->death);
	count = -1;
	while (++count < p->number_of_philosophers)
	{
		if (pthread_create(&(p->philosophers[count].thread),
				NULL, &routine_philo, (void *)(&(p->philosophers[count]))))
			prog_state = THREADS_INICIALIZER_FAIL;
	}
	count = -1;
	while (++count < p->number_of_philosophers)
		if (pthread_join(p->philosophers[count].thread, NULL))
			prog_state = THREADS_INICIALIZER_FAIL;
	if (prog_state != STATE_OK)
		printer(prog_state, p);
}

void print_routine(t_philosophers *p, e_message message)
{
	pthread_mutex_lock(&(p->info->print));
	if (message == FORK && p->info->some_died == 0)
		printf("[%ld] Philosopher %lu has taken a fork\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
	else if (message == EATING && p->info->some_died == 0)
		printf("[%ld] Philosopher %lu is eating\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
	else if (message == SLEEPING && p->info->some_died == 0)
		printf("[%ld] Philosopher %lu is sleeping\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
	else if (message == THINKING && p->info->some_died == 0)
		printf("[%ld] Philosopher %lu is thinking\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
	else if(message == DIE)
	{
		printf("[%ld] Philosopher %lu died\n", get_time()
		- p->info->init_time, p->philosophers_id + 1);
		p->info->some_died = 1;
	}
	pthread_mutex_unlock(&(p->info->print));
}
