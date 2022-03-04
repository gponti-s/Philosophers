/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:31:11 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/04 19:56:40 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void parsing(int argc, e_prog_state prog_state)
{
    if (argc < 5 || argc > 6)
        printer(prog_state)
}

void printer(e_prog_state prog_state, t_info *ptr_info)
{
    if (prog_state == IVALID_ARGUMENT)
        ft_putstr_fd("Error - invalid argument", 1);
    if (prog_state == STRUCT_INICIALIZER_FAIL)
        ft_putstr_fd("Error - struct inicialization fail", 1);
    if (prog_state == NEGATIVE_NUMBER)
        ft_putstr_fd("Error - negative number as argument", 1);
    if (prog_state == MUTEX_INICIALIZER_FAIL)
        ft_putstr_fd("Error - mutex inicialzation fail", 1);
    clean_free(ptr_info);
    exit()
}

void	clean_free(t_info *ptr_info)
{
	size_t	count;

	if (ptr_info->philosophers && ptr_info->number_of_philosophers > 0)
	{
		count = 0;
		while (count < ptr_info->number_of_philosophers)
		{
			pthread_mutex_destroy(&(ptr_info->forks[count]));
			count++;
		}
		free(ptr_info->forks);
		free(ptr_info->philo);
		pthread_mutex_destroy(&(ptr_info->die));
		pthread_mutex_destroy(&(ptr_info->locked));
	}
}
