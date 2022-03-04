/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gponti-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:05:49 by gponti-s          #+#    #+#             */
/*   Updated: 2021/03/09 11:05:52 by gponti-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;

	if (lst != NULL)
	{
		while (*lst)
		{
			buffer = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = buffer;
		}
	}
}
