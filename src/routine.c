/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:42:18 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/10 15:32:20 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo(t_info *ptr_info, e_prog_state prog_state)
{
	size_t	count;

	if (pthread_create(&(ptr_info->death), NULL, &ft_die, (void *)(ptr_info)))
		prog_state = THREADS_INICIALIZER_FAIL;
	pthread_detach(ptr_info->death);
	count = -1;
	while (++count < ptr_info->number_of_philosophers)
	{
		if (pthread_create(&(ptr_info->philosophers[count].thread),
				NULL, &routine_philo, (void *)(&(ptr_info->philosophers[count]))))
			prog_state = THREADS_INICIALIZER_FAIL;
	}
	count = -1;
	while (++count < ptr_info->number_of_philosophers)
		if (pthread_join(ptr_info->philosophers[count].thread, NULL))
			prog_state = THREADS_INICIALIZER_FAIL;
	if (prog_state != STATE_OK)
		printer(prog_state, ptr_info);
}
