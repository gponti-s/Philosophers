/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:46:22 by gponti-s          #+#    #+#             */
/*   Updated: 2021/02/23 11:46:24 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_printnb(long int nb, int fd)
{
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	print((nb % 10) + '0', fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	long	i;

	i = nb;
	if (i < 0)
	{
		print('-', fd);
		i = i * (-1);
	}
	ft_printnb(i, fd);
}
