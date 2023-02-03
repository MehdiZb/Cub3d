/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:02:19 by mzblah            #+#    #+#             */
/*   Updated: 2019/11/07 13:19:14 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	tab = (void *)malloc(count * size);
	if (!(tab))
		return (0);
	ft_bzero(tab, count * size);
	return (tab);
}
