/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:01:18 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/11 18:48:18 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	set_info(size_t *p, int ref, char const **argv);
static char	init_philosophers(t_info *p);
static char	init_mutex(t_info *p);

static char	init_args(t_info *general, int argc, char const **argv)
{
	general->init_time = get_time();
	general->some_died = 0;
	general->must_eat = 0;
	if (!set_info((&general->number_of_philosophers), 1, argv))
		return (INVALID_ARGUMENTS);
	if (!set_info((&general->time_to_die), 2, argv))
		return (INVALID_ARGUMENTS);
	if (!set_info((&general->time_to_eat), 3, argv))
		return (INVALID_ARGUMENTS);
	if (!set_info((&general->time_to_sleep), 4, argv))
		return (INVALID_ARGUMENTS);
	if (argc == 6)
	{
		if (!set_info((&general->philosopher_eat), 1, argv))
			return (INVALID_ARGUMENTS);
	}
	else
		general->philosopher_eat = 0;
	return (STATE_OK);
}

static char	set_info(size_t *p, int ref, char const **argv)
{
	long	len;
	int		i;

	i = 0;
	while (argv[ref][i] != '\0')
	{
		if (argv[ref][i] >= 48 && argv[ref][i] <= 57)
			i++;
		else
			return (0);
	}
	len = ft_atoi_long(argv[ref]);
	if (len <= 0 || len >= INT_MAX)
		return (0);
	*p = (size_t)len;
	return (1);
}

static char	init_philosophers(t_info *p)
{
	size_t	count;

	p->philosophers = (t_philosophers *)
		malloc(sizeof(t_philosophers) * p->number_of_philosophers);
	if (!p->philosophers)
		return (STRUCT_INICIALIZER_FAIL);
	count = 0;
	while (count < p->number_of_philosophers)
	{
		p->philosophers[count].philosophers_id = count;
		p->philosophers[count].info = p;
		p->philosophers[count].ate = 0;
		p->philosophers[count].eat_count = 0;
		p->philosophers[count].last_eat = get_time();
		p->philosophers[count].must_eat = 0;
		count++;
	}
	return (STATE_OK);
}

static char	init_mutex(t_info *p)
{
	size_t	count;

	if (pthread_mutex_init(&(p->print), NULL))
		return (MUTEX_INICIALIZER_FAIL);
	if (pthread_mutex_init(&(p->locked), NULL))
		return (MUTEX_INICIALIZER_FAIL);
	if (pthread_mutex_init(&(p->die), NULL))
		return (MUTEX_INICIALIZER_FAIL);
	p->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)
			*p->number_of_philosophers);
	if (!p->forks)
		return (MUTEX_INICIALIZER_FAIL);
	count = 0;
	while (count < p->number_of_philosophers)
	{
		if (pthread_mutex_init(&(p->forks[count]), NULL))
			return (MUTEX_INICIALIZER_FAIL);
		count++;
	}
	return (STATE_OK);
}

void	initializer(t_info *general, int argc,
char const **argv, e_prog_state prog_state)
{
	general->philosophers = NULL;
	prog_state = init_args(general, argc, argv);
	if (prog_state != STATE_OK)
		printer(prog_state, general);
	prog_state = init_philosophers(general);
	if (prog_state != STATE_OK)
		printer(prog_state, general);
	prog_state = init_mutex(general);
	if (prog_state != STATE_OK)
		printer(prog_state, general);
}
