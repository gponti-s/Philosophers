/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:01:18 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/10 15:35:24 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	set_info(size_t *ptr_info, int ref, char const **argv);
static char	init_philosophers(t_info *ptr_info);
static char	init_mutex(t_info *ptr_info);

static char	init_args(t_info *general, int argc, char const **argv)
{
	general->init_time = get_time(); // I think is better call the printer here to avoid the initializer call all the others functions
	general->some_died = 0;
	general->must_eat = 0;
	if (!set_info((&general->number_of_philosophers), 1, argv))
		return (NEGATIVE_NUMBER);
	if (!set_info((&general->time_to_die), 1, argv))
		return (NEGATIVE_NUMBER);
	if (!set_info((&general->time_to_eat), 1, argv))
		return (NEGATIVE_NUMBER);
	if (!set_info((&general->time_to_sleep), 1, argv))
		return (NEGATIVE_NUMBER);
	if (argc == 6)
	{
		if (!set_info((&general->philosopher_eat), 1, argv))
			return (NEGATIVE_NUMBER);
	}
	else
		general->philosopher_eat = 0;
	return (STATE_OK);
}

static char	set_info(size_t *ptr_info, int ref, char const **argv)
{
	int	len;

	len = ft_atoi_long(argv[ref]);
	if (len <= 0)
		return (0);
	*ptr_info = (size_t)len;
	return (1);
}

static char	init_philosophers(t_info *ptr_info)
{
	size_t	count;

	ptr_info->philosophers = (t_philosophers *) malloc(sizeof(t_philosophers) * ptr_info->number_of_philosophers);
	if (!ptr_info->philosophers)
		return (STRUCT_INICIALIZER_FAIL);
	count = 0;
	while (count < ptr_info->number_of_philosophers)
	{
		ptr_info->philosophers[count].philosophers_id = count;
		ptr_info->philosophers[count].info = ptr_info;
		ptr_info->philosophers[count].ate = 0;
		ptr_info->philosophers[count].eat_count = 0;
		ptr_info->philosophers[count].last_eat = get_time();
		ptr_info->philosophers[count].must_eat = 0;
		count++;
	}
	return (STATE_OK);
}

static char	init_mutex(t_info *ptr_info)
{
	size_t	count;

	if (pthread_mutex_init(&(ptr_info->locked), NULL))
		return (MUTEX_INICIALIZER_FAIL);
	if (pthread_mutex_init(&(ptr_info->die), NULL))
		return (MUTEX_INICIALIZER_FAIL);
	ptr_info->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			*ptr_info->number_of_philosophers);
	if (!ptr_info->forks)
		return (MUTEX_INICIALIZER_FAIL);
	count = 0;
	while (count < ptr_info->number_of_philosophers)
	{
		if (pthread_mutex_init(&(ptr_info->forks[count]), NULL))
			return (MUTEX_INICIALIZER_FAIL);
		count++;
	}
	return (STATE_OK);
}

void	initializer(t_info *general, int argc, char const **argv, e_prog_state prog_state)
{
	general->philosophers = NULL;
	prog_state = init_args(general, argc, argv);
	prog_state = init_philosophers(general);
	prog_state = init_mutex(general);
	if (prog_state != STATE_OK)
		printer(prog_state, general);
}
