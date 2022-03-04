/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 12:25:48 by gponti-s          #+#    #+#             */
/*   Updated: 2021/02/16 12:25:51 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = malloc((ft_strlen(s1) * sizeof(char) + 1));
	if (ptr == NULL)
		return (NULL);
	return (ft_memcpy(ptr, s1, ft_strlen(s1) + 1));
}
