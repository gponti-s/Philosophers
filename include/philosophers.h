/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:17:19 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/04 20:19:22 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOFER_H
# define PHILOSOFER_H

# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_prog_state
{
	STATE_OK,
	INVALID_ARGUMENTS,
	STRUCT_INICIALIZER_FAIL,
	MUTEX_INICIALIZER_FAIL,
	NEGATIVE_NUMBER,
	ERROR,
}	e_prog_state;

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


// parse
void			parsing(int argc, e_prog_state prog_state);
void			printer(e_prog_state prog_state, t_info *ptr_info);
void			clean_free(t_info *ptr_info);

// inicializer
void			inicializer(t_info *general, int argc, char const **argv, e_prog_state prog_state);
static char 	init_args(t_info *general, int argc, char const **argv);
static char		set_info(size_t *ptr_info, int ref, char const **argv);
static char		init_philosophers(t_info *ptr_info);

// utilities
unsigned int	get_time(void);
long			ft_atoi_long(const char *str);
void			ft_sleep(unsigned int delay);
static char		init_mutex(t_info *ptr_info);

// routine



#endif
