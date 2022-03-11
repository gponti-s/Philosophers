/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <gponti-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:32:32 by gponti-s          #+#    #+#             */
/*   Updated: 2022/03/11 18:50:07 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	ft_atoi_long(const char *str)
{
	int		s;
	long	r;

	s = 1;
	r = 0;
	if (*str != '\0')
	{
		while ((*str == '\t') || (*str == '\n') || (*str == '\v')
			|| (*str == '\f') || (*str == '\r') || (*str == ' '))
			str++;
		while (*str == '-' || *str == '+')
		{
			if (*str == '-')
				s *= (-1);
			str++;
			if (*str == '-' || *str == '+')
				return (0);
		}
		while (*str >= '0' && *str <= '9')
		{
			r = r * 10 + ((*str) - '0');
			str++;
		}
	}
	return (s * r);
}

void	ft_sleep(unsigned int delay)
{
	unsigned int	init;

	init = get_time();
	while ((get_time() - init) < delay)
		usleep(delay / 10);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != 0)
		write(fd, s, ft_strlen(s));
}

int	ft_strlen(char *ptr)
{
	int	len;

	len = 0;
	while (ptr[len])
		len++;
	return (len);
}
