/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:07:46 by gponti-s          #+#    #+#             */
/*   Updated: 2021/02/12 13:07:51 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	n;
	size_t	j;

	i = 0;
	while (dst[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (i > dstsize)
	{
		return (j + dstsize);
	}
	n = 0;
	while ((i + 1 + n) < dstsize && src[n] != '\0')
	{
		dst[i + n] = src[n];
		n++;
	}
	dst[i + n] = '\0';
	return (i + j);
}
