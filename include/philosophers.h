/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:17:19 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/10 15:29:14 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILOSOPHER_H
# define	PHILOSOPHER_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum e_prog_state
{
	STATE_OK,
	INVALID_ARGUMENTS,
	STRUCT_INICIALIZER_FAIL,
	MUTEX_INICIALIZER_FAIL,
	THREADS_INICIALIZER_FAIL,
	NEGATIVE_NUMBER,
	ERROR,
}				e_prog_state;

typedef	struct	s_philosophers
{
	pthread_t		thread;
	size_t			philosophers_id;
	size_t			last_eat;
	size_t			eat_count;
	char			must_eat;
	char			ate;
	struct s_info	*info;
}				t_philosophers;

typedef struct s_info
{
	pthread_t			death;
	pthread_mutex_t		*forks;
	pthread_mutex_t		die;
	pthread_mutex_t		locked;
	t_philosophers		*philosophers;
	size_t				number_of_philosophers;
	size_t				philosopher_eat;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				init_time;
	size_t				must_eat;
	char				some_died;
}				t_info;

// parse.c
void			parsing(int argc, e_prog_state prog_state);
void			printer(e_prog_state prog_state, t_info *ptr_info);
void			clean_free(t_info *ptr_info);

// inicializer.c
void			initializer(t_info *general, int argc, char const **argv, e_prog_state prog_state);
// char 			init_args(t_info *general, int argc, char const **argv);
// char			set_info(size_t *ptr_info, int ref, char const **argv);
// char			init_philosophers(t_info *ptr_info);
// char			init_mutex(t_info *ptr_info);

// utilities.c
unsigned int	get_time(void);
long			ft_atoi_long(const char *str);
void			ft_sleep(unsigned int delay);
void			ft_putstr_fd(char *s, int fd);
int 			ft_strlen(char *ptr);

// routine.c
void			philo(t_info *ptr_info, e_prog_state e_prog_state);
void			*routine_philo(void *p);

// activities.c
// void			another_fork(t_philosophers *p);
// void			philo_fork(t_philosophers *p);
// void			philo_eat(t_philosophers *p);

// death.c
void			*ft_die(void *philo);

#endif
