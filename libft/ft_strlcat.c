/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 23:52:32 by mzblah            #+#    #+#             */
/*   Updated: 2019/09/03 23:27:56 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	dest_size;
	size_t	src_size;

	count = 0;
	dest_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dest_size >= size)
		return (src_size + size);
	while (src[count] && (size - 1 > count + dest_size))
	{
		dst[count + dest_size] = src[count];
		count++;
	}
	dst[count + dest_size] = '\0';
	return (dest_size + src_size);
}
