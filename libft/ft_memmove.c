/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:37:28 by Mzblah            #+#    #+#             */
/*   Updated: 2019/10/05 11:37:29 by Mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*srcc;
	unsigned char	*dstc;
	size_t			i;

	if ((!dest && !src) || !n)
		return (dest);
	i = -1;
	srcc = (unsigned char *)src;
	dstc = (unsigned char *)dest;
	if (srcc < dstc)
		while ((int)(--n) >= 0)
			*(dstc + n) = *(srcc + n);
	else
		while (++i < n)
			*(dstc + i) = *(srcc + i);
	return (dest);
}
