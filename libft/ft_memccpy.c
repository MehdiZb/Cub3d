/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:39:39 by Mzblah            #+#    #+#             */
/*   Updated: 2019/10/05 12:39:40 by Mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			cmpt;
	unsigned char	*c_src;
	unsigned char	*c_dst;

	cmpt = 0;
	c_src = (unsigned char *)src;
	c_dst = (unsigned char *)dest;
	while (cmpt < n)
	{
		c_dst[cmpt] = c_src[cmpt];
		if (c_src[cmpt] == (unsigned char)c)
			return ((dest + 1) + cmpt);
		cmpt++;
	}
	return (NULL);
}
