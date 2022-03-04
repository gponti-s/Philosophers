/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:51:09 by gponti-s          #+#    #+#             */
/*   Updated: 2021/02/16 19:12:49 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	i;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] && ft_strrchr(set, s1[i]))
		i++;
	end = ft_strlen(s1 + i);
	if (end)
		while (s1[end + i - 1] != '\0'
			&& ft_strchr(set, s1[end + i - 1]) != NULL)
			end--;
	ptr = malloc(sizeof(char) * end + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, (s1 + i), (end + 1));
	ptr[end] = '\0';
	return (ptr);
}
