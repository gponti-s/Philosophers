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
